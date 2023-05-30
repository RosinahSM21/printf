#include "main.h"

/**
 * get_size - function tht calculates the size to cast the argument
 * @format: string to print the arguments
 * @i: arguments to be printed.
 * Return: size.
 */
int get_size(const char *format, int *i)
{
        int a;
        int sz;

        a = *i + 1;
        sz = 0;

        if (format[a] == 'l')
                sz = S_LONG;
        else if (format[a] == 'h')
                sz = S_SHORT;

        if (sz == 0)
                *i = a - 1;
        else
                *i = a;

        return (sz);
}
