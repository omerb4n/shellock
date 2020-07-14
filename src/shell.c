#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "errors.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>
#include "darray.h"

#define LINE_BUFFER_INITIAL_CAPACITY 100
#define WORDS_BUFFER_INITIAL_CAPCITY 10
#define PATH_BUFFER_INITIAL_CAPCITY 100
#define EMPTY_INPUT ""
#define DEFAULT_PROMPT "> "
#define END_OF_LINE '\n'
#define NULL_BYTE ""

#define START_MESSAGE "Starting shell starting\n"

static void read_line(DArray_t line, char const * prompt);
static void print_prompt(char const * prompt);
static bool execute_builtin_command(char ** command);
static void split_line(DArray_t words, char * line);
static void execute_command(char ** command);
static void initialize_gloabls();
static void free_globals();
static int cd(char *path);

const char * NULL_BYTE_PTR = NULL;
DArray_t current_working_directory;
static void read_line(DArray_t line, char const * prompt) {
    char current_char;
    print_prompt(prompt);
    while ((current_char = getc(stdin)) != END_OF_LINE) {
        darray_append(line, &current_char);
    }
    darray_append(line, &NULL_BYTE);
}

static void print_prompt(char const * prompt) {
    char * res;
    while(!(res = getcwd(darray_data(current_working_directory), darray_size(current_working_directory)))) {
        if (errno == ERANGE) {
            darray_expand(current_working_directory, darray_size(current_working_directory));
        } else {
            shellock_error(UNKNOWN_ERROR);
        }
    }
    if (prompt != NULL) {
        printf("%s", res);
        printf("%s", prompt);
    }
    fflush(stdout);
}

static bool execute_builtin_command(char ** command) {
    if (strcmp(command[0], "cd") == 0) {
        if (cd(command[1]) < 0) {
            shellock_error(ERROR_BUILT_IN_COMMAND);
        }
    }
    else
        return false;
    return true;
}

static void split_line(DArray_t words, char * line) {
    char *separator = " ";
    char *parsed;
    parsed = strtok(line, separator);
    while (parsed != NULL) {
        darray_append(words, &parsed);
        parsed = strtok(NULL, separator);
    }
    darray_append(words, &NULL_BYTE_PTR);
}

static void execute_command(char ** command) {
    pid_t child_pid;
    int stat_loc;

    if (!command[0])   
        return;
    if (execute_builtin_command(command))
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

static void initialize_gloabls(){
    current_working_directory = darray_new(PATH_BUFFER_INITIAL_CAPCITY, sizeof(char));
}

static void free_globals() {
    darray_free(current_working_directory);
}

void shell_loop() {
    int result_status = 0;
    DArray_t line = darray_new(LINE_BUFFER_INITIAL_CAPACITY, sizeof(char));
    DArray_t words = darray_new(WORDS_BUFFER_INITIAL_CAPCITY, sizeof(char *));
    initialize_gloabls();
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
    free_globals();
}

static int cd(char *path) {
    return chdir(path);
}