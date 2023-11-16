#include "main.h"

/**
 * str_tok - Entry point
 * @command: command line
 * @delim: delimieter
 * Return: current token
 */
char *str_tok(char *command, const char *delim)
{
	static char *last_token;
	char *current_token;

	if (command != NULL)
		last_token = command;

	if (last_token == NULL || *last_token == '\0')
		return (NULL);

	current_token = last_token;
	while (*current_token != '\0' && _strchr(delim, *current_token) != NULL)
		current_token++;

	if (*current_token == '\0')
	{
		last_token = NULL;
		return (NULL);
	}

	last_token = current_token;
	while (*last_token != '\0' && _strchr(delim, *last_token) == NULL)
		last_token++;

	if (*last_token != '\0')
	{
		*last_token = '\0';
		last_token++;
	}

	return (current_token);
}

/**
 * tokenize - Entry point
 * @command: string passed
 * @args: arguments passed
 * Return: Always 0 (Success)
 */
int tokenize(char *command, char **args)
{
	int i = 0;
	char *token = str_tok(command, " \n\t\r\a");
	char *trimmed_token;

	while (token != NULL && i < MAXARGS - 1)
	{
		trimmed_token = token;
		while (*trimmed_token == ' ')
		{
			trimmed_token++;
		}

		if (trimmed_token[0] == '#')
		{
			break;
		}

		if (*trimmed_token != '\0')
		{
			args[i++] = trimmed_token;
		}

		token = str_tok(NULL, " \n\t\r\a");
	}
	return (i);
}
