#include "main.h"

/**
 * get_precision - function that calculates the precision
 * @format: stringto print the arguments
 * @i: integer
 * @list: arguments.
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int a;
	int precn;

	a = *i + 1;
	precn = -1;

	if (format[a] != '.')
		return (precn);

	precn = 0;

	for (a += 1; format[a] != '\0'; a++)
	{
		if (is_digit(format[a]))
		{
			precn *= 10;
			precn += format[a] - '0';
		}
		else if (format[a] == '*')
		{
			a++;
			precn = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = a - 1;

	return (precn);
}
