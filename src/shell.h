#include "darray.h"

void read_line(DArray_t line, char const * prompt);
void print_prompt(char const * prompt);
void shell_loop();
void split_line(DArray_t words, char * line);