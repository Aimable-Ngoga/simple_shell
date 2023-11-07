#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of the stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for file opening*/

/************* MACROS **************/

#include "macros.h" /* for message help and prompt */

/************* STRUCTURES **************/

/**
 * struct program_info - structure for holding program data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read by _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of executed commands
 * @file_descriptor: file descriptor for input commands
 * @tokens: pointer to an array of tokenized input
 * @env: copy of the environment
 * @alias_list: array of pointers with aliases
 */
typedef struct program_info
{
    char *program_name;
    char *input_line;
    char *command_name;
    int exec_counter;
    int file_descriptor;
    char **tokens;
    char **env;
    char **alias_list;
} program_data;

/**
 * struct builtins - structure for built-in commands
 * @builtin: the name of the built-in
 * @function: the associated function to execute the built-in
 */
typedef struct builtins
{
    char *builtin;
    int (*function)(program_data *data);
} builtins;

/************* MAIN FUNCTIONS *************/

/*========  _shell.c  ========*/

/* Initializes the struct with program information */
void init_program_data(program_data *data, int argc, char *argv[], char **env);

/* Enters the infinite loop to display the prompt */
void start_infinite_loop(char *prompt, program_data *data);

/* Print the prompt on a new line */
void handle_eof(int operation UNUSED);

/*========  _getline.c  ========*/

/* Read one line from the standard input */
int get_input_line(program_data *data);

/* Split the input into separate commands if logical operators exist */
int split_logical_operators(char *command_array[], int i, char operator_array[]);

/*======== _expand.c ========*/

/* Expand variables */
void expand_variables(program_data *data);

/* Expand aliases */
void expand_alias(program_data *data);

/* Append a string to the end of the buffer */
int add_to_buffer(char *buffer, char *string_to_add);

/*======== _strtok.c ========*/

/* Split the string into tokens using a specified delimiter */
void tokenize(program_data *data);

/* Create a pointer to a part of a string */
char *_strtok(char *line, char *delimiter);

/*======== _exec.c ========*/

/* Execute a command with its full path */
int execute_command(program_data *data);

/*======== _lists.c ========*/

/* If a match is found for a built-in, execute it */
int execute_builtins(program_data *data);

/*======== _pathfinder.c ========*/

/* Create an array of path directories */
char **tokenize_path(program_data *data);

/* Search for a program in the PATH directories */
int find_program(program_data *data);

/************** MEMORY MANAGEMENT HELPERS **************/

/*======== _frees.c ========*/

/* Free the memory for directories */
void free_pointer_array(char **directories);

/* Free the fields needed for each loop */
void free_recurring_data(program_data *data);

/* Free all fields of the program data */
void free_all_data(program_data *data);

/************** BUILT-IN COMMANDS **************/

/*======== _more.c ========*/

/* Exit the shell */
int exit_shell(program_data *data);

/* Change the current directory */
int change_directory(program_data *data);

/* Set the working directory */
int set_working_directory(program_data *data, char *new_directory);

/* Display help information */
int show_help(program_data *data);

/* Set, unset, and display aliases */
int manage_alias(program_data *data);

/*======== _env.c ========*/

/* Show the environment in which the shell is running */
int display_environment(program_data *data);

/* Create or override an environment variable */
int set_environment_variable(program_data *data);

/* Delete an environment variable */
int unset_environment_variable(program_data *data);

/************** ENVIRONMENT VARIABLES MANAGEMENT HELPERS **************/

/*======== envmgt.c ========*/

/* Get the value of an environment variable */
char *get_environment_variable(char *name, program_data *data);

/* Overwrite the value of an environment variable */
int set_environment_variable(char *key, char *value, program_data *data);

/* Remove a key from the environment */
int remove_environment_variable(char *key, program_data *data);

/* Print the current environment */
void print_environment(program_data *data);

/************** PRINTING HELPERS **************/

/*======== _printers.c ========*/

/* Print a string

