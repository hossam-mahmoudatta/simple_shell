#include "shell.h"



/**
 * input_Buffer - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of len var
 *
 * Return: bytes read
 */
size_t input_Buffer(info_t *info, char **buffer, size_t *length)
{
	size_t r = 0;
	size_t length_P = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigint_voidHandler);
#if USE_GETLINE
		r = getline(buffer, &length_P, stdin);
#else
		r = _getline(info, buffer, &length_P);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->lineCount_Flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->historyCounter++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*length = r;
				info->cmdBuffer = buffer;
			}
		}
	}
	return (r);
}



/**
 * get_Input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
size_t get_Input(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, length;
	size_t r = 0;
	char **buffer_PTR = &(info->argument), *p;

	_putchar(BUFFER_FLUSH);
	r = input_Buffer(info, &buffer, &length);
	if (r == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain buffer */
	{
		j = i; /* initialize new iterator to current buffer position */
		p = buffer + i; /* get pointer for return */

		checkChain(info, buffer, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (isChain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= length) /* reached end of buffer? */
		{
			i = length = 0; /* reset position and length */
			info->cmdBufferType = CMD_NORMAL;
		}

		*buffer_PTR = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buffer_PTR = buffer; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}



/**
 * read_Buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @counter: size
 *
 * Return: r
 */
size_t read_Buffer(info_t *info, char *buffer, size_t *counter)
{
	size_t reader = 0;

	if (*counter)
		return (0);
	reader = read(info->readFD, buffer, READ_BUFFER_SIZE);
	if (reader >= 0)
		*counter = reader;
	return (reader);
}



/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @pointer: address of pointer to buffer, preallocated or NULL
 * @size_Length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **pointer, size_t *size_Length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t i, length;
	size_t k;
	size_t r = 0, s = 0;
	char *ptr = NULL, *new_ptr = NULL, *c;

	ptr = *pointer;
	if (ptr && size_Length)
		s = *size_Length;
	if (i == length)
		i = length = 0;

	r = read_Buffer(info, buffer, &length);
	if (r == -1 || (r == 0 && length == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_ptr = _realloc(ptr, s, s ? s + k : k + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (ptr ? free(ptr), -1 : -1);

	if (s)
		_strncat(new_ptr, buffer + i, k - i);
	else
		_strncpy(new_ptr, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	ptr = new_ptr;

	if (size_Length)
		*size_Length = s;
	*pointer = ptr;
	return (s);
}



/**
 * sigint_voidHandler - blocks ctrl-C
 * @signal_Number: the signal number
 *
 * Return: void
 */
void sigint_voidHandler(__attribute__((unused))int signal_Number)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
