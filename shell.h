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



/* hash_Functions.c Functions */
int mainShell(info_t *, char **);
int findBuiltIn(info_t *);
void findCMD(info_t *);
void forkCMD(info_t *);



/* path.c Functions*/
int isCMD(info_t *, char *);
char *duplicateCharacters(char *, int, int);
char *findPath(info_t *, char *, char *);



/* loop_Hash.c */
int loopHash(char **);



/* error_string_functions.c */
void _inputPuts(char *);
int _inputPutChar(char);
int _putFD(char c, int fileDescriptor);
int _putsFD(char *string, int fileDescriptor);



/* string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);



/* string_functions2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);



/* string_functions3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);



/* string_functions4.c */
char **strtow(char *, char *);
char **strtow2(char *, char);



/* memory_functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);



/* memory_functions2.c */
int bfree(void **);



/* more_functions.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);



/* more_functions2.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);



/* builtin_emulators.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);



/* builtin_emulators2.c */
int _myhistory(info_t *);
int _myalias(info_t *);



/* getline.c module */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);



/* info.c module */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);



/* env.c module */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);



/* env2.c module */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);



/* file_io_functions.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);



/* liststr.c module */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);



/* liststr2.c module */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);



/* chain.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);





char *strtok_s(char *line, char *delim);
int envi(data_of_program *data);
int envi(data_of_program *data);
int built_unset_env(data_of_program *data);



#endif
