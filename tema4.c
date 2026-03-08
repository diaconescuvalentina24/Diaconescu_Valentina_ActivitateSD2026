#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    int varsta;
    float medie;
    char* nume;
    char* facultate;
    char an;
};
typedef struct Student Student; //ca sa nu mai scriem mereu struct Student, e ca un alias

struct Nod {
    Student info;
    struct Nod* next; //pointer la nodul urmator
};
typedef struct Nod Nod;

Student initializareStudent(int id, int varsta, float medie, const char* nume, const char* facultate, char an) {
    Student s;
    s.id = id;
    s.varsta = varsta;
    s.medie = medie;

    s.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(s.nume, nume);

    s.facultate = (char*)malloc(strlen(facultate) + 1);
    strcpy(s.facultate, facultate);

    s.an = an;
    return s;
}

void afisareStudent(Student s) {
    printf("ID: %d\n", s.id);
    printf("Varsta: %d\n", s.varsta);
    printf("Medie: %.2f\n", s.medie);
    printf("Nume: %s\n", s.nume);
    printf("Facultate: %s\n", s.facultate);
    printf("An: %c\n\n", s.an);
}

void afisareListaStudenti(Nod* cap) { //cap = pointer la primul nod din lista
    while (cap != NULL) {
        afisareStudent(cap->info);
        cap = cap->next; //trecem la urmatorul nod
    }
}

void adaugaStudentInLista(Nod** cap, Student studentNou) {
    // Nod** este adresa pointerului la primul nod din lista
    Nod* nou = (Nod*)malloc(sizeof(Nod));//alocam memorie pt un nod nou
    nou->info = studentNou;// se copiaza structura student in nou->info
    nou->next = NULL;
    //daca nu e primul nod adaugat, parcurgem si punem la sfarsit
    if (*cap != NULL) {
        Nod* p = *cap;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = nou;
    }
    else { //daca lista era goala, noul nod devine primul nod (cap)
        *cap = nou;
    }
}

void adaugaStudentLaInceput(Nod** cap, Student studentNou) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = studentNou;
    nou->next = *cap; //urmatorul nod este fostul cap
    *cap = nou; //nodul nou devine primul nod al listei
}

float calculeazaMedieGeneralaStudenti(Nod* cap) {
    float suma = 0;
    int nr = 0;//ne trebuie numarul de madii sa calc media generala

    while (cap) { //echivalent cu while(cap!=NULL)
        suma += cap->info.medie;
        nr++;
        cap = cap->next;
    }

    if (nr > 0) {
        return suma / nr;
    }
    return 0;
}

float calculeazaMediaStudentilorDinFacultate(Nod* cap, const char* facultate) {
    float suma = 0;
    int nr = 0;

    while (cap) {
        if (strcmp(cap->info.facultate, facultate) == 0) {
            //strcmp returneaza 0 cand sirurile sunt egale
            suma += cap->info.medie;
            nr++;
        }
        cap = cap->next;
    }

    if (nr > 0) {
        return suma / nr;
    }
    return 0;
}

void stergeStudentiDinAnul(Nod** cap, char anCautat) {
    //Nod** este adresa pointerului la primul nod, capul listei
    //1. daca nodul cautat este la inceputul listei
    while ((*cap) && (*cap)->info.an == anCautat) {
        //(*cap) este primul nod din lista
        //(*cap)->info.an este campul "an" sin primul nod
        Nod* aux = *cap; //salvam adresa nodului care trebuie sters
        *cap = aux->next; //mutam capul pe urmatorul nod

        //eliberam memoria pt campurile alocate dinamic
        free(aux->info.nume);
        free(aux->info.facultate);
        free(aux);  //eliberam nodul
    }

    //2. daca lista nu devine goala dupa prima stergere
    if (*cap != NULL) {
        Nod* p = *cap; // p = pointer de parcurgere

        while (p != NULL) { //cautam primul nod care are next de sters
            while (p->next != NULL && p->next->info.an != anCautat) {
                p = p->next;
            }

            if (p->next != NULL) { //am gasit un nod care tb sters, p->next
                Nod* aux = p->next; // aux este nodul care va fi sters
                p->next = aux->next; //luam adresa urmatorului nod sa nu pierdem lista

                //eliberam memoria si nodul aux
                free(aux->info.nume);
                free(aux->info.facultate);
                free(aux);
            }
            else {
                //in cazul acesta nu mai exista noduri
                p = NULL;
            }
        }
    }
}

void dezalocareListaStudenti(Nod** cap) {
    while (*cap) {
        Nod* p = *cap;
        *cap = p->next;

        free(p->info.nume);
        free(p->info.facultate);
        free(p);
    }
}


int main() {
    Nod* cap = NULL;

    adaugaStudentInLista(&cap, initializareStudent(1, 20, 8.5f, "Ana", "CSIE", '1'));
    adaugaStudentInLista(&cap, initializareStudent(2, 21, 9.3f, "Mihai", "Cibernetica", '2'));
    adaugaStudentLaInceput(&cap, initializareStudent(3, 19, 7.9f, "Ioana", "CSIE", '1'));
    adaugaStudentInLista(&cap, initializareStudent(4, 22, 6.8f, "Radu", "Marketing", '3'));
    
    afisareListaStudenti(cap);

    printf("Media generala a studentilor este: %.2f\n", calculeazaMedieGeneralaStudenti(cap));

    printf("Media studentilor de la CSIE este: %.2f\n", calculeazaMediaStudentilorDinFacultate(cap, "CSIE"));

    printf("\nStergere studenti din anul 1:\n");
    stergeStudentiDinAnul(&cap, '1');

    afisareListaStudenti(cap);

    dezalocareListaStudenti(&cap);

    return 0;
}