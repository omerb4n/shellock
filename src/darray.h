/*
Stands for dynamic array.
Exports functions to deal with dynamic size arrays in heap
*/
#include <stddef.h>

typedef struct DArray_s *DArray_t;

DArray_t darray_new(unsigned int initial_size, size_t member_size);
void darray_set(DArray_t darray, unsigned int index, const void * value);
void darray_reset(DArray_t darray);
void darray_append(DArray_t darray, void * value);
void * darray_get(DArray_t darray, unsigned int index);
void darray_expand(DArray_t darray, size_t n);
void darray_free(DArray_t darray);
size_t darray_size(DArray_t darray);
void * darray_data(DArray_t darray);
size_t darray_length(DArray_t darray);