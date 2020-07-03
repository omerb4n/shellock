#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "errors.h"

#define LINE_MAXIMUM_SIZE 1024


char * read_line() {
    char* line_buffer = malloc(LINE_MAXIMUM_SIZE * sizeof(char));
    if (!line_buffer) {
        shellock_error(ERROR_MEMORY);
    }
}
void shell_loop() {
    int result_status;

    printf("Starting shell starting\n");
    do {
        printf("> ");
        read_line();
    }
    while(result_status == 0);
}