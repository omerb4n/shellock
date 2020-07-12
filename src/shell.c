#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "errors.h"

#define LINE_BUFFER_INITIAL_SIZE 100 * sizeof(char)
#define EMPTY_INPUT ""
#define DEFAULT_PROMPT "> "
#define END_OF_LINE '\n'
#define NULL_BYTE ""
#define START_MESSAGE "Starting shell starting\n"


void read_line(DArray_t line, char const * prompt) {
    char current_char;
    print_prompt(prompt);
    darray_reset(line);
    while ((current_char = getc(stdin)) != END_OF_LINE) {
        darray_append(line, &current_char);
    }
    darray_append(line, &NULL_BYTE);
}

void print_prompt(char const * prompt) {
    if (prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }
}
void shell_loop() {
    int result_status = 0;
    DArray_t line = darray_new(LINE_BUFFER_INITIAL_SIZE, sizeof(char));
    printf(START_MESSAGE);
    do {
        read_line(line, DEFAULT_PROMPT);
    }
    while(result_status == 0);
    darray_free(line);
}