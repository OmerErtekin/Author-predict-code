#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "types.h"
#include "signature.h"
#include "features.h"
#define TABLO 7920

int main(int argc, char *argv[]) {


//TTR Harici diğerlerinde bariz fark var
	/* Kitabin adini komut satirindan alir */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text_file>\n", argv[0]);
        exit(1);
    }

    /* Dosya adi ve dosya verisi icin gosterici */
    char *file_name = argv[1];
    char *file_data = NULL;

    /* Kitaptan cikarilacak imza icin */
    struct features feat;
    /* Diskten okunacak imzalar icin dizi */
    struct features **authors;

    /* En iyi skoru tutacak degisken */
    double best_score = INFINITY;
    /* En iyi skora sahip yazarin dizi icindeki indeksi */
    int best_author = 0;
    /* Dosyanin boyutu */
    int file_size;
    /* Diskten okunan yazar sayisi */
    int nr_authors;
    int i;

    /* Kitap dosyasini ac */
    FILE *book = fopen(file_name, "rb");

    /* Kitap dosyasi acilamazsa programi sonlandir */
    if (book == NULL) {
        fprintf(stderr, "Can't open file %s.\n", file_name);
        exit(1);
    }

    /* Dosya acildi, boyutunu hesapla
     * Bunun icin fseek ile once dosyanin sonuna gidiyoruz
     * sonra ftell() ile dosyanin kacinci baytina geldigimizi
     * anliyoruz. Son olarak tekrar basa sariyoruz. */
    fseek(book, 0L, SEEK_END);
    file_size = ftell(book);
    fseek(book, 0L, SEEK_SET);

    /* Boyut + 1 kadarlik yer ayir, (+1 '\0' icin) */
    file_data = malloc(file_size + 1);
    if (file_data == NULL) {
    	fprintf(stderr, "Can't allocate memory for file data.\n");
    	fclose(book);
    	exit(1);
     }

    /* Tum dosyayi bir defada char dizisine oku */
    if (fread(file_data, 1, file_size, book) != file_size) {
        fprintf(stderr, "Couldn't read file %s correctly.\n", file_name);
        free(file_data);
        fclose(book);
        exit(1);
    }

    /* Artik dosyayi kapatabiliriz */
    fclose(book);

    /* Sonlandiriciyi koy */
    file_data[file_size] = '\0';

    /* Yazar imzalarini diskten oku. */
    authors = read_signatures(&nr_authors);

    /* Mevcut metnin imzasini hesapla */
    compute_features(file_data, &feat);
    /* TODO: authors[] dizisini gezerek mevcut
     * yazarlarin imzalariyla, metinden hesapladiginiz
     * imzayi sim_score() kullanarak karsilastirin.
     *
     * En dusuk skor en yakin yazari verir. En yakin yazarin
     * indeksini best_author'a, skoru ise best_score degiskenine
     * kaydedin. */
    double fark = 99;
    for(int m = 0;m<nr_authors;m++){
    	double yeni_fark =sim_score(authors[m],&feat);
    	if(yeni_fark < fark){
    		fark = yeni_fark;
    		best_author = m;
    		printf("%s\n",authors[m]->author);
			best_score=yeni_fark;
    	}
    }




    /* Analizin ekrana bastirilmasi */
    printf("--------------------------------------------------------------------------------\n");
    printf("%30s %9s %9s %9s %9s %9s %9s\n", "Author/File",
           "AWL", "TTR", "HAPAX", "AWPS", "COMPL", "SCORE");
    printf("--------------------------------------------------------------------------------\n");
    for (i = 0; i < nr_authors; ++i) {
        double s = sim_score(authors[i], &feat);
        printf("%30s: %8.4f, %8.4f, %8.4f, %8.4f, %8.4f, %8.4f", authors[i]->author,
               authors[i]->avg_word_length, authors[i]->ttr, authors[i]->hapax,
               authors[i]->avg_word_per_sentence, authors[i]->complexity, s);
        if (i == best_author) {
            printf(" (*)");
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------------------------\n");
    printf("%30s: %8.4f, %8.4f, %8.4f, %8.4f, %8.4f\n", file_name,
           feat.avg_word_length, feat.ttr, feat.hapax, feat.avg_word_per_sentence,
           feat.complexity);

    /* Veri yapilarinin isletim sistemine iade edilmesi */
    free(file_data);
    free_signatures(authors);
    free(authors);

    return 1;
}
