#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int i;
    int sum = 0;

    printf("argc or ac = %d\n", argc);
    printf("argv content is argv[]\n");

    for (i = 1; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
        sum += atoi(argv[i]);
    }

    printf("Sum of arguments: %d\n", sum);

    return sum;
}
