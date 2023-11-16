#include "shell.h"



/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readFD <= 2);
}

/**
 * is_delimiter - checks if character is a delimeter
 * @c: the char to check
 * @delimiter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

/**
 *_isAlpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isAlpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@string: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *string)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  string[i] != '\0' && flag != 2; i++)
	{
		if (string[i] == '-')
			sign *= -1;

		if (string[i] >= '0' && string[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (string[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
