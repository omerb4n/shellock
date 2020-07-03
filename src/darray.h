/*
Stands for dynamic array.
Exports functions to deal with dynamic size arrays in heap
*/

typedef struct {
    unsigned int size;
    unsigned char *data;
} DArray;

void darray_init(DArray *darray, unsigned int initial_size);
void darray_set(DArray *darray, unsigned int index, char value);
char darray_get(DArray *darray, unsigned int index);
void darray_expand(DArray *darray, unsigned int n);
void darray_free(DArray *darray);