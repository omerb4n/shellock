#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "errors.h"

#define LINE_BUFFER_INITIAL_SIZE 0 * sizeof(char)
#define EMPTY_INPUT ""
#define DEFAULT_PROMPT "> "
#define END_OF_LINE '\n'
#define START_MESSAGE "Starting shell starting\n"


void read_line(DArray * line, char const * prompt) {
    char current_char;
    print_prompt(prompt);
    darray_reset(line);
    while ((current_char = getc(stdin)) != END_OF_LINE) {
        darray_append(line, current_char);
    }
    darray_append(line, 0);
}

void print_prompt(char const * prompt) {
    if (prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }
}
void shell_loop() {
    int result_status = 0;
    DArray line;
    darray_init(&line, LINE_BUFFER_INITIAL_SIZE);
    printf(START_MESSAGE);
    do {
        read_line(&line, DEFAULT_PROMPT);
    }
    while(result_status == 0);
    darray_free(&line);
}