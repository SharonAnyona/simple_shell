#include "main.h"

/**
 * bfree - It frees a pointer & NULLs the address
 * @ptr: It is the  Address of the pointer to free
 *
 * Return: Give  1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
