#include "shell.h"



/**
 * get_charHistoryFile - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */

char *get_charHistoryFile(info_t *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HISTORY_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HISTORY_FILE);
	return (buffer);
}


/**
 * write_intHistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_intHistory(info_t *info)
{
	size_t fileDelimiter;
	char *fileName = get_charHistoryFile(info);
	list_t *node = NULL;

	if (!fileName)
		return (-1);

	fileDelimiter = open(fileName, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fileName);
	if (fileDelimiter == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsFD(node->string, fileDelimiter);
		_putFD('\n', fileDelimiter);
	}
	_putFD(BUFFER_FLUSH, fileDelimiter);
	close(fileDelimiter);
	return (1);
}

/**
 * read_intHistory - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_intHistory(info_t *info)
{
	int i, last = 0, lineCount = 0;
	size_t fileDelimiter, rdLength, fSize = 0;
	struct stat standard;
	char *buffer = NULL, *file_Name = get_charHistoryFile(info);

	if (!file_Name)
		return (0);

	fileDelimiter = open(file_Name, O_RDONLY);
	free(file_Name);
	if (fileDelimiter == -1)
		return (0);
	if (!fstat(fileDelimiter, &standard))
		fSize = standard.st_size;
	if (fSize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fSize + 1));
	if (!buffer)
		return (0);
	rdLength = read(fileDelimiter, buffer, fSize);
	buffer[fSize] = 0;
	if (rdLength <= 0)
		return (free(buffer), 0);
	close(fileDelimiter);
	for (i = 0; i < fSize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_intHistoryList(info, buffer + last, lineCount++);
			last = i + 1;
		}
	if (last != i)
		build_intHistoryList(info, buffer + last, lineCount++);
	free(buffer);
	info->historyCounter = lineCount;
	while (info->historyCounter-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	reNumber_intHistory(info);
	return (info->historyCounter);
}



/**
 * build_intHistoryList - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_intHistoryList(info_t *info, char *buffer, int lineCount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, lineCount);

	if (!info->history)
		info->history = node;
	return (0);
}



/**
 * reNumber_intHistory - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int reNumber_intHistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}
	return (info->historyCounter = i);
}
