#include "main.h"

/**
 * handle_write_char - Function that prints a string
 * @c: character
 * @buffer: Buffer array
 * @flags: active flags calculator.
 * @width: get width.
 * @precision: specify precision
 * @size: specify Size
 * Return: Number of characters
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* paddind is stored at buffer's right whereas char is stored at left */
	int a = 0;
	char pd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		pd = '0';

	buffer[a++] = c;
	buffer[a] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (; a < width - 1; a++)
			buffer[BUFF_SIZE - a - 2] = pd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - function that prints a string
 * @is_negative: Lista of arguments
 * @ind: character
 * @buffer: Buffer array
 * @flags:  active flags calculator
 * @width: width.
 * @precision: specify precision
 * @size: Specify size
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int leng = BUFF_SIZE - ind - 1;
	char pd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		leng, pd, extra_ch));
}

/**
 * write_num - function that writes a number using a bufffer
 * @ind: Index
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision
 * @length: length
 * @padd: Pading
 * @extra_c: character
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int a;
	int pd = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (a = 1; a < width - length + 1; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], a - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], a - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--pd] = extra_c;
			return (write(1, &buffer[pd], a - pd) +
				write(1, &buffer[ind], length - (1 - pd)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - function that writes an unsigned number
 * @is_negative: Number
 * @ind: Index
 * @buffer: Array
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int leng = BUFF_SIZE - ind - 1;
	int a = 0;
	char pd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precision > 0 && precision < leng)
		pd = ' ';
	while (precision > leng)
	{
		buffer[--ind] = '0';
		leng++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pd = '0';
	if (width > leng)
	{
		for (; a < width - leng; a++)
			buffer[a] = pd;
		buffer[a] = '\0';
		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>pd]*/
			return (write(1, &buffer[ind], leng) + write(1, &buffer[0], a));
		else /* Asign extra char to left of padding [pd>buffer]*/
			return (write(1, &buffer[0], a) + write(1, &buffer[ind], leng));
	}

	return (write(1, &buffer[ind], leng));
}

/**
 * write_pointer - function that writes a memory address
 * @buffer: Array
 * @ind: Index
 * @length: Length
 * @width: Width
 * @flags: Flags
 * @padd: padding
 * @extra_c: Character
 * @padd_start: Index
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int a;

	if (width > length)
	{
		for (a = 3; a < width - length + 3; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], a - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], a - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
