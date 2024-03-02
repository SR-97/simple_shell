#include "main.h"

/**
 * start_process - Start a new process.
 * @d: Pointer to the data struct.
 * Return: void.
 */
void start_process(data *d)
{
	pid_t child_pid = fork();
	int status = 0;

	if (child_pid == -1)
		goto free;
	if (child_pid == 0 && execve(d->av[0], d->av, NULL) == -1)
		goto free;
	else if (wait(&status) == -1)
		goto free;
	if (WIFEXITED(status))
		d->last_exit_status = WEXITSTATUS(status);
	return;

free:
	perror(d->shell_name);
	free_array(d->av);
	free(d->cmd);
	exit(EXIT_FAILURE);
}

/**
 * handler_sigint - Signal handler function for SIGINT.
 * @signal: The signal number.
 * Return: void.
 */
void handler_sigint(int signal)
{
	(void)signal;
	exit(EXIT_FAILURE);
}

/**
 * _exec - Execute the command.
 * @d: Pointer to the data struct.
 * Return: void.
 */
void _exec(data *d)
{
	const char prompt[] = PROMPT;

	/* Register the signal handler for SIGINT */
	signal(SIGINT, handler_sigint);

	while (1)
	{
		/* Print the shell prompt if the input is from terminal */
		if (isatty(STDIN_FILENO))
			_printf(prompt);

		/* Read the command from the user */
		read_cmd(d);

		/* Check if the command is not empty */
		if (_strlen(d->cmd) != 0)
		{
			/* Split the command into tokens */
			split(d, " ");

			/* Check if the command is a built-in */
			if (!exec_builtin(d))
			{
				/* Search for the command in PATH */
				_which(d);

				/* Check if the command exists */
				if (access(d->av[0], F_OK) == -1)
				{
					perror(d->shell_name);
				}
				else
				{
					/* Start a new process to execute the command */
					start_process(d);
				}
			}
			free_array(d->av);
		}
		free(d->cmd);
	}
}
