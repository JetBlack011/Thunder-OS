#include "hashtable.h"
#include "../string.h"
#include "../mem.h"
#include "../../drivers/screen.h"

#include <stdint.h>

uint32_t fnv_hash(char* key)
{
    uint32_t fnv_prime = 16777619;
    uint32_t hash = 0x811c9dc5;

    while (*key)
        hash = (hash ^ (*key++)) * fnv_prime;

    return hash;
}

hashtable_t *table_create(int size)
{
    hashtable_t *hashtable;
    if (size < 1)
        return NULL;

    hashtable = (hashtable_t*) kmalloc(sizeof(hashtable_t));
    hashtable->table = (entry_t**) kmalloc(sizeof(entry_t*) * size);

    for (int i = 0; i < size; i++)
        hashtable->table[i] = NULL;

    hashtable->size = size;
    return hashtable;
}

void table_add(hashtable_t *hashtable, char *key, int val)
{
    uint32_t index = fnv_hash(key) % (uint32_t) hashtable->size;
    entry_t *entry = hashtable->table[index];
    entry_t *last = NULL;

    while (entry != NULL && strcmp(entry->key, key) != 0)
    {
        last = entry;
        entry = entry->next;
    }

    if (entry == NULL)
        entry = (entry_t*) kmalloc(sizeof(entry_t));

    entry->key = key;
    entry->val = val;
    entry->next = NULL;

    if (last == NULL)
        hashtable->table[index] = entry;
    else
        last->next = entry;
}

int table_find(hashtable_t *hashtable, char *key)
{
    uint32_t index = fnv_hash(key) % (uint32_t) hashtable->size;
    entry_t *entry = hashtable->table[index];

    if (entry == NULL)
        return -1;
    else if (strcmp(entry->key, key) == 0)
        return entry->val;
    else
    {
        while (entry != NULL && strcmp(entry->key, key) != 0)
            entry = entry->next;

        if (strcmp(entry->key, key) == 0)
            return entry->val;
    }
   return -1;
}
