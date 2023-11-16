#include "main.h"

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: Always 0 (Success)
 */
int main(int argc __attribute__((unused)), char **argv)
{
	bool interactive = isatty(STDIN_FILENO);
	char *shellPrompt = interactive ? "$ " : "";
	size_t n = 0;
	ssize_t line;
	int line_num = 1;
	char **cmd;

	signal(SIGINT, SIG_IGN);

	for (;;)
	{
		if (interactive)
		{
			write(STDOUT_FILENO, shellPrompt, 3);
			fflush(stdout);
		}
		line = get_line(argv, &n, STDIN_FILENO);
		if (line == -1)
		{
			if (feof(stdin))
			{
				exit(EXIT_SUCCESS);
			}
			break;
		}
		if (line == 0 || *argv[0] == '\n')
			continue;
		cmd = argv;
		while (*cmd != NULL)
		{
			execute(*cmd, line_num);
			cmd++;
		}
		_freeargs(argv);
		line_num++;
	}
	return (0);
}
