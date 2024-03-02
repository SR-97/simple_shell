#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    while (1) {
        printf("$ ");
        characters = getline(&buffer, &bufsize, stdin);
        if (characters == -1) {
            break; 
        }
        buffer[characters - 1] = '\0';  
        if (fork() == 0) {
            // Child process
            execlp(buffer, buffer, NULL);
            // If execlp returns, an error occurred
            perror("Error");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);  // Wait for child to finish
        }
    }

    free(buffer);
    return 0;
}
