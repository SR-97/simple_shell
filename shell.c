#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "helpers.h"

#define MAX_LINE_LENGTH 1024

int main(void) {
    char *line = NULL;
    char *args[2];  /* Only two elements: command and NULL */
    ssize_t read_bytes;  /* Declare read_bytes at the beginning */

    int status;

    do {
        printf("($) ");
        read_bytes = getline(&line, NULL, stdin);
        if (read_bytes == -1) {
            free(line);
            break;  /* Exit on Ctrl+D (EOF) */
        }
        line[read_bytes - 1] = '\0'; /* Removing the newline character */

        args[0] = line;
        args[1] = NULL;  /* Last element must be NULL for execve */

        status = execute(args);

        free(line);
    } while (status);

    return EXIT_SUCCESS;
}
