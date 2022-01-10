#include <stdio.h>

static struct {
    int base;
    char repr;
} roman_table[] = {
    {    1000,   'M' },
    {     500,   'D' },
    {     100,   'C' },
    {      50,   'L' },
    {      10,   'X' },
    {       5,   'V' },
    {       1,   'I' },
    {       0,     0 }
};

void print_roman(int x)
{
    volatile char *debugout = (char*)0x200;
    int i;

    for (i = 0; roman_table[i].base != 0; ++i)
    {
        while (x >= roman_table[i].base)
        {
            *debugout = roman_table[i].repr;
            x = x - roman_table[i].base;
        }
    }

    *debugout = '\n';
}
