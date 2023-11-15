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
