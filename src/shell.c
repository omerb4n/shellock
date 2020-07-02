#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "shell.h"

#define LINE_MAXIMUM_SIZE 1024

void error(char * message) {
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
}
char * read_line() {
    char* line_buffer = malloc(LINE_MAXIMUM_SIZE * sizeof(char));
    if (!line_buffer) {
        error("allocation error");
    }
}
void shell_loop() {
    int result_status;

    printf("Starting shell starting");
    do {
        printf("> ");
        
    }
    while(result_status == 0);
}