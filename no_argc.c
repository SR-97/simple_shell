#include <stdio.h>

int main(int ac, char **av) {
    printf("argv content is argv[]\n");

    if (av[1] == NULL) {
        printf("argv = %s\n", av[0]);
    }
 
    else {
        int i = 1;
        while (av[i] != NULL) {
            printf("argv = %s\n", av[i]);
            i++;
        }
    }

    return 0;
}
