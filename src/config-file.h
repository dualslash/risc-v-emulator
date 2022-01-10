/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * config-file.h - Simple config file parser
 */

#ifndef __CONFIG_FILE__
#define __CONFIG_FILE__

#include <string>

#include <vector>
#include <list>
#include <map>

class ConfigFile
{
  public:
    using KeyValue = std::pair<std::string, std::string>;

    ConfigFile(const std::string &filename);

    void load(const std::string &filename);

    bool hasSection(const std::string &sectionName) const;
    const std::list<std::string> &getSections(void) const;

    bool hasProperty(const std::string &sectionName,
                     const std::string &keyName) const;
    std::vector<KeyValue> getProperties(const std::string &sectionName) const;

  private:
    using PropertyName = std::pair<std::string, std::string>;
    using PropertyMap = std::map<PropertyName, std::string>;
    PropertyMap properties;

    std::list<std::string> sections;

    void clear(void);

    void addSection(const std::string &sectionName);
    void addProperty(const PropertyName &propertyName,
                     const std::string &value);
};

#endif /* __CONFIG_FILE__ */
