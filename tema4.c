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



int main() {
    Nod* cap = NULL;

    adaugaStudentInLista(&cap, initializareStudent(1, 20, 8.5f, "Ana", "CSIE", '1'));
    adaugaStudentInLista(&cap, initializareStudent(2, 21, 9.3f, "Mihai", "Cibernetica", '2'));
    adaugaStudentLaInceput(&cap, initializareStudent(3, 19, 7.9f, "Ioana", "CSIE", '1'));

    afisareListaStudenti(cap);


    return 0;
}