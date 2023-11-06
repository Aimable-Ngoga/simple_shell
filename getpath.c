#include "main.h"

/**
 * getpath - find the path of a command
 * @command: command to be found
 *
 * Return: pointer to the path of command
 */

char *getpath(char *command)
{
	char *path, *pathtoken, *filepath, *pathcopy;
	

	path = getenv("PATH");

	pathcopy = strdup(path);

	pathtoken = strtok(pathcopy, ":");

	filepath = malloc(strlen(pathtoken) + strlen(command) + 2);

	while (pathtoken)
	{
		strcpy(filepath, pathtoken);
		strcat(filepath, "/");
		strcat(filepath, command);
		strcat(filepath, "\0");

		if (access(filepath, X_OK) == 0)
		{
			return (filepath);
		}

		pathtoken = strtok(NULL, ":");
	}

	return (NULL);
}
