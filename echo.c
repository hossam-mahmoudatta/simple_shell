#include "main.h"

/**
 * _itoa - Entry point
 * @value: integer to be converted
 * Return: string converted from integer
 */
char *_itoa(int value)
{
	int i, len = 0;
	int temp = value;
	char *str = (char *)malloc((len + 1) * sizeof(char));

	while (temp != 0)
	{
		len++;
		temp /= 10;
	}

	if (value == 0)
	{
		len = 1;
	}

	if (str == NULL)
	{
		return (NULL);
	}

	for (i = len - 1; i >= 0; i--)
	{
		str[i] = '0' + (value % 10);
		value /= 10;
	}

	str[len] = '\0';

	return (str);
}

/**
 * my_echo - Entry point
 * @args: command and arguments
 * Return: Always 0 (Success)
 */
int my_echo(char **args)
{
	int i, len;
	int printed_chars = 0;

	for (i = 1; args[i] != NULL && i < MAXARGS - 1; i++)
	{
		if (_strcmp(args[i], "$$") == 0)
		{
			echo_ppid(printed_chars);
		}
		else if (_strcmp(args[i], "$?") == 0)
		{
			echo_exit(printed_chars);
		}
		else if (args[i][0] == '$')
		{
			echo_env(printed_chars, args, i);
		}
		else
		{
			len = _strlen(args[i]);
			printed_chars += write(STDOUT_FILENO, args[i], len);
			printed_chars += len;
		}
		if (args[i + 1] != NULL)
		{
			printed_chars += write(STDOUT_FILENO, " ", 1);
			printed_chars++;
		}
	}
	return (printed_chars);
}

/**
 * echo_ppid - Entry point
 * @printed_chars: character count
 * Return: Always 0 (Success)
 */
int echo_ppid(int printed_chars)
{
	int len;
	pid_t pid;
	char *pid_str;

			pid = getpid();
			pid_str = _itoa(pid);

			if (pid_str != NULL)
			{
				len = _strlen(pid_str);

				printed_chars += write(STDOUT_FILENO, pid_str, len);
				free(pid_str);
			}
			return (0);
}

/**
 * echo_exit - Entry point
 * @printed_chars: character count
 * Return: Always 0 (Success)
 */
int echo_exit(int printed_chars)
{

	int exit_status = exit_stat();
	char *exit_status_str = _itoa(exit_status);

	if (exit_status_str != NULL)
	{
		int len = _strlen(exit_status_str);

		printed_chars += write(STDOUT_FILENO, exit_status_str, len);
		free(exit_status_str);
	}
	return (0);
}

/**
 * echo_env - Entry point
 * @printed_chars: character count
 * @args: arguments
 * @i: iterate variable
 * Return: Always 0 (Success)
 */
int echo_env(int printed_chars, char **args, int i)
{
	int len;
	char *value;
	char *var_name;

	var_name = args[i] + 1;
	value = _getenv(var_name);

	if (value != NULL)
	{
		len = _strlen(value);
		printed_chars += write(STDOUT_FILENO, value, len);
		printed_chars += len;
	}
	else
		return (0);
	return (0);
}
