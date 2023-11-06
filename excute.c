#include "main.h"

/**
 * excute - create new pid with fork and run ecxecv
 * @command: command to be excuted
 * @env: environment variable
 * @commandpath: command file path
 *
 * Return: void
 */

void excute(char *commandpath, char **command)
{
	pid_t child_pid;
	int status = 0;

	child_pid = fork();

	if (child_pid < 0)
	{
		print_string("fork faild");
		exit(0);
	}

	else if (child_pid == 0)
	{
		if (execve(commandpath, command, environ) == -1)
		{
			print_string("execve error\n");
		}
	}

	else
	{
		wait(&status);
	}

}

