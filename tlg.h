#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG; /* tipurile Celula, Lista  */

typedef struct {
	char* cuv;
	int lungime;
  int frecventa;
} TCuv;

typedef struct {
  int frecventa;
  char* cuv;
} TcelSublista;

typedef struct {
  int lungime;
  TLG sblista;
} Tcampinfo;

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */
typedef int (*SCMP)(void*,void*,int);

int Ins_IncLG(TLG*, void*);  /*- inserare la inceput reusita sau nu (1/0) -*/
int InsOrd(TLG *aL, void *elem, TFCmp cmp );
int compara_lungimi(void* e1, void* e2);
int cmpcuvant(void * e1, void * e2);
int cmpcuvant2(void * e1, void * e2);
int CautaTLG( TLG L, void* ref, TFCmp cmpcuvant );
void EliminaCuvListaCuv ( TLG *aL, void* ref, TFCmp identic);
void InitFrecventaUpdate ( TLG *aL);
void DistrugeLG(TLG* aL, TF fe); /* distruge lista */
void DistrugeCuv(void* el);
void Afisare(TLG*, TF);
void afisareListaCuv(void * element);
int InsOrdUnica(TLG *aL, void *elem, TFCmp cmp );
int InsOrdUnicaSbl(TLG *aL, void *elem, TFCmp cmp );
#endif