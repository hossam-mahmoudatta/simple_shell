#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

char *_strtok(char *line, char *delim);
int envi(data_of_program *data);
int envi(data_of_program *data);
int built_unset_env(data_of_program *data);
int getline(data_of_program *data);

#endif
