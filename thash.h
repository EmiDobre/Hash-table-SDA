#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFHash)(void*);

typedef struct
{
    size_t M;
    TFHash fh;
    TLG *v;
} TH;

//fct tabel:
TH* AlocaTH(size_t M, TFHash fh);
int codHash(void * element);
void DistrTH(TH**aa, TF fe);
void AfiTH(TH*a, TF afiEl);
int strcmpins ( char*s1, char* s2, int lungime);
TH* InitUpdateTH(TH* h, TLG listaCuv, TFCmp fcmp);
int compara_frecventa(void* e1, void* e2);
void AfisareCampInfo(void* element);
void afisareCelulaSublista(void* element);
int cmpcuvantSUBLISTE(void * e1, void * e2);
int* copiaza_vect(int* lungimi, int* copie);
int compara_lungimiCAMPINFO(void* e1, void* e2);
void CautaTHDupaLitera ( TH* h, char lit, int lung);
void AfisareCampInfoENT(void* element);
void CautaTHDupaFz(TH* h, int aparitii);
int ExistaFZ(TLG p, int aparitii);
int ExistaFZinCINFO( Tcampinfo* l, int fz);
void DistrugeCampinfo(void* el);
void DistrugeCelSublista(void* el);
#endif