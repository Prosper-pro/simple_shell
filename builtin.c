#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * isbuiltin - check whether a command is a builtin
 *
 * @cmd: the command to check
 *
 * Return: 1 if command is builtin, otherwise 0
 *
 */
int isbuiltin(const char *cmd)
{
	char *builtins[] = { "exit", "env", NULL };
	int i = 0;

	while (builtins[i])
	{
		if (_strcmp(builtins[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * executebuiltin - map a command with a function
 *
 * @tokens: command to execute
 *
 */
void executebuiltin(char **tokens)
{
	builtin_t builtins[] = {
		{ "exit", __exit },
		{ "env", _env },
		{ NULL, NULL }
	};
	int i = 0;

	while (builtins[i].cmd)
	{
		if (_strcmp(builtins[i].cmd, tokens[0]) == 0)
			builtins[i].execute_builtin(tokens);
		i++;
	}
}

/**
 * __exit - the exit builtin that exits the shell
 *
 * @tokens: array of character arrays consisting the exit command
 * and its arguments
 *
 * Usage: exit
 *
 */
void __exit(char **tokens)
{
	if (tokens[1])
		exit(_atoi(tokens[1]));
	exit(0);
}

/**
 * _env - the env builtin that prints the current environment
 *
 * @tokens: array of character arrays consisting the env command
 * and its arguments
 *
 */
void _env(char **tokens)
{
	unsigned int i;

	for (i = 0; tokens[0] && environ[i] != NULL; ++i)
		printf("%s\n", environ[i]);
}
