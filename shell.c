#include "main.h"

/**
 * main - main function
 * @argc: argument count
 * @argv: argumet vector
 *
 * Return: 0 0n success
 */

int main(int argc, char **argv)
{
	char *buffer, *command[20], *commandpath;
	size_t buffer_size = 0;
	ssize_t char_count;
	int i, j;

	if (argc > 1)
		return (-1);
	while (1)
	{
		if (isatty(0))
			print_string("$ ");
		char_count = getline(&buffer, &buffer_size, stdin);
		if (char_count == -1)
			break;
		i = 0;
		while (buffer[i])
		{
			if (buffer[i] == '\n')
				buffer[i] = 0;
			i++;
		}
		j = 0;
		command[j] = strtok(buffer, " ");
		while (command[j])
			command[++j] = strtok(NULL, " ");
		command[j] = NULL;
		if (builts_check(command) != 0)
			continue;
		commandpath = getpath(command[0]);
		if (commandpath == NULL)
		{
			print_string(argv[0]);
			print_string(": No such file or directory\n");
			free(commandpath);
			continue;
		}
		excute(commandpath, command);
	}
	free(commandpath);
	return (0);
}
