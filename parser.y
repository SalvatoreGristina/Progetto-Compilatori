%{
#include <stdio.h>
#include "sym_tab.h"
int yylex();
void yyerror (char const*);
%}
%union{
  char *stringa;
  int intero;
}
%error-verbose
%token <stringa> DATA PAROLE CODICE D_TAPPA PETTORINA
%token <intero> NUMERO ORA MINUTO SECONDO
%token DPN SEP1 SEP2 SEP3 TRAT ARR PARA PARC VIR
%start Input
%%
Input: DATA SEP1 Sezione1 SEP2 SEP3 Sezione2
  ;
Sezione1: L_ciclisti
  ;
L_ciclisti: Ciclisti
  | L_ciclisti Ciclisti
  ;
Ciclisti: PARA CODICE VIR PAROLE VIR PAROLE VIR PETTORINA PARC {ins_ciclista($2,$4,$6,$8);}
  ;
Sezione2: L_tratti
  ;
L_tratti: Tratti
  | L_tratti Tratti
  ;
Tratti: DATA TRAT PAROLE TRAT PAROLE TRAT L_supporto {ins_tratto($1,$3,$5);}
  ;
L_supporto: Supporto
  | L_supporto Supporto
  ;
Supporto: PARA PETTORINA DPN ORE DPN MINUTO DPN SECONDO {ins_supporto($2,(($4*3600)+($6*60)+$8));}
  ;
