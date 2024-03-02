#include "main.h"

/**
 * builtin_cd - Change the current working directory.
 * @d: Pointer to the data struct.
 * Return: void.
 */
void builtin_cd(data *d)
{
	char *dir = d->av[1];
	char cwd[256];

	/* Get the current working directory */
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");

	/* Update the PWD environment variable */
	_setenv(d, "PWD", cwd);

	/* If no directory provided, change to home directory */
	if (!dir)
		dir = _getenv("HOME");

	/* Change directory */
	if (chdir(dir) == -1)
		perror("cd");
	else
	{
		/* Update OLDPWD environment variable */
		_setenv(d, "OLDPWD", _getenv("PWD"));

		/* Get the new current working directory */
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");

		/* Update the PWD environment variable */
		_setenv(d, "PWD", cwd);
	}
}
