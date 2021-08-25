#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "shell.h"

/**
 * main - Entry point to the custom shell program
 *
 * Return: 0 on success, -1 on failure
 *
 */
int main(void)
{
	char *line, *name;
	size_t length;
	char **tokens;
	struct stat s;
	int i;

	printprompt();
	while (getline(&line, &length, stdin) >= 0)
	{
		tokens = tokenize(line);
		if (tokens[0])
		{
			name = tokens[0];
			if (isbuiltin(tokens[0]))
			{
				executebuiltin(tokens);
			}
			else
			{
				if (stat(tokens[0], &s) != 0)
					tokens[0] = check_path(tokens[0]);
				if (tokens[0])
					executecmd(tokens[0], tokens, NULL);
				else
					printf("%s: command not found\n", name);
			}
		}
		printprompt();
	}
	for (i = 0; tokens[i] != 0; ++i)
		free(tokens[i]);
	free(tokens);

	return (0);
}

/**
 * printprompt - print the shell prompt
 *
 */
void printprompt(void)
{
	printf("$ ");
}

/**
 * check_path - checks a file in the environment path
 *
 * @file: name of the file to check
 *
 * Return: full path of file
 *
 */
char *check_path(char *file)
{
	char *path, *temp;
	char *token;

	path = getenv("PATH");
	temp = _strdup(path);
	if (temp == NULL)
		return (NULL);
	token = strtok(temp, ":");
	while (token)
	{
		if (check_file(token, file))
		{
			strcat(token, "/");
			strcat(token, file);
			return (token);
		}
		token = strtok(NULL, ":");
	}
	free(temp);
	return (NULL);
}

/**
 * check_file - check if a file exist in a directory
 *
 * @dirname: directory name
 * @file: name of the file to check
 *
 * Return: 1 if success, 0 if failure
 */
int check_file(char *dirname, char *file)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(dirname);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (_strcmp(dir->d_name, file) == 0)
				return (1);
		}
		closedir(d);
	}
	return (0);
}
