#include "shell.h"



/**
 * list_Length - determines length of linked list
 * @HeadPTR: pointer to first node
 *
 * Return: size of list
 */
size_t list_Length(const list_t *HeadPTR)
{
	size_t i = 0;

	while (h)
	{
		HeadPTR = HeadPTR->next;
		i++;
	}
	return (i);
}



/**
 * list_to_Strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_Strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_Length(head), j;
	char **strings;
	char *str;

	if (!head || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->string) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->string);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}



/**
 * print_List - prints all elements of a list_t linked list
 * @HeadPTR: pointer to first node
 *
 * Return: size of list
 */
size_t print_List(const list_t *HeadPTR)
{
	size_t i = 0;

	while (HeadPTR)
	{
		_puts(convert_number(HeadPTR->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(HeadPTR->string ? HeadPTR->string : "(nil)");
		_puts("\n");
		HeadPTR = HeadPTR->next;
		i++;
	}
	return (i);
}



/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->string, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}



/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
size_t get_node_index(list_t *head, list_t *node)
{
	size_t counter = 0;

	while (head)
	{
		if (head == node)
			return (counter);
		head = head->next;
		counter++;
	}
	return (-1);
}
