#include "main.h"
/**
 * execute_with_path - is a function that exeuctes command from the path
 * @args: is an array of tokenized commands
 * Return: The process id
 */
int execute_with_path(char **args)
{
	linked_path *temp = link_path();
	char full_Path[1024];

	while (temp != NULL)
	{
		sprintf(full_Path, "%s/%s", temp->dir, args[0]);
		if (access(full_Path, F_OK) == 0)
		{
			execve(full_Path, args, NULL);
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
	char full_Path[1024];

	while (temp != NULL)
	{
		sprintf(full_Path, "%s/%s", temp->dir, args[0]);
		if (access(full_Path, F_OK) == 0)
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
	char *direction;
	char *Path;
	char *Path_dup;
	linked_path *head;
	linked_path *current_node = (linked_path *)malloc(sizeof(linked_path));

	head = current_node;


	Path = _getenv("PATH");
	Path_dup = _strdup(Path);
	direction = str_tok(Path_dup, ":");
	current_node->dir = _strdup(direction);

	while (direction != NULL)
	{
		direction = str_tok(NULL, ":");
		if (direction != NULL)
		{
			current_node->next = (linked_path *)malloc(sizeof(linked_path));
			current_node = current_node->next;
			current_node->dir = _strdup(direction);
		}
	}
	current_node->next = NULL;

	return (head);

}
