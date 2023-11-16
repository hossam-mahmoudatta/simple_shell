#include "main.h"


/**
 * _strlen - Entry point
 * @s: string checked
 * Return: the length of a string.
 */
int _strlen(const char *s)
{
	int lent;

	if (s == NULL)
		return (-1);

	lent = 0;
	while (s[lent] != '\0')
		lent++;
	return (lent);
}

/**
 * _strcmp - Entry point
 * @s1: pointer variable 1
 * @s2: pointer variable 2
 * Return: result of two strings compared
 */
int _strcmp(const char *s1, const char *s2)
{
	const char *p1 = s1;
	const char *p2 = s2;
	int i = 0;

	if (p1 == NULL && p2 == NULL)
		return (0);
	else if (p1 == NULL)
		return (-1);
	else if (p2 == NULL)
		return (1);

	while (*(p1 + i) != '\0' && *(p2 + i) != '\0' && p1[i] == p2[i])
	{
		i++;
	}
	return (p1[i] - p2[i]);
}

/**
 * _strchr - Entry point
 * @s: pointer variable
 * @c: character to be checked
 * Return: Always 0 (Success)
 */
char *_strchr(const char *s, const char c)
{
	const char *p = s;
	const char *pp = &c;
	int i;

	for (i = 0; *(p + i) != '\0'; i++)

		if (*(p + i) == *pp)
		{
			return ((char *)(s + i));
		}

	return (0);
}

/**
 * _strdup - Entry point
 * @str: string to duplicate
 * Return: Always 0 (Success)
 */
char *_strdup(const char *str)
{
	int i, len = 0;
	char *r_value;

	if (str == NULL)
		return (NULL);

	for (; str[len] != '\0'; len++)
		;

	r_value = malloc(sizeof(char) * (len + 1));
	if (r_value == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		r_value[i] = str[i];

	return (r_value);
}

/**
 * _strncmp - Entry point
 * @s1: 1st string to compare
 * @s2: 2nd string to compare
 * @n: Maximum number of characters to compare
 * Return: Always 0 (Success)
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char p1, p2;
	size_t i;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	for (i = 0; i < n; i++)
	{
		p1 = (unsigned char)s1[i];
		p2 = (unsigned char)s2[i];

		if (p1 != p2)
			return (p1 - p2);
		if (p1 == '\0')
			break;
	}

	return (0);
}
