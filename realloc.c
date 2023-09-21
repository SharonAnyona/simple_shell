#include "main.h"

/**
 **_memset - used to fill costant byte to memory 
 *@s: denotes the memory pointer
 *@b: denotes the byte to fill *s with
 *@n: denotes the amount of fulled bytes
 *Return: Give  (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Empties a string of strings
 * @pp: is a string of strings 
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - A block of memory reallocater
 * @ptr:  malloc'ated previous block pointer
 * @old_size: previous block byte size
 * @new_size: new block byte size
 *
 * Return: Give pointer to the  ol'block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
