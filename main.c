#include "main.h"
#include "helpers.h"

int main(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("($) ");
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}
