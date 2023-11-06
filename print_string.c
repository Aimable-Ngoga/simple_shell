#include "main.h"

/**
 * print_string - prints a string
 * @string: string to be printed
 *
 * Return: number of chars printed
 */

int print_string(char *string)
{
	int count = 0;
	int i = 0;

	while (string[i])
	{
		count += write(1, &string[i], 1);
		i++;
	}

	return (count);
}

