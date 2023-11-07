#include "shell.h"

/**
 * main - Initialize program variables.
 * @argc: Number of arguments received from the command line.
 * @argv: Arguments received from the command line.
 * @env: Shell environment.
 * Return: 0 on success.
 */
int main(int argc, char *argv[], char *env[])
{
    data_of_program data_struct = {NULL}, *data = &data_struct;
    char *terminal_message = "";

    init_data(data, argc, argv, env);

    signal(SIGINT, handle_sigint);

    if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
    {
        /* We are in the terminal, in interactive mode */
        errno = 2;
        terminal_message = PROMPT;
    }
    errno = 0;
    start_prompt(terminal_message, data);
    return 0;
}

/**
 * handle_sigint - Display a newline and the prompt when the SIGINT
 * (Ctrl + C) signal is sent to the program.
 * @unused: An unused parameter in the function.
 */
void handle_sigint(int unused)
{
    _print("\n");
    _print(PROMPT);
}

/**
 * init_data - Initializes program information into the structure.
 * @data: A pointer to the data structure.
 * @argv: An array of arguments passed to the program for execution.
 * @env: An environment passed to the program for execution.
 * @argc: The number of values received from the command line.
 */
void init_data(data_of_program *data, int argc, char *argv[], char **env)
{
    int i = 0;

    data->program_name = argv[0];
    data->input_line = NULL;
    data->command_name = NULL;
    data->exec_counter = 0;

    if (argc == 1)
    {
        data->file_descriptor = STDIN_FILENO;
    }
    else
    {
        data->file_descriptor = open(argv[1], O_RDONLY);
        if (data->file_descriptor == -1)
        {
            _printe(data->program_name);
            _printe(": 0: Can't open ");
            _printe(argv[1]);
            _printe("\n");
            exit(127);
        }
    }
    data->tokens = NULL;
    data->env = malloc(sizeof(char *) * 50);

    if (env)
    {
        for (; env[i]; i++)
        {
            data->env[i] = _strdup(env[i]);
        }
    }
    data->env[i] = NULL;
    env = data->env;

    data->alias_list = malloc(sizeof(char *) * 20);
    for (i = 0; i < 20; i++)
    {
        data->alias_list[i] = NULL;
    }
}

/**
 * start_prompt - Main prompt loop.
 * @terminal_message: Message to be displayed.
 * @data: Prompt loop to display.
 */
void start_prompt(char *terminal_message, data_of_program *data)
{
    int err_code = 0, string_length = 0;

    while (++(data->exec_counter))
    {
        _print(terminal_message);
        err_code = string_length = _getline(data);

        if (err_code == EOF)
        {
            free_all_data(data);
            exit(errno);
        }

        if (string_length >= 1)
        {
            expand_alias(data);
            expand_vars(data);
            tokenize(data);
            if (data->tokens[0])
            {
                err_code = exec(data);
                if (err_code != 0)
                {
                    _print_error(err_code, data);
                }
            }
            free_recurrent_data(data);
        }
    }
}

