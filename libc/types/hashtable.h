typedef struct entry_t
{
    char *key;
    int val;
    struct entry_t *next;
} entry_t;

typedef struct
{
    int size;
    entry_t **table;
} hashtable_t;

hashtable_t *table_create(int size);
void table_add(hashtable_t *hashtable, char *key, int val);
int table_find(hashtable_t *hashtable, char *key);
