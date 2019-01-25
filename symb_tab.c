#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symb_tab.h"

supporto *current = NULL;
tratto *tratt_list = NULL;
ciclista *controllo = NULL;
int n_ciclisti = 0;
int i = 0;
int conta_tappe;

unsigned int hash (char *s){
	int h = 0;
	for(;*s!='\0';s++)
		h = (127*h+*s)%HASHSIZE;
		return h;
}

ciclista *lookup(char *s){
		ciclista *c;
		for(c = hashtable[hash(s)]; c!= NULL; c = c->next)
			if(strcmp(s,c->codice) == 0)
				return c;
		return NULL;
}

ciclista *ins_ciclista(char *codice, char *nome, char *squadra, char *pettorina){
		ciclista *c;
		c = (ciclista *)malloc(sizeof(*c));
		unsigned hashval;
		if ((c = lookup(pettorina)) == NULL){
			if ((c = (ciclista *)malloc(sizeof(*c))) == NULL)
				return NULL;
			c->nome = strdup(nome);
			c->codice = strdup(codice);
			c->squadra = strdup(squadra);
			c->pettorina = strdup(pettorina);
			hashval = hash(pettorina);
			c->next = hashtable[hashval];
			hashtable[hashval] = c;
		}
		return c;
}

tratto *ins_tratto(char *data, char *c_partenza, char *c_arrivo){
		tratto *t;
		t = (tratto *)malloc(sizeof(*t));
		t->data = data;
		t->citta_p = c_partenza;
		t->citta_a = c_arrivo;
		t->s = current;
		t->next = tratt_list;
		tratt_list = t;
		return t;
}

supporto *ins_supporto(char *pettorina, int tempo){
	controllo = lookup(pettorina);
	if(controllo == NULL){
		printf("Errore\n");
	}
	else{
		if(i < n_ciclisti){
			supporto *tmp;
			tmp = (supporto *)malloc(sizeof(*tmp));
			tmp->tempo_tratto = tempo;
			tmp->tempo_totale = tempo;
			tmp->pettorina = strdup(pettorina);
			tmp->next = current;
			current = tmp;
			i++;
		}
		else{
			while(current != NULL){
				if(strcmp(current->pettorina,pettorina) == 0){
					current->tempo_tratto = tempo;
					current->tempo_totale += tempo;
				}
				else{
					current = current->next;
				}
			}
			current = temp;
		}
	}
}
void conta_tappe(char *c_partenza,char *c_arrivo){
	char *tempp = c_partenza;
	char *tempa	= c_arrivo;
	if()
	conta_tappe++;
}
