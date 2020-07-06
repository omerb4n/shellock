/*
Stands for dynamic size char array.
Exports functions to deal with dynamic sized char arrays in heap.
*/

#include "darray.h"
#include <stdlib.h>
#include <stdio.h>
#include "errors.h"

void darray_init(DArray *darray, unsigned int initial_size){
    darray->size = initial_size;
    darray->length = 0;
    darray->data = malloc(sizeof(char) * darray->size);
    if (darray->data == 0) {
        shellock_error(ERROR_MEMORY);
    }
}

void darray_append(DArray * darray, char value) {
    darray_set(darray, darray->length, value);
}

void darray_set(DArray *darray, unsigned int index, char value) {
    unsigned int assummed_size = index + sizeof(char);
    if (assummed_size > darray->size) {
        unsigned int expand_size;
        if (assummed_size > darray->size * 2)
            expand_size = assummed_size - darray->size;
        else
            expand_size = darray->size;
        darray_expand(darray, expand_size);
    }
    darray->data[index] = value;
    if (darray->length <= index)
        darray->length = index +1;
}

char darray_get(DArray *darray, unsigned int index){
    if(index > darray->size || index < 0){
        printf("Index %d out of bounds for vector of size %d\n", index, darray->size);
        exit(1);
    }

    return darray->data[index];
}

void darray_free(DArray *darray) {
    free(darray->data);
    darray->size = 0;
}
void darray_expand(DArray *darray, unsigned int n) {
    darray->size = darray->size + sizeof(char) * n;
    darray->data = realloc(darray->data, darray->size);
    if (darray->data == 0) {
        shellock_error(ERROR_MEMORY);
    }
}