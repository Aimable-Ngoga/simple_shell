#include "main.h"

/**
 * environment - prints environmet variables
 *
 * Return: void
 */

void environment(void)
{
	int i = 0;

	while (environ[i])
	{
		print_string(environ[i]);
		print_string("\n");
		i++;
	}

}
