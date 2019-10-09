#include <stddef.h>

typedef struct
{
    size_t size;
    size_t max_size;
    void **data;
} arraylist_t;

void array_set(arraylist_t *array, size_t index, void *val);
void array_add(arraylist_t *array, void *val);
void array_insert(arraylist_t *array, size_t index, void *val);
void array_remove(arraylist_t *array, size_t index);
