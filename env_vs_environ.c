#include <stdio.h>

extern char **environ;
int main(int ac, char **av, char **env) {
    printf("%p\n", env);
    printf("%p\n", environ);
    return 0;
}

