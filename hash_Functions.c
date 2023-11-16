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
	ssize_t variable1 = 0;
	int builtin_ret = 0;

	while (variable1 != -1 && builtin_ret != -2)
	{
		clear_voidInfo(info);
		if (interactive(info))
			_puts("$ ");
		_inputPutChar(BUFFER_FLUSH);
		variable1 = get_Input(info);
		if (variable1 != -1)
		{
			set_voidInfo(info, argVector);
			builtin_ret = findBuiltIn(info);
			if (builtin_ret == -1)
				findCMD(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_voidInfo(info, 0);
	}
	write_intHistory(info);
	free_voidInfo(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->errorNumber == -1)
			exit(info->status);
		exit(info->errorNumber);
	}
	return (builtin_ret);
}


/**
 * findBuiltIn - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int findBuiltIn(info_t *info)
{
	int counter, builtIn_Retention = -1;

	builtIn_Table builtIn_Table_Instance[] = {
		{"exit", _shellExit},
		{"env", _myenv},
		{"help", _myHelp},
		{"history", _myHistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _shellCD},
		{"alias", _myAlias},
		{NULL, NULL}
	};

	for (counter = 0; builtIn_Table_Instance[counter].type; counter++)
		if (_strcmp(info->argv[0], builtIn_Table_Instance[counter].type) == 0)
		{
			info->lineCount++;
			builtIn_Retention = builtIn_Table_Instance[counter].functionPTR(info);
			break;
		}
	return (builtIn_Retention);
}


/**
 * findCMD - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void  findCMD(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->lineCount_Flag == 1)
	{
		info->lineCount++;
		info->lineCount_Flag = 0;
	}
	for (i = 0, k = 0; info->argument[i]; i++)
		if (!is_delimiter(info->argument[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findPath(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkCMD(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && isCMD(info, info->argv[0]))
			forkCMD(info);
		else if (*(info->argument) != '\n')
		{
			info->status = 127;
			print_voidError(info, "not found\n");
		}
	}
}

/**
 * forkCMD - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forkCMD(info_t *info)
{
	pid_t childPID;

	childPID = fork();
	if (childPID == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (childPID == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_voidInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_voidError(info, "Permission denied\n");
		}
	}
}
