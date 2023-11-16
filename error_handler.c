#include "main.h"

/**
 * print_error - Entry point
 * @cmd: first argument
 * @msg: error message
 * @line_num: to track error
 * Return: Always 0 (Success)
 */
void print_error(const char *cmd, const char *msg, int line_num)
{
	const char *shell_name = "hsh";
	const char *separator = ": ";
	char line_number_str[16];
	unsigned long int i = 0;
	int j, n = line_num;
	size_t shell_name_len = _strlen(shell_name);
	size_t separator_len = _strlen(separator);

	write(STDERR_FILENO, shell_name, shell_name_len);
	write(STDERR_FILENO, separator, separator_len);

	if (n == 0)
	{
		line_number_str[i++] = '0';
	}
	else
	{
		while (n > 0 && i < sizeof(line_number_str) - 1)
		{
			line_number_str[i++] = '0' + (n % 10);
			n /= 10;
		}
	}
	for (j = i - 1; j >= 0; j--)
	{
		write(STDERR_FILENO, &line_number_str[j], 1);
	}

	write(STDERR_FILENO, separator, separator_len);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, separator, separator_len);
	write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}


/**
 * cd_error - Entry point
 * @args: arguments
 * Return: Always 0 (Success)
 */
char *cd_error(char **args)
{
	char *error_message = (char *)malloc(100 * sizeof(char));

	if (error_message == NULL)
	{
		return (NULL);
	}

	_strcpy(error_message, "can't ");
	_strcat(error_message, " ");
	_strcat(error_message, args[0]);
	_strcat(error_message, " to ");
	_strcat(error_message, args[1]);

	return (error_message);
}
