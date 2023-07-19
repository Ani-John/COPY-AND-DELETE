#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
/**
 * is_at_delimeter - checks if a pointer is pointing at at a delimeter value
 * @p: the pointer
 * @d: a pointer to a string of given delimeter value(s)
 * Return: 1 if p is pointing at at a delimeter value, else 0. Returns -1 on error
 */
int is_at_delimeter (char *p, const char *d)
{
	int i = 0;
	
	if (p != NULL && d != NULL)
	{
		while (d[i])
		{
			if (*p == *(d + i))
				return (1);
			i++;
		}
	}
	
	return (0);
}

/**
 * _strtok -  breaks  a string into a sequence of zero
 * or more nonempty tokens.
 *
 * @str: the string to be broken inot tokens
 * @delim: an argument specifyinh a set of bytes that
 * delimit the tokens in the parsed string.
 *
 * Return:  a pointer to the next token, or NULL if
 * there are no more tokens.
 */

char *_strtok(char *str, const char *delim)
{
	int i = 0;
	static char *ptr;
	char *start_of_token, *end_of_token = NULL;

	if (str != NULL)
	{
		ptr = str;
	}
	else if (ptr == NULL)
		return (NULL);

	while (is_at_delimeter(ptr, delim) == 1)
		ptr++;

	start_of_token = ptr;

	while (ptr[i])
	{
		if (is_at_delimeter(&ptr[i], delim) == 1)
		{
			*(ptr + i) = '\0';
			end_of_token = (ptr + i + 1);
			break;
		}
		i++;
	}

	ptr = end_of_token;
	return (start_of_token);
}
