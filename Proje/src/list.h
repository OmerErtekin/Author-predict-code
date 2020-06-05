#ifndef _LIST_H_
#define _LIST_H_

#ifdef WITH_UTHASH
#include "uthash.h"
#endif

struct node {
    char *word;
    int count;
    struct node *next;
#ifdef WITH_UTHASH
    /* Hash ile derlenirken ihtiyac duyulan bir
     * degisken */
    UT_hash_handle hh;

#else
    /* Bagli listeyle derlenirken ihtiyac duyulan
     * sonraki gosterici. */
#endif
};

unsigned long hash_compute(const char* str);
void hash_free(struct node** table);
struct node* add_word(struct node **list, char *word);

#endif
