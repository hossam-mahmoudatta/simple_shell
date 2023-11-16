#include "main.h"
/**
 * execute_with_path - is a function that exeuctes command from the path
 * @args: is an array of tokenized commands
 * Return: The process id
 */
int execute_with_path(char **args)
{
	linked_path *temp = link_path();
	char fullpath[1024];

	while (temp != NULL)
	{
		sprintf(fullpath, "%s/%s", temp->dir, args[0]);
		if (access(fullpath, F_OK) == 0)
		{
			execve(fullpath, args, NULL);
		}
		temp = temp->next;
	}
	return (-1);

}

/**
 * check_path - is a function that checks for a command in the path
 * @args: is a command
 * Return: pid
 */
int check_path(char **args)
{
	linked_path *temp = link_path();
	char fullpath[1024];

	while (temp != NULL)
	{
		sprintf(fullpath, "%s/%s", temp->dir, args[0]);
		if (access(fullpath, F_OK) == 0)
		{
			return (1);
		}
		temp = temp->next;
	}
	return (-1);
}

/**
 * link_path - is a function that creates a linked list for the path
 * Return: a pointer to the first node
 */
linked_path *link_path(void)
{
	char *dir;
	char *Path;
	char *Path_dup;
	linked_path *head;
	linked_path *current_node = (linked_path *)malloc(sizeof(linked_path));

	head = current_node;


	Path = _getenv("PATH");
	Path_dup = _strdup(Path);
	dir = str_tok(Path_dup, ":");
	current_node->dir = _strdup(dir);

	while (dir != NULL)
	{
		dir = str_tok(NULL, ":");
		if (dir != NULL)
		{
			current_node->next = (linked_path *)malloc(sizeof(linked_path));
			current_node = current_node->next;
			current_node->dir = _strdup(dir);
		}
	}
	current_node->next = NULL;

	return (head);

}
