#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

    int main(void) {
    int i = 0;
    char **array;
    pid_t child_pid;
    int status;
    char *buf = NULL;
    size_t buf_size = 0;
    char *token;

    while (1) {
        write(1, "#cisfun$ ", 9);
        getline(&buf, &buf_size, stdin);
        token = strtok(buf, "\t\n");
        array = malloc(sizeof(char*) * 1024);

        while (token) {
            array[i] = token;
            token = strtok(NULL, "\t\n");
            i++;
        }
        array[i] = NULL;
        child_pid = fork();
        if (child_pid == 0) {
            if (execve(array[0], array, NULL) == -1)
                perror("Error");
        } else {
            wait(&status);
        }

        i = 0;
        free(array);
    }
}
