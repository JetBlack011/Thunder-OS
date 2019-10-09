#include "arraylist.h"
#include "../mem.h"

void array_realloc(arraylist_t *array) {
    if (++array->size > array->max_size)
    {
        array->max_size *= 2;
        if ((array = krealloc(array, array->max_size * sizeof(void*) * 2)) == NULL)
            return;
        array->max_size *= 2;
    }
}

void array_create(arraylist_t **array, size_t max_size)
{
    *array = kmalloc(max_size);
    (*array)->data = (void*) *array + sizeof(size_t) * 2 + sizeof(void*);
    (*array)->max_size = max_size;
}

void array_set(arraylist_t *array, size_t index, void *val)
{
    if (index >= array->size)
        return;
    array->data[index] = val;
}

void array_add(arraylist_t *array, void *val)
{
    array_realloc(array);
    array->data[array->size] = val;
}

void array_insert(arraylist_t *array, size_t index, void *val)
{
    if (index > array->size)
        return;

    array_realloc(array);

    void *tmp = array->data[index];
    array->data[index] = val;

    for (size_t swap = index; swap < array->size; swap++)
    {
        array->data[swap] = tmp;
        tmp = array->data[swap];
    }
}

void array_remove(arraylist_t *array, size_t index)
{
    array->size--;
    for (size_t swap = index; swap < array->size; swap++)
        array->data[swap] = array->data[swap+1];
}
