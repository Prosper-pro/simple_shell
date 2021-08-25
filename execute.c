#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * tokenize - break a line of input into separate tokens
 *
 * @input: character array to tokenize
 *
 * Return: pointer to array of characters (tokens)
 */
char **tokenize(char *input)
{
	char *token;
	char **args;
	char *delim = " \n";
	int i;

	args = malloc(sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	token = strtok(input, delim);
	while (token != NULL)
	{
		args[i] = malloc(sizeof(token));
		if (args[i] == NULL)
			return (NULL);
		_strcpy(args[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	args[i] = NULL;

	return (args);
}

/**
 * executecmd - execute a command with arguments
 *
 * @name: pathname to execute command
 * @argv: array of arguments
 * @env: environment to be passed
 *
 * Return: 0 on success, -1 on failure
 *
 */
int executecmd(const char *name, char *const argv[], char *const env[])
{
	if (fork() == 0)
	{
		if (execve(name, argv, env) == -1)
			return (-1);
	}
	else
	{
		wait(NULL);
	}

	return (0);
}
