#include "main.h"
/**
 * check_alias - is a function that check if an alias exist
 * @neww: is a list of arguments
 * Return: Name of alias if success or NULL if not
 */
char *check_alias(char *neww)
{
	alias *temp = get_alias_list();

	while (temp != NULL)
	{
		if (_strcmp(neww, temp->new_command) == 0)
		{
			return (temp->new_command);
		}
		temp = temp->next;
	}
	return (NULL);
}
/**
 * execute_alias - is a function that check if an alias exist
 * @args: is a list of arguments
 * @main: is the value
 * Return: Name of alias if success or NULL if not
 */
int execute_alias(char *main, char **args)
{
	if (execve(main, args, environ) == -1)
	{
		fprintf(stderr, "%s: No such file or directory\n", args[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}
/**
 * create_keyvalue_pair - is a function that creates an alias
 * @name: is the the argument to be initialized into the name_command
 * @alias_list: is a pointer to the alias list
 * @equals: is a pointer to the '=' in the args
 * Return: the new node
 */
int create_keyvalue_pair(alias **alias_list, char *name, char *equals)
{
	alias *list_copy = *alias_list;
	int i, b = 0, j,  value_length;
	char *main_command, *new_command = malloc((strlen(name) + 1) * sizeof(char));

	while (name[b] != '=')
	{
		new_command[b] = name[b];
		b++;
	}

	*equals = '\0';
	equals = equals + 1;

	printf("now allocating memory for value_command equals = %s\n", equals);
	value_length = strlen(equals) - strspn(equals, "'\"");
	main_command = malloc(sizeof(char) * (value_length + 1));

	printf("now entering initialization loop\n");
	for (i = 0, j = 0; equals[i] != '\0'; i++)
	{
		if (equals[i] != '\'' && equals[i] != '"')
		{
			main_command[j] = equals[i];
			j++;
		}
	}
	main_command[j] = '\0';

	printf("before add name = %s and value = %s\n", new_command, main_command);
	*alias_list = add_alias(&list_copy, new_command, main_command);

	return (0);
}
/**
 * add_alias - is a function that adds an alias to the list
 * @new: is the name of the new command
 * @main: is the name fo the main command
 * @head: is a pointer to a list of aliases
 * Return: the head of the list
 */
alias *add_alias(alias **head, char *new, char *main)
{
	alias *new_node = NULL;
	alias *temp;

	new_node->main_command = malloc(sizeof(char) * 50);
	new_node->new_command = malloc(sizeof(char) * 50);

	new_node->main_command = strdup(main);
	new_node->new_command = strdup(new);
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			if (strcmp(new, temp->new_command) == 0)
			{
				free(temp->main_command);
				temp->main_command = strdup(main);
				free(new_node->main_command);
				free(new_node->new_command);
				return (*head);
			}
			temp = temp->next;
		}
		temp->next = new_node;
	}
	printf("added alias to list successfully\n");

	while (temp != NULL)
	{
		printf("alias is %s='%s'\n", temp->new_command, temp->main_command);
		temp = temp->next;
	}
	return (*head);
}
/**
 * print_alias_list - is a function that prints out the alias list
 * @head: is a pointer to a list of aliases
 * Return: void
 */
int print_alias_list(alias *head)
{
	alias *temp = head;

	while (temp != NULL)
	{
		printf("alias %s=\'%s\'\n", temp->new_command, temp->main_command);
		temp = temp->next;
	}
	printf("print list successfully\n");

	return (0);
}
