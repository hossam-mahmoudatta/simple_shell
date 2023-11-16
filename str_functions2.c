#include "main.h"


/**
 * _strcat - Entry point
 * @dest: pointer variable 1
 * @src: pointer variable 2
 * Return: two strings concatenated)
 */
char *_strcat(char *dest, const char *src)
{
	char *p = dest;

	while (*p)
	{
		p++;
	}
	if (src)
	{
		while (*src)
		{
			*p++ = *src++;
		}
	}
	*p = '\0';

	return (dest);
}


/**
 * _strcpy - Entry point
 * @dest: pointer variable 1
 * @src: pointer variable 2
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	char *p;

	while (*src == ' ')
	{
		src++;
	}

	p = dest;
	while (*src)
	{
		*p++ = *src++;
	}

	while (p > dest && *(p - 1) == ' ')
	{
		p--;
	}

	*p = '\0';

	return (dest);
}
