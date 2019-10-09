#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>

/* Memory section within the heap */
struct chunk_t;

typedef struct
{
    uint8_t is_free;
    size_t size;
    struct chunk_t *next;
    void *data;
} chunk_t;

/* Heap structure, used to allocate memory */
typedef struct
{
    size_t size;
    size_t max_size;
    chunk_t *chunks;
} heap_t;

void heap_init();

/* Memory management functions */
void memcopy(uint8_t *source, uint8_t *dest, int nbytes);
void memset(uint8_t *dest, uint8_t val, uint32_t len);

/* Heap allocation functions */
void *kmalloc(size_t size);
void kfree(void *ptr);
void *krealloc(void *ptr, size_t size);

#endif
