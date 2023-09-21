#include "main.h"

/**
 * _strlen - used to return string length
 * @s: lenght of string to be checked 
 *
 * Return: strings length integer 
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
/**
 * starts_with - examines if needle starts with haystack
 * @haystack: search string
 * @needle: substring to be found
 *
 * Return: haystack or NULL next char address
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcmp - Perform two strings lexicogarphic comparison.
 * @s1: is the first string
 * @s2: is the second strang
 *
 * Return: gives positive if s1 > s2,negative if s1 < s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strcat - two strings concatinater 
 * @dest: buffer destination
 * @src: buffer source
 *
 * Return: give destination buffer pointer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
