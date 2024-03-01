#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t child_pid;
    int status;
    char *args[] = {"ls", "-l", "/tmp", NULL};

    for (int i = 1; i <= 5; i++) {
        child_pid = fork();
        if (child_pid == -1) {
            perror("Error:");
            return 1;
        }
        if (child_pid == 0) {
            execve("/bin/ls", args, NULL);
            perror("Error:");
            exit(1);
        }
    }

   
    for (int i = 0; i < 5; i++) {
        wait(&status);
    }

    return 0;
}
