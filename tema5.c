#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Melodie {
    int id;
    int durata;
    int nrDescarcari;
    char* titlu;
    char* artist;
    char gen;
};
typedef struct Melodie Melodie;

struct Nod {
    Melodie info;
    struct Nod* next; //pointer la urmatorul nod
    struct Nod* prev; //pointer la nodul precedent
};
typedef struct Nod Nod;

struct ListaDubla {
    Nod* first;
    Nod* last;
    int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

Melodie initializareMelodie(int id, int durata, int nrDescarcari, const char* titlu, const char* artist, char gen) {
    Melodie m;
    m.id = id;
    m.durata = durata;
    m.nrDescarcari = nrDescarcari;

    m.titlu = (char*)malloc(strlen(titlu) + 1);
    strcpy(m.titlu, titlu);

    m.artist = (char*)malloc(strlen(artist) + 1);
    strcpy(m.artist, artist);

    m.gen = gen;
    return m;
}

void afisareMelodie(Melodie m) {
    printf("ID:%d\n", m.id);
    printf("Durata:%d sec\n", m.durata);
    printf("Numar descarcari: %d\n", m.nrDescarcari);
    printf("Titlu:%s\n", m.titlu);
    printf("Artist:%s\n", m.artist);
    printf("Gen: %c\n", m.gen);
    printf("--------------\n");
}

void afisareListaDeLaInceput(ListaDubla lista) {
    Nod* p = lista.first; //incepem cu primul nod
    while (p) { //cat timp p!=NULL apelam functia afisare si parcurgem catre finalul listei
        afisareMelodie(p->info);
        p = p->next;
    }
}

void afisareListaDeLaSfarsit(ListaDubla lista) {
    Nod* p = lista.last; //incepem cu ultimul nod
    while (p) { //cat timp p!=NULL apelam functia afisare si parcurgem catre inceputul listei
        afisareMelodie(p->info);
        p = p->prev;
    }
}

void adaugaLaSfarsit(ListaDubla* lista, Melodie melodieNoua) {
    // ListaDubla* pointer ca sa putem modifica first/last/nrNoduri
    Nod* nou = (Nod*)malloc(sizeof(Nod)); //alocam memorie pt un nod nou
    nou->info = melodieNoua; //copiem structura in nodul nou
    nou->next = NULL; //pt ca va fi ultimul nu exista next
    nou->prev = lista->last; //nodul nou se leaga de fostul ultim nod

    if (lista->last != NULL) {
        lista->last->next = nou; //daca exista utimul nod, actualizam legatura inainte
    }
    else {
        lista->first = nou; //daca lista e goala, noul nod devine si primul
    }

    lista->last = nou; //noul nod devine si ultimul
    lista->nrNoduri++; //creste nr de noduri
}

void adaugaLaInceput(ListaDubla* lista, Melodie melodieNoua) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = melodieNoua;
    nou->prev = NULL; //pt ca va fi primul nu exista prev
    nou->next = lista->first; // se leaga de fostul prim nod

    if (lista->first != NULL) {
        lista->first->prev = nou; //daca exista primul nod, actualizam legatura inapoi
    }
    else {
        lista->last = nou; //daca lista e goala, noul nod devine si ultimul
    }

    lista->first = nou; //noul nod devine si primul
    lista->nrNoduri++; //creste nr de noduri
}


void stergeMelodieDupaId(ListaDubla* lista, int id) {

    //verificam daca lista este goala
    if (lista->first == NULL) {
        return;
    }

    Nod* p = lista->first; //incepem cautarea de la primul nod

    //cautam melodia dupa id
    while (p != NULL && p->info.id != id) {
        p = p->next;
    }

    //nu am gasit melodia
    if (p == NULL) {
        return;
    }

    //actualizam primul nod
    if (p->prev == NULL) {

        lista->first = p->next;

        if (lista->first != NULL) {
            lista->first->prev = NULL;
        }
    }
    else {
        p->prev->next = p->next;
    }

    //actualizam ultimul nod
    if (p->next == NULL) {
        lista->last = p->prev;

        if (lista->last != NULL) {
            lista->last->next = NULL;
        }
    }
    else {
        p->next->prev = p->prev;
    }

    //eliberam memoria
    if (p->info.titlu != NULL) {
        free(p->info.titlu);
    }

    if (p->info.artist != NULL) {
        free(p->info.artist);
    }
    free(p);

    //actualizam numar noduri
    lista->nrNoduri--;
}

char* getTitluMelodieCuNrMaximDescarcari(ListaDubla lista) {

    //verificam lista goala
    if (lista.first == NULL) {
        return NULL;
    }
    Nod* max = lista.first;
    Nod* p = lista.first->next;

    //cautam melodia cu nr maxim de descarcari
    while (p) {

        if (p->info.nrDescarcari >
            max->info.nrDescarcari) {
            max = p;
        }
        p = p->next;
    }

    //alocam memorie + creare copie pentru titlu
    char* titlu =(char*)malloc(strlen(max->info.titlu) + 1);
    strcpy(titlu, max->info.titlu);
    return titlu;
}

float calculeazaDurataMedie(ListaDubla lista) {

    
    if (lista.nrNoduri == 0) {
        return 0;
    }
    int suma = 0;
    Nod* p = lista.first;

    //calculam suma pt durata
    while (p) {
        suma += p->info.durata;
        p = p->next;
    }
    return (float)suma / lista.nrNoduri;

}

void dezalocareListaDubla(ListaDubla* lista) {

    Nod* p = lista->first;

    //parcurgem si eliberam memoria
    while (p) {
        Nod* aux = p;
        p = p->next;

        //se elibereaza campurile alocate dinamic
        if (aux->info.titlu != NULL) {
            free(aux->info.titlu);
        }
        if (aux->info.artist != NULL) {
            free(aux->info.artist);
        }
        free(aux);
    }

    //resetam lista
    lista->first = NULL;
    lista->last = NULL;
    lista->nrNoduri = 0;
}

int main() {

    ListaDubla lista;
    lista.first = NULL;
    lista.last = NULL;
    lista.nrNoduri = 0;

    adaugaLaSfarsit(&lista, initializareMelodie(1, 210, 45000, "Independent", "Deliric", 'R'));
    adaugaLaSfarsit(&lista, initializareMelodie(2, 180, 72000, "Acele", "Carlas", 'P'));
    adaugaLaInceput(&lista, initializareMelodie(3, 240, 150000, "Cosmos", "Irina Rimes", 'P'));
    adaugaLaSfarsit(&lista, initializareMelodie(4, 200, 38000, "A venit politia", "Theo R", 'M'));

    printf("Afisare de la inceput:\n");
    afisareListaDeLaInceput(lista);

    printf("Afisare de la sfarsit:\n");
    afisareListaDeLaSfarsit(lista);

    printf("Durata medie este:%.2f\n",
        calculeazaDurataMedie(lista));

    char* titluMax =getTitluMelodieCuNrMaximDescarcari(lista);

    if (titluMax != NULL) {
        printf(
            "Melodia cu cele mai multe descarcari este:%s\n",titluMax);
        free(titluMax);
    }

    printf("\nStergere melodie cu id 2:\n");
    stergeMelodieDupaId(&lista, 2);
    afisareListaDeLaInceput(lista);


    dezalocareListaDubla(&lista);


    return 0;
}