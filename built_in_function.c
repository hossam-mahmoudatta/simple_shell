#include "main.h"
/**
 * built_ins - Entry point
 * @args: command and arguments
 * @line_num: execution count
 * Return: Always 0 (Success)
 */
int built_ins(char **args, int line_num)
{
	if (args[0] == NULL)
		return (1);

	if (_strcmp(args[0], "exit") == 0)
	{
		my_exit(args);
		exit(2);
	}
	if (_strcmp(args[0], "env") == 0)
	{
		my_env();
		return (1);
	}
	if (_strcmp(args[0], "cd") == 0)
	{
		my_cd(args, line_num);
		return (1);
	}
	if (_strcmp(args[0], "setenv") == 0)
	{
		my_setenv(args[1], args[2], 1);
		return (1);
	}
	if (_strcmp(args[0], "unsetenv") == 0)
	{
		my_unsetenv(args);
		return (1);
	}
	return (0);
}
/**
 * built_ins2 - Entry point
 * @args: command and arguments
 * @line_num: execution count
 * Return: Always 0 (Success)
 */
int built_ins2(char **args, int line_num __attribute__ ((unused)))
{
	if (_strcmp(args[0], "alias") == 0)
	{
		my_alias(args);
		return (1);
	}
	if (_strcmp(args[0], "echo") == 0)
	{
		my_echo(args);
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}

	return (0);
}
