#include "main.h"

/**
 * _perror - Prints an error message to stderr.
 * @str1: The name of the shell program.
 * @str2: The error message to be printed.
 * Return: void
 */
void _perror(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		return;

	while (*str1)
	{
		write(STDERR_FILENO, str1, 1);
		str1++;
	}

	write(STDERR_FILENO, ": ", 2);

	while (*str2)
	{
		write(STDERR_FILENO, str2, 1);
		str2++;
	}
	write(STDERR_FILENO, "\n", 1);
}


/**
 * _trim - Removes leading and trailing spaces and tabs from a string.
 * @str: The string to be trimmed.
 * Return: void.
 */
void _trim(char *str)
{
	int i, j, len = _strlen(str);

	for (i = 0; i < len && (str[i] == ' ' || str[i] == '\t'); i++)
		;

	for (j = 0; i < len ; i++, j++)
		str[j] = str[i];

	str[j] = '\0';

	for (i = _strlen(str) - 1; i > 0 && (str[i] == ' ' || str[i] == '\t'); i--)
		str[i] = '\0';
}


/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: Pointer to the memory block to be reallocated.
 * @new_size: The new size of the memory block.
 * Return: Pointer to the newly allocated memory block.
 */
void *_realloc(void *ptr, unsigned int new_size)
{
	char *p;
	unsigned int i, tp = new_size, old_size = sizeof(ptr);

	if (old_size == new_size)
		return (ptr);
	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size > old_size)
		tp = old_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	p = malloc(new_size);

	for (i = 0; i < tp; i++)
		p[i] = ((char *)ptr)[i];
	free(ptr);
	return (p);
}
