#include <stdlib.h>
#include <stddef.h>
#include "shell.h"

/**
 * _strdup - duplicate a string
 *
 * @str: the string to copy
 *
 * Return: pointer to the newly allocated space in memory,
 *   NULL if @str is null, or insufficient memory available
 */
char *_strdup(char *str)
{
  char *newstr;
  int i, len;

  if (str == NULL)
    return (NULL);

  len = 0;
  while (*(str + len++))
    ;
  newstr = malloc(len * sizeof(char));
  if (newstr == NULL)
    return (NULL);

  i = 0;
  while (*(str + i))
    {
      *(newstr + i) = *(str + i);
      ++i;
    }
  *(newstr + i) = '\0';
  return (newstr);
}

/**
 * _strlen - return the length of a string
 * @str: the string to be processed
 * Return: the length of the string
 */
int  _strlen(char *str)
{
  int i;

  for (i = 0; str[i] != '\0'; ++i)
    ;
  return (i);
}

/**
 * _strcmp - compare two strings (exactly like the standard library function)
 *
 * @s1: the first string
 * @s2: the second string
 *
 * Return: 0 if strings are equal otherwise the difference between the strings
 */
int _strcmp(const char *s1, const char *s2)
{
  for (; *s1 != '\0' && *s2 != '\0'; ++s1, ++s2)
    if (*s1 != *s2)
      return (*s1 - *s2);

  if (*s1 != '\0')
    return (*s1);
  else if (*s2 != '\0')
    return (*s2);

  return (0);
}

/**
 * _strcpy - copy a string to another
 * @dest: the string to be copied to
 * @src: the string to be copied
 * Return: pointer to @dest
 */
char *_strcpy(char *dest, char *src)
{
  int i;

  for (i = 0; src[i] != '\0'; ++i)
    dest[i] = src[i];
  dest[i] = src[i];
  return (&dest[0]);
}
