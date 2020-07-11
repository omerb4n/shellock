/*
Stands for dynamic size char array.
Exports functions to deal with dynamic sized char arrays in heap.
*/

#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "darray.h"

struct DArray_s {
    size_t size;
    size_t length;
    unsigned char *data;
};

DArray_t darray_new(unsigned int initial_size)
{
    DArray_t darray = malloc(sizeof(DArray_t));
    darray->size = initial_size;
    darray->length = 0;
    darray->data = malloc(sizeof(char) * darray->size);
    if (darray->data == 0) {
        shellock_error(ERROR_MEMORY);
    }
    return darray;
}

size_t darray_size(DArray_t darray) {
    return darray->size;
}

unsigned char * darray_data(DArray_t darray) {
    return darray->data;
}

size_t darray_length(DArray_t darray) {
    return darray->length;
}

void darray_append(DArray_t darray, char value) {
    darray_set(darray, darray->length, value);
}

void darray_reset(DArray_t darray) {
    darray->length = 0;
}

void darray_set(DArray_t darray, unsigned int index, char value) {
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

char darray_get(DArray_t darray, unsigned int index){
    if(index >= darray->length || index < 0){
        fprintf(stderr, "Index %d out of bounds for vector of size %zu\n", index, darray->size);
        shellock_error(ERROR_VALUE);
    }
    return darray->data[index];
}

void darray_free(DArray_t darray) {
    free(darray->data);
    darray->size = 0;
    darray->length = 0;
}
void darray_expand(DArray_t darray, size_t n) {
    darray->size = darray->size + sizeof(char) * n;
    void * temporary_data_pointer = realloc(darray->data, darray->size);
    if (temporary_data_pointer == 0) {
        shellock_error(ERROR_MEMORY);
    }
    darray->data = temporary_data_pointer;
}