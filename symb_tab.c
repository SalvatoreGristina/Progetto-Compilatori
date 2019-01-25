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
					ordinamento(current,0);
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

void ordinamento(supporto *start,int tipo){
	int swapped, i;
	supporto *ptr1;
	supporto *rptr = NULL;

	/* Checking for empty list */
	if (start == NULL)
		return;
	if (tipo == 0){
	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != rptr)
		{
			if (ptr1->tempo_tratto > ptr1->next->tempo_tratto)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		rptr = ptr1;
	}
	while (swapped);
}
if (tipo == 1){
do
{
	swapped = 0;
	ptr1 = start;

	while (ptr1->next != rptr)
	{
		if (ptr1->tempo_tratto > ptr1->next->tempo_tratto)
		{
			swap(ptr1, ptr1->next);
			swapped = 1;
		}
		ptr1 = ptr1->next;
	}
	rptr = ptr1;
}
while (swapped);
}
}

void swap(supporto *a, supporto *b)
{
	int temp = a->tempo_totale;
	a->tempo_totale = b->tempo_totale;
	b->tempo_totale = temp;
}

void print_res(){
	int p = 1;
	printf("CLASSIFICA GIORNO %s",tratt_list->data);
	ordinamento(current,1);
}
