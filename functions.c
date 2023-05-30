#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints on a char
 * @types: List all of the arguments
 * @buffer: Buffer the array to a handle print
 * @flags:  Calculates exact active flags
 * @width: A width
 * @precision Precision specification
 * @size: Size of specifier
 * Return: Number of all the chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, d;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (d = width - length; d > 0; d--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (d = width - length; d > 0; d--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent of the sign
 * @types: Lista as many of  arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates on the target active flags
 * @width: get a width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars are printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print in a  int
 * @types: Lista of the perfact arguments
 * @buffer: Buffer array to handle into a print
 * @flags:  Calculates active smart flags
 * @width: get the surrounded width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars are printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int d = BUFF_SIZE - 2;
	int is_negative = 0;
	long int b = va_arg(types, long int);
	unsigned long int num;

	b = convert_size_number(b, size);

	if (b == 0)
		buffer[d--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)b;

	if (b < 0)
	{
		num = (unsigned long int)((-1) * b);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[d--] = (num % 10) + '0';
		num /= 10;
	}

	d++;

	return (write_number(is_negative, d, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints on  an unsigned number
 * @types: Lista of vary arguments
 * @buffer: Buffer array is to handle print
 * @flags:  Calculates perfect active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size of the specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int b, c, d, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	b = va_arg(types, unsigned int);
	c = 2147483648; /* (2 ^ 31) */
	a[0] = b / c;
	for (d = 1; d < 32; d++)
	{
		c /= 2;
		a[d] = (b / c) % 2;
	}
	for (d = 0, sum = 0, count = 0; d < 32; d++)
	{
		sum += a[d];
		if (sum || d == 31)
		{
			char z = '0' + a[d];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

