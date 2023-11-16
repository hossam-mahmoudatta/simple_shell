#include "main.h"


/**
 * _strlen - Entry point
 * @s: string checked
 * Return: the length of a string.
 */
int _strlen(const char *s)
{
	int str_Length;

	if (s == NULL)
		return (-1);

	str_Length = 0;
	while (s[str_Length] != '\0')
		str_Length++;
	return (str_Length);
}

/**
 * _strcmp - Entry point
 * @s1: pointer variable 1
 * @s2: pointer variable 2
 * Return: result of two strings compared
 */
int _strcmp(const char *s1, const char *s2)
{
	const char *ptr1 = s1;
	const char *ptr2 = s2;
	int i = 0;

	if (ptr1 == NULL && ptr2 == NULL)
		return (0);
	else if (ptr1 == NULL)
		return (-1);
	else if (ptr2 == NULL)
		return (1);

	while (*(ptr1 + i) != '\0' && *(ptr2 + i) != '\0' && ptr1[i] == ptr2[i])
	{
		i++;
	}
	return (ptr1[i] - ptr2[i]);
}

/**
 * _strchr - Entry point
 * @s: pointer variable
 * @c: character to be checked
 * Return: Always 0 (Success)
 */
char *_strchr(const char *s, const char c)
{
	const char *ptr1 = s;
	const char *ptr2 = &c;
	int i;

	for (i = 0; *(ptr1 + i) != '\0'; i++)

		if (*(ptr1 + i) == *ptr2)
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
	int i, str_Length = 0;
	char *r_value;

	if (str == NULL)
		return (NULL);

	for (; str[str_Length] != '\0'; str_Length++)
		;

	r_value = malloc(sizeof(char) * (str_Length + 1));
	if (r_value == NULL)
		return (NULL);

	for (i = 0; i <= str_Length; i++)
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
	unsigned char ptr1, ptr2;
	size_t counter;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	for (counter = 0; counter < n; counter++)
	{
		ptr1 = (unsigned char)s1[i];
		ptr2 = (unsigned char)s2[i];

		if (ptr1 != ptr2)
			return (ptr1 - ptr2);
		if (ptr1 == '\0')
			break;
	}

	return (0);
}
