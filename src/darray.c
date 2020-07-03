/*
Stands for dynamic size char array.
Exports functions to deal with dynamic sized char arrays in heap.
*/

#include "darray.h"
#include <stdlib.h>
#include <stdio.h>

void darray_init(DArray *darray, unsigned int initial_size){
    darray->size = initial_size;
    darray->data = malloc(sizeof(char) * darray->size);
}

void darray_set(DArray *darray, unsigned int index, char value) {
    if (index + sizeof(char) > darray->size) {
        darray_expand(darray, darray->size);
    }
    darray->data[index] = value;
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
}