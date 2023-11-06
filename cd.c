#include "main.h"

/**
 * change_directory - change directory
 * @command: command
 *
 * Return: void
 */

void change_directory(char **command)
{
	if (command[1] == NULL)
	{
		chdir(getenv("HOME"));
	}

	else
	{
		if (chdir(command[1]) == -1)
		{
			print_string("No such file or directory\n");
		}
	}
}
