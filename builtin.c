#include "main.h"

/**
 * exec_builtin - Check if the command is a built-in and execute it if so.
 * @d: Pointer to the data struct.
 * Return: 1 if the command is a built-in, 0 otherwise.
 */
int exec_builtin(data *d)
{
	builtin builtin[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{"cd", builtin_cd},
		{NULL, NULL},
	};
	int i = 0;

	for (i = 0; builtin[i].cmd; i++)
	{
		if (_strcmp(d->av[0], builtin[i].cmd) == 0)
		{
			builtin[i].f(d);
			return (1);
		}
	}
	return (0);
}

/**
 * builtin_exit - Exit the shell.
 * @d: Pointer to the data struct.
 * Return: void.
 */
void builtin_exit(data *d)
{
	const char *errorString = "./hsh: 1: exit: Illegal number: ";

	if (d->av[1])
	{
		if (d->av[1][0] != '-' && _isnumber(d->av[1]))
			d->last_exit_status = atoi(d->av[1]);
		else
		{
			write(STDERR_FILENO, errorString, strlen(errorString));
			write(STDERR_FILENO, d->av[1], strlen(d->av[1]));
			write(STDERR_FILENO, "\n", 1);
			d->last_exit_status = 2;
		}
	}
	free_array(d->av);
	free(d->cmd);
	if (d->flag_setenv)
		free_array(environ);
	exit(d->last_exit_status);
}

/**
 * builtin_env - Print the current environment.
 * @d: Pointer to the data struct.
 * Return: void.
 */
void builtin_env(data *d)
{
	int i = 0;

	(void)d;
	while (environ[i])
	{
		_printf(environ[i]);
		_printf("\n");
		i++;
	}
}

/**
 * builtin_setenv - Set or modify an environment variable.
 * @d: Pointer to the data struct.
 * Return: void.
 */
void builtin_setenv(data *d)
{
	(void)d;
	if (d->av[1] && d->av[2])
	{
		if (_setenv(d, d->av[1], d->av[2]) == -1)
		{
			perror("setenv");
		}
	}
}

/**
 * builtin_unsetenv - Unset an environment variable.
 * @d: Pointer to the data struct.
 * Return: void.
 */
void builtin_unsetenv(data *d)
{
	int i, j;
	int len;

	(void)d;
	if (!d->av[1] || !getenv(d->av[1]))
	{
		_perror(d->shell_name, "variable not found.");
		return;
	}
	len = strlen(d->av[1]);
	for (i = 0; environ[i]; i++)
		if (strncmp(environ[i], d->av[1], len) == 0 && environ[i][len] == '=')
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
}
