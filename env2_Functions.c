#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->envChanged)
	{
		info->environ = list_to_strings(info->env);
		info->envChanged = 0;
	}

	return (info->Environment);
}



/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @variable: the string env var property
 * 	constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t i = 0;
	char *string;

	if (!node || !variable)
		return (0);

	while (node)
	{
		string = starts_with(node->string, variable);
		if (string && *string == '=')
		{
			info->envChanged = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->envChanged);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *string;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		string = starts_with(node->string, variable);
		if (string && *string == '=')
		{
			free(node->string);
			node->string = buffer;
			info->envChanged = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->envChanged = 1;
	return (0);
}
