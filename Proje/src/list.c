#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define KATSAYI 31
#define TABLOBOYU 7919

unsigned long hash_compute(const char* str){
	unsigned long hash = 0;
	while(*str){
		hash = (hash*KATSAYI)+ *str;
		str++;
	}
	return hash % TABLOBOYU;
}



struct node* add_word(struct node **list, char *word) {
  		struct node *current = NULL;
   	 int hash_code = hash_compute(word);
		 struct node *result = list[hash_code];

		  		for(current = result;current != NULL;current = current->next){
		  		    if(strcmp(current->word,word) == 0){
		  		      	    return current;
		  		      	      }
		  		      	      	}

		  			current = (struct node*) malloc(sizeof(struct node));
		  		    if(current){
		  		      	    current->count = 0;
		  		      	    current->word = strdup(word);
		  		      	    current->next = result;
		  		      	    list[hash_code] = current;
		  		      	    return current;

		  		      	 }

		  		      	 return NULL;

#ifdef WITH_UTHASH
  		/* TODO: Hash kodu */




#else
    /* TODO: Bagli liste kodu */
//      	      	current = list;
//      	      	while(current != NULL){
//      	      		if(strcmp(word,current->word) == 0){
//      	      			current->count++;
//      	      			break;
//      	      		}
//      	      		current = current->next;
//      	      	}
//      	      	if(current == NULL){
//      	      		struct node* new_node =malloc(sizeof(struct node));
//      	      		new_node->count=1;
//      	      		new_node->word=strdup(word);
//      	      		new_node->next = list;
//      	      		list = new_node;
//      	      	}
#endif
      	      	return list;


}
