#include "shell.h"

/**
 *_inputPuts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _inputPuts(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		_inputPutChar(string[i]);
		i++;
	}
}

/**
 * _inputPutChar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _inputPutChar(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}



/**
 * _putFileDescriptor - writes the character c to given fd
 * @c: The character to print
 * @fileDescriptor: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putFileDescriptor(char c, int fileDescriptor)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fileDescriptor, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}



/**
 *_putsFD - prints an input string
 * @string: the string to be printed
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int _putsFD(char *string, int fileDescriptor)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += _putFD(*string++, fileDescriptor);
	}
	return (i);
}
