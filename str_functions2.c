#include "main.h"


/**
 * _strcat - Entry point
 * @destination: pointer variable 1
 * @source: pointer variable 2
 * Return: two strings concatenated)
 */
char *_strcat(char *destination, const char *source)
{
	char *p = destination;

	while (*p)
	{
		p++;
	}
	if (source)
	{
		while (*source)
		{
			*p++ = *source++;
		}
	}
	*p = '\0';

	return (destination);
}


/**
 * _strcpy - Entry point
 * @destination: pointer variable 1
 * @source: pointer variable 2
 * Return: pointer to dest
 */
char *_strcpy(char *destination, const char *source)
{
	char *p;

	while (*source == ' ')
	{
		source++;
	}

	p = destination;
	while (*source)
	{
		*p++ = *source++;
	}

	while (p > destination && *(p - 1) == ' ')
	{
		p--;
	}

	*p = '\0';

	return (destination);
}
