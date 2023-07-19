#include "main.h"
/**
 * intilize_argv_to_null - initializes argv to null
 * @argv: a pointer to array of strings
 */
void intilize_argv_to_null(char **argv)
{
	int i = 0;

	while (i < 90)
	{
		argv[i] = malloc(30 * sizeof(char));
		i++;
	}
}
