#include "mem.h"

static heap_t *heap;

/* Memory management functions */
void memcopy(uint8_t *source, uint8_t *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memset(uint8_t *dest, uint8_t val, uint32_t len) {
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

void heap_init()
{
    heap = (heap_t*) 0x10000;
    heap->chunks = (chunk_t*) &heap->chunks + sizeof(chunk_t*);
    heap->size = 0;
    heap->max_size = 0xFFFEFFF / sizeof(chunk_t);
}

/* Heap allocation functions */
void *kmalloc(size_t size)
{
    if (size > heap->max_size || size < 1)
        return NULL;

    chunk_t *chunk = heap->chunks;

    if (heap->size == 0)
    {
        chunk->is_free = 1;
        chunk->size = size;
        chunk->next = (void*) chunk + sizeof(chunk_t) + size;
        chunk->data = (void*) chunk + sizeof(chunk_t);
        heap->size++;

        return chunk->data;
    }
    else
    {
        for (size_t i = 0; i < heap->size; i++)
        {
            if (chunk->is_free == 0 && size <= chunk->size)
            {
                chunk->is_free = 1;
                chunk->size = size;
                if (chunk->next == NULL)
                    chunk->next = (void*) chunk + sizeof(chunk_t) + size;
                chunk->data = (void*) chunk + sizeof(chunk_t);
                heap->size++;

                return chunk->data;
            }
            else
                chunk = (chunk_t*) chunk->next;
        }

        chunk->is_free = 1;
        chunk->size = size;
        chunk->next = (void*) chunk + sizeof(chunk_t) + size;
        chunk->data = (void*) chunk + sizeof(chunk_t);
        heap->size++;

        return chunk->data;
    }
}

void kfree(void *ptr)
{
    chunk_t *chunk = (chunk_t*) ptr;

    if (chunk == NULL)
        return;

    chunk->is_free = 0;
}

void *krealloc(void *ptr, size_t size)
{
    chunk_t *chunk = (chunk_t*) ptr;

    if (chunk == NULL)
        return kmalloc(size);

    if (chunk->size < size)
    {
        chunk = (chunk_t*) kmalloc(size);
        memcopy((uint8_t*) chunk, ptr, size);
        kfree(ptr);
        return chunk->data;
    }

    chunk->size = size;
    return chunk->data;
}
