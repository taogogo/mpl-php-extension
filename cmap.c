#include <string.h>
#include <stdlib.h>
//http://stackoverflow.com/questions/1234514/very-simple-map-implemention-in-c-for-caching-purpose
#define NR_BUCKETS 1024

struct StrHashNode {
    char *key;
    void *value;
    struct StrHashNode *next;

};

struct StrHashTable {
    struct StrHashNode *buckets[NR_BUCKETS];
    void (*free_key)(char *);
    void (*free_value)(void*);
    unsigned int (*hash)(const char *key);
    int (*cmp)(const char *first,const char *second);
};

void *cmap_get(struct StrHashTable *table,const char *key)
{
    unsigned int bucket = table->hash(key)%NR_BUCKETS;
    struct StrHashNode *node;
    node = table->buckets[bucket];
    while(node) {
        if(table->cmp(key,node->key) == 0)
            return node->value;
        node = node->next;
    }
    return NULL;
}
int cmap_insert(struct StrHashTable *table,char *key,void *value)
{
    unsigned int bucket = table->hash(key)%NR_BUCKETS;
    struct StrHashNode **tmp;
    struct StrHashNode *node ;

    tmp = &table->buckets[bucket];
    while(*tmp) {
        if(table->cmp(key,(*tmp)->key) == 0)
            break;
        tmp = &(*tmp)->next;
    }
    if(*tmp) {
        if(table->free_key != NULL)
            table->free_key((*tmp)->key);
        if(table->free_value != NULL)
            table->free_value((*tmp)->value);
        node = *tmp;
    } else {
        node = malloc(sizeof *node);
        if(node == NULL)
            return -1;
        node->next = NULL;
        *tmp = node;
    }
    node->key = key;
    node->value = value;

    return 0;
}

unsigned int simple_strhash(const char *str)
{
    unsigned int hash = 0;
    for(; *str; str++)
        hash = 31*hash + *str;
    return hash;
}

void *malloc_value(char *key)
{
    //return key;
    char *p;
    void *new_mem;  
    new_mem = malloc(strlen(key));
    //http://blog.jqian.net/post/malloc.html
    if (new_mem == NULL){
        printf("mallioc fail\n");  
        exit(1);
    }
    p=(char *)new_mem;
    strncpy(p, key, strlen(key)); 
    return p;
}
