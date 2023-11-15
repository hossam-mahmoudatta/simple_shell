#ifndef SHELL_H
#define SHELL_H


/*******************************************************************************
 *                              						       	Include Libraries						                       	   	   *
 *******************************************************************************/

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

/*******************************************************************************
 *                              							    Types Declaration					                       		     *
 *******************************************************************************/

/* for read/write buffers */
#define READ_BUFFER_SIZE		1024
#define WRITE_BUFFER_SIZE		1024
#define BUFFER_FLUSH					-1

/* Used for command chaining */
#define CMD_NORMAL		0
#define CMD_OR					1
#define CMD_AND					2
#define CMD_CHAIN				3

/* for the function convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED		2

/* 1 if using system getline() */
#define USE_GETLINE 			0
#define USE_STRTOK 				0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **Environment;


/**
 * struct listString - singly linked list
 * @number: the number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct listString
{
	int number;
	char *string;
	struct listString *next;
} list_t;


/**
 *struct passInformation - contains pseudo-arguments to pass into a function,
 *allowing uniform prototype for function pointer struct
 *@argument: a string generated from getline containing arguments
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@lineCount: the error count
 *@errorNumber: the error code for exit()s
 *@lineCount_Flag: if on count this line of input
 *@fileName: the program filename
 *@env: linked list local copy of environ
 *@Environment: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@envChanged: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmdBuffer: address of pointer to cmd_buf, on if chaining
 *@cmdBufferType: CMD_type ||, &&, ;
 *@readFD: the fd from which to read line input
 *@historyCounter: the history line number count
 */
typedef struct passInformation
{
	char *argument;
	char **argv;
	char *path;
	int argc;
	unsigned int lineCount;
	int errorNumber;
	int lineCount_Flag;
	char *fileName;
	list_t *env;
	char **Environment;
	list_t *history;
	list_t *alias;
	int envChanged;
	int status;
	char **cmdBuffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmdBufferType; /* CMD_type ||, &&, ; */
	int readFD;
	int historyCounter;
} info_t;

/**
 *struct builtIn - contains a builtin string and related function
 *@type: the builtin command flag
 *@functionPTR: the function
 */
typedef struct builtIn
{
	char *type;
	int (*functionPTR)(info_t *);
} builtIn_Table;

char *strtok_s(char *line, char *delim);
int envi(data_of_program *data);
int envi(data_of_program *data);
int built_unset_env(data_of_program *data);



#endif
