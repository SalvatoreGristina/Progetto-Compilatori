#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symb_tab.h

int n_ciclisti = 0;
int k=0;
int n_tratti=0;
int controllo_bonus=0;
int x=0;
supporto *current=NULL;
ciclista *controllo=NULL;
supporto *tmp=NULL;
tratto *tratt_list=NULL;

unsigned int hash(char *s){
  int h=0;
  for(;*s!='\0';s++){
    h=(127*h+*s)%HASHSIZE;
    }
  return h;
}

ciclista *lookup(char *s){
  ciclista *c=NULL;
  for(c = hashtable[hash(s)]; c != NULL; c = c->next)
    if(strcmp(s,c->pettorina) == 0)
      return c;
    return NULL;
}

ciclista *ins_ciclista(char *codice, char *nome, char *squadra, char *pettorina){
  ciclista *c=NULL;
  unsigned hashval;
  if ((c = lookup(pettorina))==NULL){
    if((c = (ciclista *)malloc(sizeof(*c)))==NULL)
      return NULL;
  c->codice = strdup(codice);
  c->nome = strdup(nome);
  c->squadra = strdup(squadra);
  c->pettorina = strdup(pettorina);
  n_ciclisti++;
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
  controllo = lookup(pettorina); //controllo è un puntatore globale che punta a ciclisti

  if(controllo == NULL){
    printf("Pettorina non trovata.\n" );
  }
  else{
    if(k<n_ciclisti){ //n_ciclisti  è una variabile globale che viene aumentanta ogni volta che viene

      tmp = (supporto *)malloc(sizeof(*tmp));
      tmp->tempo_tratto = tempo;
      tmp->tempo_totale = tempo;
      tmp->pettorina = strdup(pettorina);
      tmp->next = current;
      current = tmp;
      k++;

    } //nell' if ci entreremo solo per la creazione della prima lista che poi sarà aggiornata nei prossimi inserimenti nel while
    else{
      while(current!=NULL){
        if(strcmp(current->pettorina,pettorina)==0){
          current->tempo_tratto = tempo;
          x++;

			if(x==n_ciclisti){
		  	current = tmp;

		  	ordina_tratto(current);
				bonus_posizione(current);

				current->tempo_totale += current->tempo_tratto;
				current->next->tempo_totale += current->next->tempo_tratto;
			  current->next->next->tempo_totale +=  current->next->next->tempo_tratto;

				while(current!=NULL){
		  			current=current->next->next->next;
		  			current->tempo_totale += current->tempo_tratto;
		  			current=current->next;
				}
		  	current=tmp;
				x=0;
			}
		  	current=tmp;
        return current;
        }
        else{
          current = current->next;
        }
      }
        current = tmp;
    }
    if(k==(n_ciclisti)){
    	ordina_tratto(current);
    	bonus_posizione(current);
		  k++;
    }
    return tmp;
  }
}

void print_res(){
  int tempo=0;
  char *nome;
  char *data_tratto = tratt_list->data;
	ordina_tratto(current);
 	printf("Classifica corrente Data: %s\n ",data_tratto);

	while(current!=NULL){
    	controllo=lookup(current->pettorina);
    	nome = controllo->nome;
    	tempo = current->tempo_tratto;

      int h1,m1,s1;

      h1 = (tempo/3600);
      m1 = (tempo -(3600*h1))/60;
      s1 = (tempo -(3600*h1)-(m1*60));

      printf("%s\t\t%d:%d:%d\n",nome,h1,m1,s1);
      current=current->next;
  	}
  	current=tmp;
    ordina_totale(current);
   	printf("\nClassifica Generale:\n");

   	while(current!=NULL){
   	 	controllo=lookup(current->pettorina);
   	 	nome = controllo->nome;
   		tempo = current->tempo_totale;

      int h,m,s;

      h = (tempo/3600);
      m = (tempo -(3600*h))/60;
      s = (tempo -(3600*h)-(m*60));
      printf("%s\t\t%d:%d:%d\n",nome,h,m,s);
      current=current->next;
  	}
  }


void ordina_totale(supporto *start){
  int swapped, i;
  supporto *ptr1;
  supporto *rptr = NULL;

  //Checking for empty list
  if (start == NULL)
    return;

    do{
      swapped = 0;
    	ptr1 = start;

      while (ptr1->next != rptr){
    		if (ptr1->tempo_totale > ptr1->next->tempo_totale){
    		    swap_totale(ptr1, ptr1->next);
    				swapped = 1;
    		}
    		ptr1 = ptr1->next;
    	}
    	rptr = ptr1;
    }
    while (swapped);
}

void ordina_tratto(supporto *start){
  int swapped1, i1;
  supporto *ptr11;
  supporto *rptr1 = NULL;

  //Checking for empty list
  if (start == NULL)
    return;

    do{
    	swapped1 = 0;
    	ptr11 = start;

    	while (ptr11->next != rptr1){
    	   if (ptr11->tempo_tratto > ptr11->next->tempo_tratto){
    				swap_tratto(ptr11, ptr11->next);
    				swapped1 = 1;
    			}
    			ptr11 = ptr11->next;
    	}
    	rptr1 = ptr11;
    }
    while (swapped1);
}


void swap_totale(supporto *a, supporto *b){
  int temp_totale = a->tempo_totale;
  a->tempo_totale = b->tempo_totale;
  b->tempo_totale = temp_totale;

  int temp_tratto = a->tempo_tratto;
  a->tempo_tratto = b->tempo_tratto;
  b->tempo_tratto = temp_tratto;

  char *temp2 = a->pettorina;
  a->pettorina = b->pettorina;
  b->pettorina = temp2;
}

void swap_tratto(supporto *c, supporto *d){
  int temp1 = c->tempo_tratto;
  c->tempo_tratto = d->tempo_tratto;
  d->tempo_tratto = temp1;

  int temp1_totale = c->tempo_totale;
  c->tempo_totale = d->tempo_totale;
  d->tempo_totale = temp1_totale;

  char *temp3 = c->pettorina;
  c->pettorina = d->pettorina;
  d->pettorina = temp3;
}

bonus_posizione(current){
  supporto *bp = current;

  if(controllo_bonus == 0){
    bp->tempo_tratto = bp->tempo_tratto -60; 							bp->tempo_totale = bp->tempo_totale -60;
		bp->next->tempo_tratto = bp->next->tempo_tratto-30; 				bp->next->tempo_totale = bp->next->tempo_totale-30;
	  bp->next->next->tempo_tratto = bp->next->next->tempo_tratto-10; 	bp->next->next->tempo_totale = bp->next->next->tempo_totale-10;
		controllo_bonus = 1;
	 }

  else{
		bp->tempo_tratto = bp->tempo_tratto -60;
		bp->next->tempo_tratto = bp->next->tempo_tratto-30;
		bp->next->next->tempo_tratto = bp->next->next->tempo_tratto-10;
  }
}
