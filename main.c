/*DOBRE EMILIA ILIANA - 315CB*/

#include <stdio.h>
#include "tlg.h"
#include "thash.h"
#include <string.h>

void InitUpdateListaCuv ( TLG* listaCuv, char* input ) {
    char* sep = " 12345678""""90:;,./?+=_)'(*&^$#@!`~\n";
    char* cuv = strtok(input+7, sep);
    while ( cuv != NULL ){
        if (cuv[strlen(cuv) - 1] == '\n')
		    cuv[strlen(cuv) - 1] = '\0';

        if ( strlen(cuv) >= 3 ) {
		    TCuv * cuvant = calloc(1,sizeof(TCuv));
		    if (cuvant == NULL)
		    return ;
		    cuvant->cuv = (char*)calloc(100, sizeof(char));
		    memcpy(cuvant->cuv, cuv, strlen(cuv));
		    cuvant->lungime = strlen(cuv);
		    InsOrd(listaCuv, (void*)cuvant, compara_lungimi);
        }
        cuv = strtok(NULL, sep);
    }
}

//fct care initializeaza frecventele
void InitFrecventaUpdate ( TLG *listaCuv ) {
    TLG l = *listaCuv;
    while ( l != NULL ) {
        ((TCuv*)l->info)->frecventa = CautaTLG(*listaCuv, l->info, cmpcuvant );
        l = l->urm;
    }
    l = *listaCuv;
}



int main(char* argc, char**argv) 
{
    TH* h = NULL;
    FILE* f = fopen(argv[1], "rt");

    //citesc fiecare rand din input:
    //bag totul intr-un TLG ajutator pt a stii lungimea,fz, cuv pt fiecare cuv
    //TLG ul se schimba odata cu fiecare insert introdus

    TLG listaCuv = NULL;    
    char input[100];
    size_t M = ('Z'-'A' + 1);
    h = AlocaTH(M, codHash);

    while ( fgets(input, 100, f) != NULL ) {
        if ( input[strlen(input)-1] == '\n')
            input[strlen(input)-1] = '\0';
        if ( input[0] == 'i' ) {
            InitUpdateListaCuv(&listaCuv, input);
            InitFrecventaUpdate(&listaCuv);
            h = InitUpdateTH(h, listaCuv, cmpcuvant);
            
            
        } else {
            
            if ( strcmp(input, "print") == 0 )
                AfiTH(h, AfisareCampInfo);

            if ( strncmp(input, "print ", 6) == 0 ) 
                if ( (input[6] - '\0') >= 65 ) {
                    char lit = input[6];
                    int lung = atoi(&input[8]);
                    //printf("%c %d\n", lit, lung);
                    CautaTHDupaLitera(h, lit, lung);
                } else {
                    int aparitii = atoi(&input[6]);
                    CautaTHDupaFz(h, aparitii);
                }
        }
    }
    
    fclose(f);
    //dezaloc lista cuvinte
    DistrugeLG(&listaCuv, DistrugeCuv );
    //dezaloc hash
    //DistrTH(&h, DistrugeCampinfo);
    
    return 0;
}

int strcmpins ( char*s1, char* s2, int lungime) {
    int ok = 0, dif = 0;
    for ( int i = 0; i < lungime; i++ ) {
        dif = (s1[i] - '\0')- (s2[i] - '\0');
        if ( dif == 0) ok++;
    }
    if ( ok == lungime ) {
        return 1; //sunt egale
    } else {
        return 0; //nu sunt egale
    }
}


