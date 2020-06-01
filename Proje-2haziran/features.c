#include "features.h"
#include "list.h"

#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define TABLO 7920



void cleanup(char *s) {
    /* s stringini kucuk harflere cevirip basindan ve
     * sonundan noktalama ve bazi diger karakterleri kaldirir. */
    char *cset = "!\"',;:.-?) _([]<>*#\n\t\r";
    char *sp, *start, *ep, *end;
    int length, i;


    sp = start = s;
    ep = end = sp + strlen(s) - 1;

    /* basini ve sonunu temizle */
    while (sp <= end && strchr(cset, *sp))
        sp++;
    while (ep > start && strchr(cset, *ep))
        ep--;

    if ((start != sp) || (ep != end)) {
        length = (sp > ep) ? 0 : ((ep - sp) + 1);
        if (length > 0)
            memmove(start, sp, length);
        start[length] = '\0';
    }

    /* kucuk harfe cevir */
    for (i = 0; start[i] != '\0'; ++i) {
        start[i] = tolower(start[i]);
    }
    // tüm noktalam işaretlerinin silindiğinden emin olmak için
 //   s = strtok(s,"!\"',;:.- ?)(_[]<>*#\n\t\r");
}

/* TODO: iki imza arasindaki benzerligi hesaplayan fonksiyon. */
double sim_score(struct features *s1, struct features *s2) {
	    double sim_score=0;
	    double awl_score=11.0*fabs(s1->avg_word_length - s2->avg_word_length);
	    double ttr_score=33.0*fabs(s1->ttr - s2->ttr);
	    double hapax_score=50.0*fabs(s1->hapax - s2->hapax);
	    double awps_score=0.4*fabs(s1->avg_word_per_sentence - s2->avg_word_per_sentence);
	    double compl_score=4*fabs(s1->complexity - s2->complexity);
	    sim_score= awl_score+ttr_score+hapax_score+awps_score+compl_score;
	    return sim_score;
}


/* TODO */
void compute_features(char *text, struct features *feat) {
    /* TODO: Ortak kod */
	unsigned long kelime_uzunlugu = 0;
	unsigned long toplam_kelime_sayisi= 0;
	char* wordpoint[25];
	char* word[25];
	int farkli_kelime = 0;
	int bir_defa_gecen = 0;
	float hapax;
	float ttr;
	float awl;
	float awps;
	float compl;
	int sentence_counter = 0;
	int phrase_counter = 0;
	struct node* w = NULL;
	struct node* w2 = NULL;
	struct node* hash_table[TABLO];
	struct node* hash_tablepoint[TABLO];
	memset(hash_table,0,sizeof(hash_table));
	memset(hash_tablepoint,0,sizeof(hash_tablepoint));
	char * noktasiz_text = text;



	while(1){
			if(sscanf(text,"%s",wordpoint)!= 1) break;
			text+=strlen(wordpoint)+1;
			if(strcmp("-",wordpoint) != 0){
			strtok(wordpoint,"---_'\" \n\t\r");
			printf("%s\n",wordpoint);
			w2 = add_word(&hash_tablepoint,wordpoint);
			w2->count++;
			}

	}

	for(int m  = 0 ;m<TABLO;m++){
				while(hash_tablepoint[m] != NULL){
					int kelimeuzunlugu;

//				printf("%s = ",hash_tablepoint[m]->word);
//				printf("%d\n",hash_tablepoint[m]->count);
					kelimeuzunlugu = strlen(hash_tablepoint[m]->word);
					if(hash_tablepoint[m]->word[kelimeuzunlugu-1] == '.' ||
						hash_tablepoint[m]->word[kelimeuzunlugu-1] == '!' ||
						hash_tablepoint[m]->word[kelimeuzunlugu-1] == '?'||
						hash_tablepoint[m]->word[kelimeuzunlugu-1] == ')'){

						if(strcmp("Mr.",hash_tablepoint[m]->word) != 0 &&
							strcmp("Mrs.",hash_tablepoint[m]->word) != 0 &&
							strcmp("etc.",hash_tablepoint[m]->word) != 0 &&
							strcmp("-",hash_tablepoint[m]->word) != 0 ){
							sentence_counter += hash_tablepoint[m]->count;
//							printf("Sentence counter:%d\n",sentence_counter);
						}

					}

					if(hash_tablepoint[m]->word[kelimeuzunlugu-1] == ';' ||
						hash_tablepoint[m]->word[kelimeuzunlugu-1] == ':' ||
						hash_tablepoint[m]->word[kelimeuzunlugu-1] == ',' ||
						hash_tablepoint[m]->word[kelimeuzunlugu-1] == '-'){
							phrase_counter += hash_tablepoint[m]->count;
//							printf("Phrase counter :%d\n",phrase_counter);
					}

					hash_tablepoint[m] = hash_tablepoint[m]->next;
				}
	}


	while(1){
		if(sscanf(noktasiz_text,"%s",word)!= 1){
			break;
		}

		noktasiz_text+=strlen(word)+1;
		cleanup(word);
		//printf("%s\n",word);
		w = add_word(&hash_table,word);
		w->count++;
}




	for(int m  = 0 ;m<TABLO;m++){
			while(hash_table[m] != NULL){
//				printf("%s = ",hash_table[m]->word);
//				printf("%d\n",hash_table[m]->count);

				//features hesapları
				farkli_kelime++;
				if(hash_table[m]->count == 1) bir_defa_gecen++;
				unsigned long v1 = strlen(hash_table[m]->word);
				unsigned long v2 = hash_table[m]->count;


				kelime_uzunlugu += v1 * v2;
				toplam_kelime_sayisi  += (unsigned long)hash_table[m]->count;
				hash_table[m] = hash_table[m]->next;

			}
	}

	printf("Kelime sayısı:%d\n",toplam_kelime_sayisi);
	printf("Cümle sayısı:%d\n",sentence_counter);
	printf("phrase counter :%d\n",phrase_counter);
	awl = (float)kelime_uzunlugu /(float)toplam_kelime_sayisi;
	hapax = (float)bir_defa_gecen/(float)toplam_kelime_sayisi;
	ttr = (float)farkli_kelime/(float)toplam_kelime_sayisi;
	awps = (float)toplam_kelime_sayisi/(float)sentence_counter;
	compl = ((float)phrase_counter+(float)sentence_counter)/(float)sentence_counter;

	//Her cümle aslında aynı zamanda bir cümle parçacığıdır.



	feat->avg_word_length = (double)awl;
	feat->hapax = (double)hapax ;
	feat->ttr = (double)ttr ;
	feat->avg_word_per_sentence = (double)awps ;
	feat->complexity = (double)compl ;


#ifdef WITH_UTHASH
    /* TODO: Hash kullanarak kelime listesini
     * gezip ilgili sayaclari hesaplayin. Gezdikce
     * dugumleri HASH_DEL() ile temizleyip, mevcut
     * dugumun char* uyesini ve dugumun kendisini++
     * free() ile iade etmelisiniz.*/
#else
    /* TODO: Bagli liste kullanarak kelime listesini
     * gezin. Gezdikce dugumlerin char* uyesini ve
     * kendisini free() ile iade etmelisiniz. */
#endif
    
    /* TODO: Ortak kod. feat yapisinin uyelerini artik doldurabilirsiniz. */
}

