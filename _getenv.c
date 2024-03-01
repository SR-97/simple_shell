#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_getenv(const char *name) {
    extern char **environ;
    int i = 0;
    char *token;
    while (environ[i]) {
        token = strtok(environ[i], "=");
        if (strcmp(token, name) == 0) {
            return strtok(NULL, "=");
        }
        i++;
    }
    return NULL;
}

int main(void) {
    char *homevalue = _getenv("HOME");
    printf("%s\n", homevalue);
    return 0;
}
