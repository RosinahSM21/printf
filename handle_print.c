#include "main.h"
/**
 * handle_print - function that prints an argument based on its type
 * @fmt: string to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: integer
 * @buffer: Buffer array.
 * @flags: Calculates flags
 * @width: width.
 * @precision: Precision
 * @size: Specify size
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = 0;
	int leng = 0;
	int chars = -1;

	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (; fmt_types[a].fmt != '\0'; a++)
		if (fmt[*ind] == fmt_types[a].fmt)
			return (fmt_types[a].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[a].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		leng += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			leng += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		leng += write(1, &fmt[*ind], 1);
		return (leng);
	}
	return (chars);
}

