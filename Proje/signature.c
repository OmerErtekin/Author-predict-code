#include "signature.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct features** read_signatures(int *nr_author) {
    int i = 0;
    struct features **author_sigs = calloc(MAX_AUTHORS, sizeof(struct features *));
    const char* authors[] = {
                                "agatha_christie",
                                "alexandre_dumas",
                                "brothers_grim",
                                "charles_dickens",
                                "douglas_adams",
                                "emily_bronte",
                                "fyodor_dostoevsky",
                                "james_joyce",
                                "jane_austen",
                                "lewis_caroll",
                                "mark_twain",
                                "sir_arthur_conan_doyle",
                                "william_shakespeare",
                                NULL,
                            };

    for (i = 0; authors[i] != NULL; ++i) {
        char fullpath[strlen("imzalar") + strlen(authors[i]) + 2];
        sprintf(fullpath, "imzalar/%s", authors[i]);

        // imza dosyasini ac
        FILE *f = fopen(fullpath, "rb");
        if (f == NULL) {
            fprintf(stderr, "Can't read sig file: %s\n", authors[i]);
            exit(1);
        }

        // struct icin yer ayirip icini doldur
        author_sigs[i] = malloc(sizeof(struct features));

        fscanf(f, "%m[A-za-z ]", &(author_sigs[i]->author));
        fscanf(f, "%lf", &(author_sigs[i]->avg_word_length));
        fscanf(f, "%lf", &(author_sigs[i]->ttr));
        fscanf(f, "%lf", &(author_sigs[i]->hapax));
        fscanf(f, "%lf", &(author_sigs[i]->avg_word_per_sentence));
        fscanf(f, "%lf", &(author_sigs[i]->complexity));

        // dosyayi kapat
        fclose(f);
    }
    *nr_author = i;
    return author_sigs;
}

void free_signatures(struct features **authors) {
    int i;
    for (i = 0; i < MAX_AUTHORS; ++i) {
        struct features *f = authors[i];
        if (f == NULL) {
            break;
        } else {
            free(f->author);
            free(f);
        }
    }
}



