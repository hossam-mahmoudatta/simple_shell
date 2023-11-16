#ifndef MAIN_H
#define MAIN_H
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

/* standard library functions */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <ctype.h>

/** Global environment */
extern char **environ;
extern int exit_status;


/** MACROS **/
#define MAXARGS 128
#define MAX_PATH_LENGTH 256



/**
 * struct linked_path - This is a linked list containing
 * ---------------------Each diretory in the path
 * @dir: This is a directory Path
 * @next: is apointer to the next directory
 */
typedef struct linked_path
{
	char *dir;
	struct linked_path *next;
} linked_path;

/**
 * struct alias - This is a linked list containing
 * ---------------------Each diretory in the path
 *
 * @main_command: is the main command
 * @new_command: is a new command
 * @next: is a pointer to the next alias
 */
typedef struct alias
{
	char *main_command;
	char *new_command;
	struct alias *next;
} alias;
extern alias *alias_list;

/* memory freeing functions */
void _freeenv(void);
void  _freeargs(char **args);
void _freepath(linked_path *path);

/** alias handler functions */
int my_alias(char **args);
int create_keyvalue_pair(alias **alias_list, char *args, char *equals);
alias *add_alias(alias **head, char *neww, char *main);
int print_alias_list(alias *head);
char *check_alias(char *neww);
int execute_alias(char *main, char **args);
alias *get_alias_list(void);

/** environ functions */
int my_setenv(const char *name, const char *value, int overwrite);
int my_env(void);
int check_path(char **args);
char *_getenv(const char *name);
char *get_dir();
int my_unsetenv(char **args);
linked_path *link_path(void);

/** execute functions */
int execute(char *command, int line_num);
int execute_with_path(char **args);
ssize_t get_line(char **buffer, size_t *bufsize, int fd);
int my_cd(char **args, int line_num);
int my_echo(char **args);
int run_child(char **args);
int run_parent(void);
int exit_stat(void);

/** string / parsing functions */
char *str_tok(char *command, const char *delim);
int tokenize(char *command, char **args);
int built_ins(char **args, int line_num);
int built_ins2(char **args, int line_num);
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
char *_strchr(const char *s, const char c);
char *_strdup(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
void print_error(const char *cmd, const char *msg, int line_num);
char *_itoa(int value);
char *cd_error(char **args);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
int echo_ppid(int printed_chars);
int echo_exit(int printed_chars);
int echo_env(int printed_chars, char **args, int i);
void not_buff(void);
int my_exit(char **args);


#endif /* MAIN_H */
