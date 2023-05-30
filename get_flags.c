#include "main.h"

/**
 * get_flags - Calculates flags
 * @format: string to print the arguments
 * @i:integer.
 * Return: Flags
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int a;
	int b;
	int flg;

	a = 0;
	flg = 0;

	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (b = *i + 1; format[b] != '\0'; b++)
	{
		for (; FLAGS_CH[a] != '\0'; a++)
			if (format[curr_i] == FLAGS_CH[a])
			{
				flg |= FLAGS_ARR[a];
				break;
			}

		if (FLAGS_CH[a] == 0)
			break;
	}

	*i = b - 1;

	return (flg);
}
