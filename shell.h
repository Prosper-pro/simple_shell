#ifndef _SHELL_H_
#define _SHELL_H_

/**
 * struct process_builtin - structure to hold a command and a
 * function pointer to hold the command
 *
 * @cmd: the command to execute
 * @execute_builtin: pointer to a function that takes a command and
 * executes it
 *
 */
struct process_builtin
{
	char *cmd; void (*execute_builtin)(char **tokens);
};
typedef struct process_builtin builtin_t;

extern char **environ;

int isbuiltin(const char *cmd);
char **tokenize(char *input);
void executebuiltin(char **tokens);
int executecmd(const char *name, char *const argv[], char *const env[]);
void printprompt(void);
void __exit(char **tokens);
void _env(char **tokens);
char *check_path(char *file);
int check_file(char *dirname, char *file);
char *_strdup(char *str);
int  _strlen(char *str);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, char *src);
int _atoi(char *str);

#endif /* _SHELL_H_ */
