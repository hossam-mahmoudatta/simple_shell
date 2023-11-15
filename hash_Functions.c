#include "shell.h"



/**
 * mainShell - main shell loop
 * @info: the parameter & return info struct
 * @argVector: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int mainShell(info_t *info, char **argVector)
{
	size_t variable1 = 0;
	int builtin_ret = 0;

	while (variable1 != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		variable1 = get_input(info);
		if (variable1 != -1)
		{
			set_info(info, argVector);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}