#include "shell.h"

/**
 * _strcat - concatenates two string in a path form
 * @first: the first given destination
 * @second: the second given source
 *
 * Return: (Success) to the newly string
 * ------- (Fail) if it failed
 */
char *_strcat(char *first, char *second)
{
  int len1, len2, i = 0, j = 0;
  char *result;

  len1 = _strlen(first);
  len2 = _strlen(second);
  result = malloc((len1 + len2 + 2) * sizeof(char));
  if (!result)
    return (NULL);
  *result = '\0';
  while (first[j])
    result[i++] = first[j++];
  result[i++] = '/';
  j = 0;
  while (second[j])
    result[i++] = second[j++];
  result[i] = '\0';
  return (result);
}

/**
 * _strlen - finds the length of a given string
 * @str: the given string
 *
 * Return: (Success) the length of the string
 * ------- (Fail) negative value
 */
int _strlen(char *str)
{
  char *ptr;

  if (str == NULL)
    return (-1);
  for (ptr = str; *ptr; ptr++)
    ;
  return (ptr - str);
}

/**
 * _strcmp - compare two strings
 * @s1: the first given string
 * @s2: the second given string
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int _strcmp(char *s1, char *s2)
{
  int cmp = 0, i;

  if (s1 == NULL || s2 == NULL)
    return (1);
  for (i = 0; s1[i]; i++)
    {
      if (s1[i] != s2[i])
	{
	  cmp = s1[i] - s2[i];
	  break;
	}
      else
	continue;
    }
  return (cmp);
}

/**
 * _strchr - locates a character in a given string
 * @str: the given string
 * @c: the given string
 *
 * Return: (Success) a pointer to the first occurence of c
 * ------- (Fail) return a null pointer
 */
char *_strchr(char *str, char c)
{
  char *ptr;

  for (ptr = str; *ptr; ptr++)
    if (*ptr == c)
      return (ptr);
  return (NULL);
}

/**
 * _strdup - dupicates string
 * @str: the given string
 *
 * Return: (Success) a pointer to the duplicated string
 * ------- (Fail) return a null pointer
 */
char *_strdup(char *str)
{
  char *dupl;

  if (str == NULL)
    return (NULL);
  dupl = malloc(_strlen(str) + 1);
  if (dupl == NULL)
    return (NULL);
  _strcpy(dupl, str);
  return (dupl);
}
#include "shell.h"
/**
 * is_path_form - chekc if the given fikenname is a path
 * @data: the data strucct pointer
 *
 * Return: (Success)
 * ------- (Fail) otherwise
 */
int is_path_form(sh_t *data)
{
	if (_strchr(data->args[0], '/') != 0)
	{
		data->cmd = _strdup(data->args[0]);
		return (SUCCESS);
	}
	return (FAIL);
}

#define DELIMITER ":"
/**
 * is_short_form - chekc if the given fikenname is short form
 * @data: the data strucct pointer
 *
 * Return: (Success)
 * ------- (Fail) otherwise
 */
void is_short_form(sh_t *data)
{
	char *path, *token, *_path;
	struct stat st;

	path = _getenv("PATH");
	_path = _strdup(path);
	token = strtok(_path, DELIMITER);
	while (token)
	{
		data->cmd = _strcat(token, data->args[0]);
		if (stat(data->cmd, &st) == 0)
			break;
		free(data->cmd);
		token = strtok(NULL, DELIMITER);
	}
	if (*data->cmd == '\0')
		data->cmd = _strdup(data->args[0]);
	free(_path);
}

#undef DELIMITER

/**
 * is_builtin - checks if the command is builtin
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 * ------- (Fail) negative number will returned
 */
int is_builtin(sh_t *data)
{
	blt_t blt[] = {
		{"exit", abort_prg},
		{"cd", change_dir},
		{"help", display_help},
		{NULL, NULL}
	};
	int i = 0;

	while ((blt + i)->cmd)
	{
		if (_strcmp(data->args[0], (blt + i)->cmd) == 0)
			return (SUCCESS);
		i++;
	}
	return (NEUTRAL);
}
