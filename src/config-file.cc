/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * config-file.cc - Simple config file parser.
 */

#include "config-file.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <algorithm>
#include <regex>

/* All key-value pairs not designated to a section are placed in a
 * section __GLOBAL. Since this name is not accepted by sectionRegex,
 * there cannot be a collision.
 */
static const std::string globalSectionName("__GLOBAL");


ConfigFile::ConfigFile(const std::string &filename)
{
  load(filename);
}

void
ConfigFile::clear(void)
{
  sections.clear();
  properties.clear();
}

void
ConfigFile::load(const std::string &filename)
{
  clear();

  /* Add default "global" section and make active */
  std::string currentSection(globalSectionName);
  sections.push_back(currentSection);

  /* Regexes to use while parsing */
  std::regex sectionRegex("\\[([a-zA-Z0-9]+)\\]\\s*");
  std::regex keyValueRegex("([a-zA-Z]\\S*)\\s*=\\s*(\\S+)");
  std::regex emptyLineRegex("^\\s*$");
  std::smatch match;

  /* Open and parse the file */
  std::fstream file(filename.c_str());
  if (!file.good())
    throw std::runtime_error("cannot open file " + filename);

  std::string line;
  int lineNumber(0);
  while (std::getline(file, line))
    {
      ++lineNumber;

      /* Is this a section header? */
      if (std::regex_match(line, match, sectionRegex))
        {
          if (hasSection(match[1]))
            {
              std::stringstream msg;
              msg << filename << ": line " << lineNumber
                  << ": duplicate definition of section '" << match[1] << "'";
              throw std::runtime_error(msg.str());
            }

          currentSection = match[1];
          addSection(match[1]);
        }
      /* A key value pair? */
      else if (std::regex_match(line, match, keyValueRegex))
        {
          if (hasProperty(currentSection, match[1]))
            {
              std::stringstream msg;
              msg << filename << ": line " << lineNumber
                  << ": duplicate definition of '" << match[1] << "'";
              throw std::runtime_error(msg.str());
            }

          addProperty(std::make_pair(currentSection, match[1]), match[2]);
        }
      /* An empty line, perhaps? Otherwise: give up. */
      else if (!std::regex_match(line, match, emptyLineRegex))
        {
          std::cerr << "warning: " << filename
                    << ": cannot parse line " << lineNumber
                    << ", ignoring." << std::endl;
        }
    }

  file.close();
}


bool
ConfigFile::hasSection(const std::string &sectionName) const
{
  auto it = std::find(sections.begin(), sections.end(), sectionName);

  return it != std::end(sections);
}

const std::list<std::string> &
ConfigFile::getSections(void) const
{
  return sections;
}

bool
ConfigFile::hasProperty(const std::string &sectionName,
                        const std::string &keyName) const
{
  auto item = properties.find(std::make_pair(sectionName, keyName));

  return item != std::end(properties);
}

/* Translate properties of a specified section from the internal
 * data structure to a simple vector of key-value pairs.
 */
std::vector<ConfigFile::KeyValue>
ConfigFile::getProperties(const std::string &sectionName) const
{
  std::vector<ConfigFile::KeyValue> result;

  for (auto &property : properties)
    if (property.first.first == sectionName)
      result.push_back(std::make_pair(property.first.second, property.second));

  return result;
}


void
ConfigFile::addSection(const std::string &sectionName)
{
  sections.push_back(sectionName);
}

void
ConfigFile::addProperty(const PropertyName &propertyName,
                        const std::string &value)
{
  properties.emplace(std::make_pair(propertyName, value));
}
