#include "shell.h"
/**
 * _strtok - separates strings with delimiters
 * @line: pointer to array we receive in getline.
 * @del: characters we mark off string in parts.
 * Return: A pointer to the created token
*/
char *_strtok(char *line, char *del)
{
	int i;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (i = 0; del[i] != '\0'; i++)
		{
			if (*str == del[i])
			break;
		}
		if (del[i] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (i = 0; del[i] != '\0'; i++)
		{
			if (*str == del[i])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
