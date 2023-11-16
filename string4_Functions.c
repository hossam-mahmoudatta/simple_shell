#include "shell.h"



/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @string: the input string
 * @delimiter: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *string, char *delimiter)
{
	int i, j, k, m, numWords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	for (i = 0; string[i] != '\0'; i++)
		if (!is_delimiter(string[i], delimiter) && (is_delimiter(string[i + 1], delimiter) || !string[i + 1]))
			numWords++;

	if (numWords == 0)
		return (NULL);
	s = malloc((1 + numWords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (is_delimiter(string[i], delimiter))
			i++;
		k = 0;
		while (!is_delimiter(string[i + k], delimiter) && string[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * strtow2 - splits a string into words
 * @string: the input string
 * @delimiter: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *string, char delimiter)
{
	int i, j, k, m, numWords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (i = 0; string[i] != '\0'; i++)
		if ((string[i] != delimiter && string[i + 1] == delimiter) ||
		    (string[i] != delimiter && !string[i + 1]) || string[i + 1] == delimiter)
			numWords++;
	if (numWords == 0)
		return (NULL);
	s = malloc((1 + numWords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (string[i] == delimiter && string[i] != delimiter)
			i++;
		k = 0;
		while (string[i + k] != delimiter && string[i + k] && string[i + k] != delimiter)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
