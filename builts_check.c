#include "shell.h"

/**
 * builts_check - checks if the command is builten command
 * @command: command to be checked
 *
 * Return: 0 on success
 */

int builts_check(char **command)
{
	if (strcmp(command[0], "exit") == 0)
	{
		exit(0);
	}

	else if (strcmp(command[0], "env") == 0)
	{
		environment();
		return (1);
	}

	else if (strcmp(command[0], "setenv") == 0)
	{
		print_string("setenv");
		return (1);
	}

	else if (strcmp(command[0], "unsetenv") == 0)
	{
		print_string("unsetenv");
		return (1);
	}

	else if (strcmp(command[0], "cd") == 0)
	{
		change_directory(command);
		return (1);
	}

	return (0);
}
