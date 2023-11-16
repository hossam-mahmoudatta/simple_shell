#include "shell.h"

/**
 * _myHistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myHistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unsetAlias - sets alias to string
 * @info: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetAlias(info_t *info, char *string)
{
	char *p, c;
	int ret;

	p = _strchr(string, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, string, -1)));
	*p = c;
	return (ret);
}

/**
 * setAlias - sets alias to string
 * @info: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setAlias(info_t *info, char *string)
{
	char *p;

	p = _strchr(string, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetAlias(info, string));

	unsetAlias(info, string);
	return (add_node_end(&(info->alias), string, 0) == NULL);
}

/**
 * printAlias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printAlias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->string, '=');
		for (a = node->string; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myAlias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myAlias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			setAlias(info, info->argv[i]);
		else
			printAlias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
