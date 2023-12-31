#include "shell.h"

/**
 * showEnvironment - Display the environment in which the shell is running.
 * @data: A structure containing program data.
 * Return: Zero on success, or a non-zero value if specified in the arguments.
 */
int showEnvironment(data_of_program *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_cpy = NULL;

	/* If there are no arguments */
	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			/* Check if there's a '=' character */
			if (data->tokens[1][i] == '=')
			{
				/* Check if there's a variable with the same name and temporarily change its value */
				var_cpy = _strdup(env_get_key(cpname, data));
				if (var_cpy != NULL)
					env_set_key(cpname, data->tokens[1] + i + 1, data);

				/* Print the environment */
				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{
					/* Print the variable if it doesn't exist in the environment */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					/* Restore the old value of the variable */
					env_set_key(cpname, var_cpy, data);
					free(var_cpy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}
/**
 * setEnvironment - ...
 * @data: The struct for the program's data
 * Return: Zero if successful, or another number if specified in the arguments
 */
int setEnvironment(data_of_program *data)
{
	/* Validate arguments */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}
/**
 * removeEnvironment - ...
 * @data: A struct containing the program's data.
 * Return: ...
 */
int removeEnvironment(data_of_program *data)
{
	/* Validate arguments */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
