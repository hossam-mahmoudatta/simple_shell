#include "shell.h"



/**
 * _strtoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _strtoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}



/**
 * print_voidError - prints an error message
 * @info: the parameter & return info struct
 * @errorString: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_voidError(info_t *info, char *errorString)
{
	_inputPuts(info->fileName);
	_inputPuts(": ");
	print_d(info->lineCount, STDERR_FILENO);
	_inputPuts(": ");
	_inputPuts(info->argv[0]);
	_inputPuts(": ");
	_inputPuts(errorString);
}



/**
 * print_intDecimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fileDescripter: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_intDecimal(int input, int fileDescripter)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fileDescripter == STDERR_FILENO)
		__putchar = _inputPutChar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}



/**
 * convert_charNumber - converter function, a clone of itoa
 * @number: number
 * @base: base
 * @argFlags: argument flags
 *
 * Return: string
 */
char *convert_charNumber(long int number, int base, int argFlags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(argFlags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';

	}
	array = argFlags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}



/**
 * remove_voidComments - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_voidComments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}
