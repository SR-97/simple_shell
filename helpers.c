#include "main.h"


void _printf(const char *str)
{
	if (!str)
		return;
	while (*str)
	{
		write(STDOUT_FILENO, str, 1);
		str++;
	}
}


void free_array(char **array)
{
	if (!array)
		return;

	for (int i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}


void split(data *d, const char *delim)
{
	char *token;
	int ntokens = 0;

	d->av = malloc(sizeof(char *));
	if (d->av == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	d->av[0] = NULL;

	token = strtok(d->cmd, delim);
	while (token)
	{
		ntokens++;
		char **tmp = realloc(d->av, (ntokens + 1) * sizeof(char *));
		if (tmp == NULL)
		{
			free_array(d->av);
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		d->av = tmp;
		d->av[ntokens - 1] = strdup(token);
		if (d->av[ntokens - 1] == NULL)
		{
			free_array(d->av);
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		d->av[ntokens] = NULL;
		token = strtok(NULL, delim);
	}
}

void init_data(data *d, const char *shell_name)
{
	d->cmd = NULL;
	d->av = NULL;
	d->shell_name = shell_name;
	d->last_exit_status = EXIT_SUCCESS;
	d->flag_setenv = 0;
}


void read_cmd(data *d)
{
	size_t n = 0;
	ssize_t nread;
	int i;

	nread = _getline(&d->cmd, &n, stdin);

	if (nread == -1)
	{
		free(d->cmd);
		exit(EXIT_SUCCESS);
	}

	d->cmd[nread - 1] = '\0';
	_trim(d->cmd);
	
	for (i = 0; d->cmd[i] != '\0'; i++)
	{
		if (d->cmd[0] == '#' || (d->cmd[i] == '#' && d->cmd[i - 1] == ' '))
		{
			d->cmd[i] = '\0';
			break;
		}
	}
	_trim(d->cmd);
}

