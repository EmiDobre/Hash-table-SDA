----------CITIREA----------

*fac un mini parser care citeste din fisier fiecare linie si decide daca introduce in lista auxiliara de cuvinte, apoi in hash, sau afiseaza 

*acest sir este trimis ca parametru in functia de InitUpdateListaCuv unde se creeaza o lista generica cu elemente care au info-ul de tip TCuv, o stuctura care contine cuvantul, lungimea si frecventa sa

*imediat dupa apelul acestei functii se adauga sau actualizeaza frecventa cuvintelor din lista de cuvinte auxiliara

*in ultima faza se va crea tabelul hash din lista de cuvinte creata/actualizata

*in cazul in care comanda introdusa este de genul afisare, "p" se apeleaza cautarile respective pentru cerinta


----------CREAREA TABELULUI HASH----------

*primul pas este crearea listei generice de cuvinte care sparge cu strtok fiecare rand din fisier in cuvinte fara semne de punctuatia sau numere (in afara de - ) si se face inserarea ordonata la inceput dupa lungime

*actualizarea frecventei presupune parcurgerea listei de cuvinte si apelarea functiei de CautareTLG care cauta in lista cuvantul respectiv si intoarce numarul sau de aparitii 

*InitUpdateTH creeaza pentru fiecare vector de TLG uri, lista de subliste, fiecare TLG are campul info de tip TCampinfo- o structura are lungimea cuvantului si un camam doua foruri din cauza posibiliatii de a nu se fi ajuns la o lungimente, aflu pentru fiecare cuvant codul hash corespunzator si creez TCampinfourile pt fiecare (fara subliste, doar dupa lungime, setez campul sublista null)

*inserez ordonat dupa lungime in vectorul de liste dupa codul hash obtinut

*parcurg iar lista de cuvinte, urmand sa inserez si in sublista campului info si sa am lista de subliste completa pt fiecare vector

*am doua foruri din cauza posibiliatii de a nu se fi ajuns la o lungime mai mare decat cele inserate pana atunci

*aflu hashul, iau o lista pt vectorul respectiv din hash, o parcurg si gasesc campulinfo care are lungimea egala cu a cuvantului de bagat in sublista

*il inserez ordonat in sublista campului info dupa frecventa


----------AFISARI----------

*PRINT => afisare hash cu functie de afisare hash si o functie de afisare TLG pt campulINfo care are la randul ei o functie de afisare TLG pentru sublista

*PRINT LITERA LUNGIME => caut in TH dupa codul literei si afisez daca lungimea corespunde cu lungimea din campul lungime al info oului de tip TCampinfo

*PRINT MAX_FRECVENTA => in CautaDupaFZ parcurg fiecare vector din lista

*apelez functia de existenta frecventa care verifica daca in tot TLG pentru un vector din hash am cuvinte de acea frecventa, daca da continui si afisez al catelea este 

*in continuare pt fiecare vector TLG, parcurg si pt fiecare campinfo al elementului din lista vectorului apelez functi a de existenta frecventa campinfocare verfiica daca in sublista acelui campinfo exista  elemente de acea frecventa;  daca da le afisez 
