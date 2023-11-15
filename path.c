#include "shell.h"


/**
 * isCMD - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isCMD(info_t *info, char *path)
{
	struct stat statStruct;

	(void)info;
	if (!path || stat(path, &statStruct))
		return (0);

	if (statStruct.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}



/**
 * duplicateCharacters - duplicates characters
 * @pathString: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicateCharacters(char *pathString, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathString[i] != ':')
			buffer[k++] = pathString[i];
	buffer[k] = 0;
	return (buffer);
}



/**
 * findPath - finds this cmd in the PATH string
 * @info: the info struct
 * @pathString: the PATH string
 * @CMD: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *findPath(info_t *info, char *pathString, char *CMD)
{
	int i = 0, currentPosition = 0;
	char *path;

	if (!pathString)
		return (NULL);
	if ((_strlen(CMD) > 2) && starts_with(CMD, "./"))
	{
		if (isCMD(info, CMD))
			return (CMD);
	}

	while (1)
	{
		if (!pathString[i] || pathString[i] == ':')
		{
			path = dup_chars(pathString, currentPosition, i);
			if (!*path)
				_strcat(path, CMD);
			else
			{
				_strcat(path, "/");
				_strcat(path, CMD);
			}
			if (isCMD(info, path))
				return (path);
			if (!pathString[i])
				break;
			currentPosition = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * findCMD - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findCMD(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->lineCount_Flag == 1)
	{
		info->lineCount++;
		info->lineCount_Flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
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
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
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
			free_info(info, 1);
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
				print_error(info, "Permission denied\n");
		}
	}
}