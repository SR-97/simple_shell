#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point for the shell program
 * Return: Always 0
 */
int main(void)
{
    char *line;
    size_t bufsize = 0;
    ssize_t characters;

    while (1)
    {
        printf("$ ");
        characters = getline(&line, &bufsize, stdin);
        if (characters == -1)
        {
            perror("getline");
            break;
        }
        printf("%s", line);
    }

    free(line);
    return (0);
}
