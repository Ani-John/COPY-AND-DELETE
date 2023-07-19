#include <stdio.h>
#include <stdlib.h>
#include "main.h"
/**
 * _getline - reads  an  entire  line  from stream,
 * storing the address of the buffer containing the text
 * into *lineptr.
 * @lineptr:  a 2d pointer to storing address after
 * reading.
 * @n: length of bytes to be read on the line.
 * @stream: the file to be read from
 * Return: 1 is success, -1 if failed.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{

	ssize_t len = 128;
	int c = 0;
	ssize_t count = 0, i = 0;

	if (n == NULL || lineptr == NULL || !stream)
	{
		errno = INVALID;
		return (-1);
	}
	if ((*lineptr == NULL && *n == 0))
	{
		*lineptr = realloc(*lineptr, len);
		if (*lineptr == NULL)
		{
			errno = ENOMEM;
			return (-1);
		}
		*n = 128;
	}

	c = getc(stream);
	while (c != EOF)
	{
		count += 1;
		if (c == '\n')
			break;
		if (count <= 1)
		{
			*lineptr = realloc(*lineptr, len);
			if (*lineptr == NULL)
			{
				errno = ENOMEM;
				return (-1);
			}
			*n = 128;
		}

		(*lineptr)[i++] = c;
		c = getc(stream);
	}
	if (c == '\n')
		(*lineptr)[i++] = '\n';
	(*lineptr)[i] = '\0';

	if (c == EOF && i == 0)
		return (-1);
	return (count);
}
