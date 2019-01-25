#define HASHSIZE 101

typedef struct c{
    char *nome;
    char *codice;
    char *squadra;
    char *pettorina;
    ciclista *next;
}ciclista;

typedef struct t{
    char *data;
    char *citta_p;
    char *citta_a;
    supporto *s;
    tratto *next;
}tratto;

typedef struct s{
    int tempo_tratto;
    int tempo_totale;
    char pettorina;
    ciclista *c;
    supporto *next;
}supporto;

ciclista *hashtable[HASHSIZE];

unsigned int hash(char *p);
ciclista *lookup(char *p);
ciclista *ins_ciclista(char *codice, char *nome, char *squadra, char *pettorina);
tratto *ins_tratto(char *data, char *citta_p, char *citta_a);
supporto *ins_supporto(char *pettorina, int tempo);
void ordinamento(supporto *start);
void swap(supporto *a, supporto *b);
