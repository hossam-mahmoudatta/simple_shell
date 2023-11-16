#include "shell.h"



/**
 * clear_voidInfo - initializes info_t struct
 * @info: struct address
 */
void clear_voidInfo(info_t *info)
{
	info->argument = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_voidInfo - initializes info_t struct
 * @info: struct address
 * @argVector: argument vector
 */
void set_voidInfo(info_t *info, char **argVector)
{
	int i = 0;

	info->fileName = argVector[0];
	if (info->argument)
	{
		info->argv = strtow(info->argument, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->argument);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAlias(info);
		replaceVars(info);
	}
}

/**
 * free_voidInfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_voidInfo(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmdBuffer)
			free(info->argument);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmdBuffer);
		if (info->readFD > 2)
			close(info->readFD);
		_putchar(BUFFER_FLUSH);
	}
}
