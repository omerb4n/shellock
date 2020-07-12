/*
Stands for dynamic array.
Exports functions to deal with dynamic size arrays in heap
*/

#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "darray.h"
#include <string.h>

struct DArray_s {
    size_t size;
    size_t length;
    size_t member_size;
    void *data;
};

DArray_t darray_new(unsigned int initial_size, size_t member_size)
{
    DArray_t darray = malloc(sizeof(struct DArray_s));
    darray->member_size = member_size;
    darray->size = initial_size * darray->member_size;
    darray->length = 0;
    darray->data = malloc(darray->size);
    if (darray->data == 0) {
        shellock_error(ERROR_MEMORY);
    }
    return darray;
}

size_t darray_size(DArray_t darray) {
    return darray->size;
}

void * darray_data(DArray_t darray) {
    return darray->data;
}

size_t darray_length(DArray_t darray) {
    return darray->length;
}

void darray_append(DArray_t darray, void * value) {
    darray_set(darray, darray->length, value);
}

void darray_reset(DArray_t darray) {
    darray->length = 0;
}

void darray_set(DArray_t darray, unsigned int index, const void * value) {
    unsigned int assummed_size = index * darray->member_size + darray->member_size;
    if (assummed_size > darray->size) {
        unsigned int expand_size;
        if (assummed_size > darray->size * 2)
            expand_size = assummed_size - darray->size;
        else
            expand_size = darray->size;
        darray_expand(darray, expand_size);
    }
    void * element_pointer = darray->data + index * darray->member_size;
    memcpy(element_pointer, value, darray->member_size);
    if (darray->length <= index)
        darray->length = index + 1;
}

void * darray_get(DArray_t darray, unsigned int index){
    if(index >= darray->length || index < 0){
        fprintf(stderr, "Index %d out of bounds for array of size %zu\n", index, darray->size);
        shellock_error(ERROR_VALUE);
    }
    return darray->data + index * darray->member_size;
}

void darray_free(DArray_t darray) {
    free(darray->data);
    darray->size = 0;
    darray->length = 0;
}
void darray_expand(DArray_t darray, size_t n) {
    darray->size = darray->size + darray->member_size * n;
    void * temporary_data_pointer = realloc(darray->data, darray->size);
    if (temporary_data_pointer == 0) {
        shellock_error(ERROR_MEMORY);
    }
    darray->data = temporary_data_pointer;
}