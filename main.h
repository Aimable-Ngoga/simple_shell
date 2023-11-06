#ifndef MAIN_H
#define MAIN_H

extern char **environ;

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int print_string(char *string);
void excute(char *commandpath, char **command);
char *getpath(char *command);
int builts_check(char **command);
void environment(void);
void change_directory(char **command);
char *_getenv(char *key);

#endif
