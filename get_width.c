#include "main.h"

/**
 * get_width - function that calculates the width for printing
 * @format: string to print the arguments.
 * @i: arguments to be printed.
 * @list: list of arguments.
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int a;
	int wid;

	wid = 0;

	for (a = *i + 1; format[a] != '\0'; a++)
	{
		if (is_digit(format[a]))
		{
			wid *= 10;
			wid += format[a] - '0';
		}
		else if (format[a] == '*')
		{
			a++;
			wid = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = a - 1;

	return (wid);
}
