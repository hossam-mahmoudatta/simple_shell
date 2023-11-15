#include "shell.h"



/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
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
		if (!is_delim(string[i], delimiter) && (is_delim(string[i + 1], delimiter) || !string[i + 1]))
			numWords++;

	if (numWords == 0)
		return (NULL);
	s = malloc((1 + numWords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (is_delim(string[i], delimiter))
			i++;
		k = 0;
		while (!is_delim(string[i + k], delimiter) && string[i + k])
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
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *string, char delimiter)
{
	int i, j, k, m, numWords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (i = 0; string[i] != '\0'; i++)
		if ((string[i] != d && string[i + 1] == d) ||
		    (string[i] != d && !string[i + 1]) || string[i + 1] == d)
			numWords++;
	if (numWords == 0)
		return (NULL);
	s = malloc((1 + numWords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (string[i] == d && string[i] != d)
			i++;
		k = 0;
		while (string[i + k] != d && string[i + k] && string[i + k] != d)
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
