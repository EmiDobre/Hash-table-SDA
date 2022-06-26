/*DOBRE EMILIA ILIANA - 315CB*/

#include "tlg.h"
#include "thash.h"

//inserare la inceput
int Ins_IncLG(TLG* aL, void* ae)
{
	TLG aux = (TLG)calloc(1, sizeof(TCelulaG));
	if(!aux)
	    return 0;

	aux->info = ae;
	aux->urm = *aL;
	*aL = aux;

	return 1;
}

TLG aloca_celulag(void* x)
{	TLG aux;
  	aux = (TLG)calloc(1,sizeof(TCelulaG));
   	if(!aux) return NULL;
   	
	aux->info = x;
	aux->urm = NULL;
	return aux;
}

int InsOrd(TLG *aL, void *elem, TFCmp cmp )
{
	TLG L = *aL, ant = NULL;
	TLG lista = aloca_celulag(elem);
	if (!lista)
		return 0;

	for (; L; ant = L, L = L->urm) {
		if ( cmp(elem, L->info) > 0 ) { //ins la inceput pt cresc
			lista->urm = L;
			if (ant == NULL) {
				*aL = lista;
			} else {
				ant->urm = lista;
			}
			return 1;
		}
	}
	//la finalul listei aici:
	if (ant == NULL) { //daca lista e nula
		*aL = lista;
	} else {	//lista are doar un el care e mai mic decat elS
		ant->urm = lista;
	} return 1;
}

int InsOrdUnica(TLG *aL, void *elem, TFCmp cmp )
{
	TLG L = *aL, ant = NULL;
	TLG lista = aloca_celulag(elem);
	if (!lista)
		return 0;

	for (; L; ant = L, L = L->urm) {
		if ( cmp(elem, L->info) > 0 ) { //ins la inceput pt cresc
			lista->urm = L;
			if (ant == NULL) {
				*aL = lista;
			} else {
				ant->urm = lista;
			}
			return 1;
		} else {
			if ( cmp(elem, L->info) == 0)
				break;
		}
	}
	//la finalul listei aici:
	if (ant == NULL) { //daca lista e nula
		*aL = lista;
	} else {	//lista are doar un el care e mai mic decat elS
		ant->urm = lista;
	} return 1;
}

int InsOrdUnicaSbl(TLG *aL, void *elem, TFCmp cmp )
{	TLG L = *aL, ant = NULL;
	TLG lista = aloca_celulag(elem);
	if (!lista)
		return 0;

	TcelSublista* element = (TcelSublista*)elem;
	for (; L; ant = L, L = L->urm) {
		TcelSublista* celula = (TcelSublista*)L->info;

		if ( strcmpins(element->cuv, celula->cuv, strlen(element->cuv)) == 1 )
			return 0;

		if ( cmp(elem, L->info) > 0 ) { //ins la inceput pt cresc
			lista->urm = L;
			if (ant == NULL) {
				*aL = lista;
			} else {
				ant->urm = lista;
			}
			return 1;
		}
	}
	//la finalul listei aici:
	if (ant == NULL) { //daca lista e nula
		*aL = lista;
	} else {	//lista are doar un el care e mai mic decat elS
		ant->urm = lista;
	} return 1;
	
}

int compara_lungimi(void* e1, void* e2) {
	TCuv* cuv1 = (TCuv*)e1;
	TCuv* cuv2 = (TCuv*)e2;
	return cuv2->lungime - cuv1->lungime;
}

int compara_lungimiCAMPINFO(void* e1, void* e2) {
	Tcampinfo* c1 = (Tcampinfo*)e1;
	Tcampinfo* c2 = (Tcampinfo*)e2;
	return c2->lungime - c1->lungime;
}

int cmpcuvant(void * e1, void * e2)
{
	TCuv * cuvant1 = (TCuv *) e1;
	TCuv * cuvant2 = (TCuv *) e2;

	if (cuvant1->lungime != cuvant2->lungime )
		return 0;
	if ( strcmpins(cuvant1->cuv, cuvant2->cuv, cuvant1->lungime) == 0 ) { 
		return 0;
	}
	return 1;//acc cuv
}

int cmpcuvantSUBLISTE(void * e1, void * e2) //au lungimi egale
{
	TcelSublista * c1 = (TcelSublista *) e1;
	TcelSublista * c2 = (TcelSublista *) e2;

	if ( strcmpins(c1->cuv, c2->cuv, strlen(c1->cuv)) == 0 ) { 
		return 0;
	}
	return 1;//acc cuv
}


int compara_frecventa(void* e1, void* e2) {
    TcelSublista* cel1 = (TcelSublista*)e1;
	TcelSublista* cel2 = (TcelSublista*)e2;
	int dif = cel1->frecventa - cel2->frecventa;
	if ( dif == 0 ) {
		return strcmp(cel2->cuv, cel1->cuv);	
	} 
	else return dif;
}

int CautaTLG( TLG L, void* ref, TFCmp cmpcuvant ) {
	int frecventa = 0;
	for ( ; L != NULL; L = L->urm ) {
		if ( cmpcuvant(L->info, ref ) == 1 ) {
			frecventa++;
		}
	}
	return frecventa;
}

void Afisare(TLG* aL, TF afiEL)
{
	if(!*aL) {
        //printf("Lista vida\n");
        return;
    }
	for(; *aL; aL = &(*aL)->urm) {
		afiEL((*aL)->info);
		if ( (*aL)->urm != NULL ) 
			printf(", ");
    }

}

void afisareListaCuv(void * element)
{
	TCuv * cuvant = (TCuv *) element;
	printf("%s - %d -fz:%d\n", cuvant->cuv, cuvant->lungime, cuvant->frecventa);
}


void DistrugeCuv(void* el) {
    TCuv* cuv = (TCuv*)el;
    free(cuv->cuv);
    free(cuv);
}


void DistrugeLG(TLG* aL, TF free_elem)
{
	while(*aL != NULL)
    {
        TLG aux = *aL;
        if (!aux)
            return;

        free_elem(aux->info);
        *aL = aux->urm;
        free(aux);
    }
}