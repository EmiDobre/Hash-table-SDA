/*DOBRE EMILIA ILIANA - 315CB*/

#include "thash.h"
#include "tlg.h"

TH* AlocaTH(size_t M, TFHash fh)
{
    TH* h = (TH *) calloc(1,sizeof(TH));
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLG *) calloc(M, sizeof(TLG));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }
    h->M = M;
    h->fh = fh;
    return h;
}

int codHash(void * element)
{
	TCuv * cuvant = (TCuv *) element;
	char * cuv = cuvant->cuv;
	if ( cuv[0] - '\0' > 96 ) return *cuv - 'a';
	return *cuv - 'A';
}

void AfiTH(TH* ah,TF afi_elem)
{
    TLG p, el;
    int i;
    for(i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
            printf("pos %d: ",i);
            for(el = p; el != NULL; el = el->urm)
                afi_elem(el->info);
            printf("\n");
        }
    }
}

TH* InitUpdateTH(TH* h, TLG listaCuv, TFCmp cmp ) 
{   
    TLG l = listaCuv, copie = listaCuv;
    TCuv* cuvant;
    int cod;
    for ( ; l != NULL; l = l->urm ) {
        cuvant = (TCuv*)calloc(1, sizeof(TCuv));
        if ( cuvant == NULL ) return h;
        memcpy(cuvant, l->info, sizeof(TCuv));
        cod = h->fh(cuvant);
        
        //adaug in fiecare h->v[cod] toate campinfurile info cu lungimea data

        Tcampinfo* campinfo = (Tcampinfo*)calloc(1, sizeof(Tcampinfo));
        campinfo->lungime = cuvant->lungime;
        campinfo->sblista = NULL;
        InsOrdUnica(&h->v[cod], (void*)campinfo, compara_lungimiCAMPINFO);
         
    }
    //in campinfo inserez sublista sa 
    for ( l = copie; l != NULL; l = l ->urm ) {
        cuvant = (TCuv*)calloc(1, sizeof(TCuv));
        if ( cuvant == NULL ) return h;
        memcpy(cuvant, l->info, sizeof(TCuv));
        cod = h->fh(cuvant);
        TcelSublista* celula = (TcelSublista*)calloc(1, sizeof(TcelSublista));
        celula->cuv = (char*)calloc(cuvant->lungime, sizeof(char));
        celula->cuv = cuvant->cuv;
        celula->frecventa = cuvant->frecventa;
        TLG lista = h->v[cod];
        while ( lista != NULL ) {
            Tcampinfo* campinfo = (Tcampinfo*)lista->info;

            if ( campinfo->lungime == strlen(celula->cuv) ) {
                InsOrdUnicaSbl(&((Tcampinfo*)lista->info)->sblista, (void*)celula, compara_frecventa);
            }
            lista = lista->urm;
        }
    }
    return h;
}


//fac functie de afisare pt TLG care are param element de tip campinfo
void AfisareCampInfo(void* element) {
    Tcampinfo* campinfo = (Tcampinfo*)element;
    printf("(%d:", campinfo->lungime);
    if ( campinfo->sblista == NULL ) return;
    else Afisare(&campinfo->sblista, afisareCelulaSublista);
    printf(")"); 
}


void afisareCelulaSublista(void* element){
    TcelSublista* celula = (TcelSublista*)element;
    printf("%s/%d", celula->cuv, celula->frecventa);
}

//fct de cautare in TH elementele cu codul hash egal cu litera data ca param
//le afisez pe cele care au lungimea data ca param
void CautaTHDupaLitera ( TH* h, char lit, int lung) {
    int cod;
    if ( lit - '\0' > 96 ) cod = lit - 'a';
    else cod = lit - 'A';
    TLG el;
    for ( el = h->v[cod]; el != NULL; el = el->urm ) {
        Tcampinfo* campinfo = (Tcampinfo*)el->info;
        if ( campinfo->lungime == lung ) 
            AfisareCampInfoENT(el->info);   
    }
}

void AfisareCampInfoENT(void* element) {
    Tcampinfo* campinfo = (Tcampinfo*)element;
    printf("(%d:", campinfo->lungime);
    if ( campinfo->sblista == NULL ) return;
    else Afisare(&campinfo->sblista, afisareCelulaSublista);
    printf(")\n");
}

int ExistaFZ(TLG p, int aparitii) {
    //caut prin toate coduril
        TLG el = p;
    
            for (el = p ; el != NULL; el = el->urm ) {
                Tcampinfo* campinfo = (Tcampinfo*)el->info;
                TLG sublista = campinfo->sblista;

                TLG camp_cautat = NULL;
                while ( sublista != NULL ) {
                    TcelSublista* celula = (TcelSublista*)sublista->info;
                    
                    if ( celula->frecventa <= aparitii ) 
                        return 1; 
                    sublista = sublista->urm;  
                }
            }
        return 0; 
}


int ExistaFZinCINFO( Tcampinfo* l, int fz) {
    TLG L = l->sblista;
	for ( ; L != NULL; L = L->urm ) {
		if ( ((TcelSublista*)L->info)->frecventa <= fz ) {
			return 1;
		}
	}
	return 0;
}

void CautaTHDupaFz(TH* h, int aparitii) {
    TLG p, el;
    int i;
    for(i = 0; i < h->M; i++) {
        p = h->v[i];
        if(p) {
            if ( ExistaFZ(p, aparitii) == 1) {
                printf("pos%d: ",i);
                for(el = p; el != NULL; el = el->urm) {
                    Tcampinfo* campinfo = (Tcampinfo*)el->info;
                    if (ExistaFZinCINFO(campinfo, aparitii) == 1 ) {
                        printf("(%d: ", campinfo->lungime);
                        TLG sublista = campinfo->sblista;
                        while ( sublista != NULL ) {
                            TcelSublista* celula = (TcelSublista*)sublista->info;
                            if ( celula->frecventa <= aparitii ) {
                                if ( sublista->urm == NULL ) 
                                    printf("%s/%d", celula->cuv, celula->frecventa);
                                else
                                    printf("%s/%d, ", celula->cuv, celula->frecventa);
                            }
                             sublista = sublista->urm;  
                        }
                        printf(")");
                    }
                }
            printf("\n");
            }
        }
    }
}


void DistrTH(TH** ah, TF elib_elem)
{
    TLG * p, el, aux;

    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        for(el = *p; el != NULL; ) {
            aux = el;
            el = el->urm;
            elib_elem(aux->info);
            free(aux);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}

void DistrugeCampinfo(void* el) {
    Tcampinfo* campinfo = (Tcampinfo*)el;
    DistrugeLG(&campinfo->sblista, DistrugeCelSublista);
}

void DistrugeCelSublista(void* el) {
    TcelSublista* celula = (TcelSublista*)el;
    free(celula->cuv);
}