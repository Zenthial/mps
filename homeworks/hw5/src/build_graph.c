#include <stdio.h>
#include <stdlib.h>

// #include "simple_graph.h"

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t lineSize = 0;

    lineSize = getline(&line, &len, stdin);

    printf("You entered %s, which has %zu chars.\n", line, lineSize - 1);

    free(line);

    return EXIT_SUCCESS;
}