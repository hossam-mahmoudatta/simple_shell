#include "shell.h"



/**
 * bfree_Pointer - frees a pointer and NULLs the address
 * @pointer: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree_Pointer(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
