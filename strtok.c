#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string(char *str, char *delim)
{
    int i, count = 0;
    char **words = NULL;
    char *token;

    token = strtok(str, delim);
    while (token != NULL)
    {
        count++;
        token = strtok(NULL, delim);
    }

    words = malloc((count + 1) * sizeof(char *));
    if (words == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(str, delim);
    for (i = 0; i < count; i++)
    {
        words[i] = token;
        token = strtok(NULL, delim);
    }
    words[count] = NULL;

    return words;
}

int main(void)
{
    char str[] = "Hello world from C";
    char **words = split_string(str, " ");

    int i = 0;
    while (words[i] != NULL)
    {
        printf("%s\n", words[i]);
        i++;
    }

    free(words);
    return 0;
}
