#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "errors.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define LINE_BUFFER_INITIAL_CAPACITY 100
#define WORDS_BUFFER_INITIAL_CAPCITY 10
#define EMPTY_INPUT ""
#define DEFAULT_PROMPT "> "
#define END_OF_LINE '\n'
#define NULL_BYTE ""

#define START_MESSAGE "Starting shell starting\n"

const char * NULL_BYTE_PTR = NULL;

void read_line(DArray_t line, char const * prompt) {
    char current_char;
    print_prompt(prompt);
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

void split_line(DArray_t words, char * line) {
    char *separator = " ";
    char *parsed;
    parsed = strtok(line, separator);
    while (parsed != NULL) {
        darray_append(words, &parsed);
        parsed = strtok(NULL, separator);
    }
    darray_append(words, &NULL_BYTE_PTR);
}

void execute_command(char ** command) {
    pid_t child_pid;
    int stat_loc;

    if (!command[0])   
        return;

    child_pid = fork();
    if (child_pid < 0) {
        shellock_error(ERROR_FORK);
    }
    if (child_pid == 0) {
        if (execvp(command[0], command) < 0) {
            perror(command[0]);
            shellock_error(ERROR_CHILD);
        }
    } else {
        waitpid(child_pid, &stat_loc, WUNTRACED);
    }
}
void shell_loop() {
    int result_status = 0;
    DArray_t line = darray_new(LINE_BUFFER_INITIAL_CAPACITY, sizeof(char));
    DArray_t words = darray_new(WORDS_BUFFER_INITIAL_CAPCITY, sizeof(char *));

    printf(START_MESSAGE);
    do {
        read_line(line, DEFAULT_PROMPT);
        split_line(words, darray_data(line));

        execute_command(darray_data(words));

        darray_reset(line);
        darray_reset(words);
    }
    while(result_status == 0);
    darray_free(words);
    darray_free(line);
}