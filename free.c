#include "main.h"
/**
 * _freeargs - is a function that frees the arguments
 * @args: this is the tokenized arguments
 * Return:void
 */
void  _freeargs(char **args)
{
	int index;
	int length = 0;

	while (args[length] != NULL)
		length++;

	for (index = 0; index < length; index++)
	{
		free(args[index]);
	}
}

/**
 * _freepath - is a function that frees the path
 * @path: is a function that frees the path
 * Return:void
 */
void _freepath(linked_path *path)
{
	linked_path *temp;

	while (temp != NULL)
	{
		temp = path->next;
		free(path->dir);
		free(path);
		path = temp;
	}
}
/**
 * _freeenv - is a function that frees the eniron
 * Return:void
 */
void _freeenv(void)
{
	int index;

	for (index = 0; environ[index] != NULL; index++)
	{
		free(environ[index]);
	}
	free(environ);
}
