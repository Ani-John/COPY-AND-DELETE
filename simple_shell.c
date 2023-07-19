#include "main.h"

/**
 * handle_end_of_file - handles end of file condition when
 * ctrl-D is passed.
 * @buffer: a pointer to the passed command
 */
void handle_end_of_file(char *buffer)
{
	(void)(buffer);

	if (isatty(STDIN_FILENO))
	pstring("\n", 1);
	exit(0);
}

/**
 * remove_newline - copies out the string from buffer to
 * path without the newline.
 * @buffer: a pointer to the string containing newline at
 * end.
 * @path: a pointer to the the memory to be copied.
 * Return: a pointer to the copied string.
 */
char *remove_newline(char *buffer, char *path)
{
	int i = 0;

	while (i < _strlent(buffer) - 1)
	{
		*(path + i) = *(buffer + i);
		i++;
	}
	return (path);
}

/**
 * tokenized_path - breaks string into path using space as
 * delimeter.
 * @path: a pointer to the string to be tokenized
 * @argv: a pointer to an array of tokenized strings
 * Return: a pointer to the list of tokenized strings
 */
char **tokenized_path(char *path, char **argv)
{
	int j = 0;

	argv[0] = strtok(path, " ");

	while (argv[j] != NULL)
	{
		++j;
		argv[j] = strtok(NULL, " ");
	}
	return (argv);
}

/**
 * execute_command - executes a command using execve
 * @argv: a pointer to an array of tokenized strings
 * @environ: a pointer to an array of environmental
 * variables
 */
void execute_command(char **argv, char *ptr, char **environ)
{
	if (execve(argv[0], argv, environ) == -1)
		perror(ptr);
}

/**
 * main - a simple shell program that excecutes command and arguments
 * passed on the terminal
 * @ac: number of arguments passed along with the program
 * @av: an array of pointers to the passed strings of arguments
 * @env: an array of pointers to environmental list of variables
 * Return: 0 on success.
 */

int main(__attribute__((unused))int ac, char **av,
		__attribute__((unused))char **env)
{
	pid_t child_pid;
	char *path = NULL, **argv = malloc(sizeof(char *) * 90), *buffer = malloc(BUFF_SIZE);
	size_t len = BUFF_SIZE;
	int status;
	bool from_terminal = true;
	/*ssize_t r;*/

	while (1 && from_terminal)
	{
		if (isatty(STDIN_FILENO))
	/*	{
			from_terminal = false;
			r = read(STDIN_FILENO, buffer, (BUFF_SIZE - 2));
			if (r == -1)
			{
				free(buffer);
				perror("./hsh");
				exit(0);
			}
			path = malloc(strlen(buffer));
			path = buffer;
		}
		else
		{*/
			printf("$ ");
		if (getline(&buffer, &len, stdin) == -1)
			handle_end_of_file(buffer);
		path = malloc(strlen(buffer));
		if (path == NULL)
		{
			free(argv);
			return (-1);
		}
		path = remove_newline(buffer, path);
	/*	}*/
		free(buffer);
		intilize_argv_to_null(argv);
		argv = tokenized_path(path, argv);
	/*	true_path = set_path(argv[0]);
		if (true_path != NULL)
			argv[0] = true_path; */
		if (inbuilt_functions(argv, path) == -1)
			child_pid = fork();
		if (child_pid == -1)
		{
			perror(av[0]);
			free(path);
			return (1);
		}
		if (child_pid == 0)
			execute_command(argv, av[0], environ);
		else
		{
			wait(&status);
			free(path);
			_free_(argv);
		}
	}
	return (0);
}
