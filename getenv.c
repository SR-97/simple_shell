#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *homevalue = getenv("HOME");
    printf("%s\n", homevalue);
    return 0;
}
