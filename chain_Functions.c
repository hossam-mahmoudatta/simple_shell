#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int isChain(info_t *info, char *buffer, size_t *p)
{
	size_t j = *p;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmdBufferType = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmdBufferType = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		info->cmdBufferType = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}



/**
 * checkChain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buffer: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @length: length of buf
 *
 * Return: Void
 */
void checkChain(info_t *info, char *buffer, size_t *p, size_t i, size_t length)
{
	size_t j = *p;

	if (info->cmdBufferType == CMD_AND)
	{
		if (info->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}
	if (info->cmdBufferType == CMD_OR)
	{
		if (!info->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}

	*p = j;
}



/**
 * replaceAlias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlias(info_t *info)
{
	int i;
	list_t *node;
	char *string;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		string = _strchr(node->string, '=');
		if (!string)
			return (0);
		string = _strdup(string + 1);
		if (!string)
			return (0);
		info->argv[0] = string;
	}
	return (1);
}

/**
 * replaceVars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]),
				_strdup(convert_charNumber(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]),
				_strdup(convert_charNumber(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]),
				_strdup(_strchr(node->string, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replaceString - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
