#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the antire value of the pointer variable
 * @types: List a of all the arguments
 * @buffer: Buffer array to handle a print
 * @flags:  Calculates active flags
 * @width: get to a width
 * @precision: Precision specification
 * @size: Size of specifier
 * Return: Number of chars printed succuess.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes into hexa of non printable chars
 * @types: Lista of all the arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates perfectly  active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size of a specifier
 * Return: Number of chars printed success
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int v = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[v] != '\0')
	{
		if (is_printable(str[v]))
			buffer[v + offset] = str[v];
		else
			offset += append_hexa_code(str[v], buffer, v + offset);

		v++;
	}

	buffer[v + offset] = '\0';

	return (write(1, buffer, v + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse all the string.
 * @types: Lista of an arguments
 * @buffer: Buffer array into handle print
 * @flags:  Calculates the active flags
 * @width: get on width
 * @precision: Precision of specification
 * @size: Size specifier
 * Return: Numbers of chars evenly printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int v, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (v = 0; str[v]; v++)
		;

	for (v = v - 1; v >= 0; v--)
	{
		char z = str[v];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print into a string in rot13.
 * @types: Lista of all arguments
 * @buffer: Buffer array to handle an print
 * @flags:  Calculates accurate active flags
 * @width: get on width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of a chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int v, n;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (v = 0; str[v]; v++)
	{
		for (n = 0; in[n]; n++)
		{
			if (in[n] == str[v])
			{
				x = out[n];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[n])
		{
			x = str[v];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
