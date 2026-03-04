#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produs {
    int id;
    int stoc;
    float pret;
    char* nume;
    char* furnizor;
    char categorie;
};
typedef struct Produs Produs;

void afisareProdus(Produs p) { //transmitem p prin valoare
    printf("ID: %d\n", p.id);
    printf("Stoc: %d\n", p.stoc);
    printf("Pret: %.2f\n", p.pret);
    printf("Nume: %s\n", p.nume);
    printf("Furnizor: %s\n", p.furnizor);
    printf("Categorie: %c\n\n", p.categorie);//%c este pentru char
}

void afisareVectorProduse(Produs* produse, int nrProduse) {
    for (int i = 0; i < nrProduse; i++) {
        afisareProdus(produse[i]);
    }
}

void adaugaProdusInVector(Produs** produse, int* nrProduse, Produs produsNou) {
    Produs* aux = (Produs*)malloc(sizeof(Produs) * ((*nrProduse) + 1));

    for (int i = 0; i < *nrProduse; i++) {
        aux[i] = (*produse)[i];
    }

    aux[*nrProduse] = produsNou; //adaugam elementul nou
    free(*produse);
    *produse = aux;
    (*nrProduse)++;
}

Produs citireProdusDinFisier(FILE* file) {
    Produs p;
    char buffer[200];
    char sep[] = ",;\n";//separatorii pt functia strtok

    fgets(buffer, 200, file);//fgets citeste o linie din fisier in buffer
    //strtok ia primul token pana la separator
    p.id = atoi(strtok(buffer, sep));//atoi = ASCII to int
    p.stoc = atoi(strtok(NULL, sep));
    p.pret = atof(strtok(NULL, sep));

    char* aux = strtok(NULL, sep);
    p.nume = (char*)malloc(strlen(aux) + 1);
    strcpy(p.nume, aux);

    aux = strtok(NULL, sep);
    p.furnizor = (char*)malloc(strlen(aux) + 1);
    strcpy(p.furnizor, aux);

    p.categorie = strtok(NULL, sep)[0];

    return p;
}

Produs* citireVectorProduseDinFisier(const char* numeFisier, int* nrProduseCitite) {
    FILE* file = fopen(numeFisier, "r"); //deschidem fisierul in modul read "r"
    Produs* produse = NULL;
    *nrProduseCitite = 0; //initial vectorul are 0 elemente

    if (file != NULL) {
        while (!feof(file)) { //cat timp nu am ajuns la finalul fisierului
            adaugaProdusInVector(&produse, nrProduseCitite, citireProdusDinFisier(file));
        } //&produse transmitem prin adresa
        fclose(file);
    }

    return produse;//se returneaza adresa vectorului
}

void dezalocareVectorProduse(Produs** vector, int* nrProduse) {
    for (int i = 0; i < *nrProduse; i++) {
        if ((*vector)[i].nume != NULL) {
            free((*vector)[i].nume);
        }
        if ((*vector)[i].furnizor != NULL) {
            free((*vector)[i].furnizor);
        }
    }//am eliberat memoria pt nume si furnizor

    free(*vector); //stergem vectorul de structuri
    *vector = NULL; //stergem dangling pointers
    *nrProduse = 0; //setam nr de produse la 0
}

int main() {
    int nrProduse = 0;
    Produs* produse = citireVectorProduseDinFisier("produse.txt", &nrProduse);

    afisareVectorProduse(produse, nrProduse);
    dezalocareVectorProduse(&produse, &nrProduse);

    return 0;
}