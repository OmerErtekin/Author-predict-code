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
	int farkli_kelime = 0;
	int bir_defa_gecen = 0;
	float hapax;
	float ttr;
	float awl;
	float awps;
	float compl;
	int cumle_sayisi = 0;
	int parcacik_sayisi = 0;



	  char* wordpoint[25];
		char* word[25];
		struct node* hash_table[TABLO];
		struct node* hash_tablepoint[TABLO];
		memset(hash_table,0,sizeof(hash_table));
		memset(hash_tablepoint,0,sizeof(hash_tablepoint));
		struct node* w = NULL;

		struct node* w2 = NULL;
		char * noktasiz_text = text;
		while(1){
						if(sscanf(text,"%s",wordpoint)!= 1) break;
						text+=strlen(wordpoint)+1;
						//printf("%s\n",wordpoint);
						strtok(wordpoint,"---_'\" \n\t\r");
						w2 = add_word(&hash_tablepoint,wordpoint);
						w2->count++;

				}

				for(int m  = 0 ;m<TABLO;m++){
							while(hash_tablepoint[m] != NULL){
								int kelimeuzunlugu;

			//				printf("%s = ",hash_tablepoint[m]->word);
			//				printf("%d\n",hash_tablepoint[m]->count);
								kelimeuzunlugu = strlen(hash_tablepoint[m]->word);
								if(hash_tablepoint[m]->word[kelimeuzunlugu-1] == '.' ||
									hash_tablepoint[m]->word[kelimeuzunlugu-1] == '!' ||
									hash_tablepoint[m]->word[kelimeuzunlugu-1] == '?'){

									if(strcmp("Mr.",hash_tablepoint[m]->word) != 0 &&
										strcmp("Mrs.",hash_tablepoint[m]->word) != 0 &&
										strcmp("etc.",hash_tablepoint[m]->word) != 0 &&
										strcmp("-",hash_tablepoint[m]->word) != 0 ){
										cumle_sayisi += hash_tablepoint[m]->count;
			//							printf("Sentence counter:%d\n",cumle_sayisi);
									}

								}

								if(hash_tablepoint[m]->word[kelimeuzunlugu-1] == ';' ||
									hash_tablepoint[m]->word[kelimeuzunlugu-1] == ':' ||
									hash_tablepoint[m]->word[kelimeuzunlugu-1] == ',' ||
									hash_tablepoint[m]->word[kelimeuzunlugu-1] == '-'){
										parcacik_sayisi += hash_tablepoint[m]->count;
			//							printf("Phrase counter :%d\n",parcacik_sayisi);
								}
								hash_tablepoint[m] = hash_tablepoint[m]->next;
							}
				}

				parcacik_sayisi+=cumle_sayisi; //her cümle bir parçadır.

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
//							printf("%s = ",hash_table[m]->word);
//							printf("%d\n",hash_table[m]->count);

							//features hesapları
							farkli_kelime++;
							if(hash_table[m]->count == 1){
								bir_defa_gecen++;
							}
							unsigned long v1 = strlen(hash_table[m]->word);
							unsigned long v2 = hash_table[m]->count;


							kelime_uzunlugu += v1 * v2;
							if((hash_table[m]->word)!=0){
							toplam_kelime_sayisi  += (unsigned long)hash_table[m]->count;
							hash_table[m] = hash_table[m]->next;

							}
						}

				}

				hash_free(hash_table);
				hash_free(hash_tablepoint);




#ifdef WITH_UTHASH


#else
//		cumle_sayisi=-1;
//	    struct node *list=NULL;
//		char *segment1,*segment2,*segment3,*sptr1,*sptr2,*sptr3,*copy1,*copy2,*copy3;
//		segment1=strtok_r(text,".!?",&sptr1);
//		while(segment1){
//			copy1=strdup(segment1);
//			cumle_sayisi++;
//			segment2=strtok_r(segment1,",;:",&sptr2);
//			while(segment2){
//				copy2=strdup(segment2);
//				parcacik_sayisi++;
//				segment3=strtok_r(segment2," -,.!?\n",&sptr3);
//				while(segment3){
//					copy3=strdup(segment3);
//					//cleanup(copy3);
//					if(copy3 != '\0') list=add_word(list,copy3);
//					segment3=strtok_r(NULL,"-,.!?\n ",&sptr3);
//
//				}
//				segment2=strtok_r(NULL,",;:",&sptr2);
//
//
//			}
//
//			segment1 = strtok_r(NULL , ".!?", &sptr1);
//
//		}
//		while(list!=NULL){
//			toplam_kelime_sayisi += list->count;
//			kelime_uzunlugu += strlen(list->word)*list->count;
//			farkli_kelime++;
//			if(list->count == 1) bir_defa_gecen++;
//			list = list->next;
//
//
//		}
//		free(segment1);
//		free(segment2);
//		free(segment3);
//		free(copy1);
//		free(copy2);
//		free(copy3);


#endif
    
    /* TODO: Ortak kod. feat yapisinin uyelerini artik doldurabilirsiniz. */
//		printf("Kelime sayısı:%d\n",toplam_kelime_sayisi);
//		printf("Cümle sayısı:%d\n",cumle_sayisi);
//		printf("phrase counter :%d\n",parcacik_sayisi);

		awl = (float)kelime_uzunlugu /(float)toplam_kelime_sayisi;
		hapax = (float)bir_defa_gecen/(float)toplam_kelime_sayisi;
		ttr = (float)farkli_kelime/(float)toplam_kelime_sayisi;
		awps = (float)toplam_kelime_sayisi/(float)cumle_sayisi;
		compl = (float)parcacik_sayisi/(float)cumle_sayisi;




		feat->avg_word_length = (double)awl;
		feat->hapax = (double)hapax ;
		feat->ttr = (double)ttr ;
		feat->avg_word_per_sentence = (double)awps ;
		feat->complexity = (double)compl ;
}

