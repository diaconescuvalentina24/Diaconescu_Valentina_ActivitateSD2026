#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Carte {
    int id;
    int nrPagini;
    char* titlu;
    float pret;
    char volum;
};

struct Carte initializareCarte(int id, int nrPagini, const char* titlu, float pret, char volum) {
    struct Carte c;
    c.id = id;
    c.nrPagini = nrPagini;

    c.titlu = (char*)malloc(strlen(titlu) + 1);
    strcpy(c.titlu, titlu);

    c.pret = pret;
    c.volum = volum;
    return c;
}

void afisareCarte(struct Carte c) {
    if (c.titlu != NULL) {
        printf("%d. Cartea %s are %d pagini, volumul %c si costa %.2f lei.\n",
            c.id, c.titlu, c.nrPagini, c.volum, c.pret);
    }
    else {
        printf("%d. Cartea fara titlu are %d pagini, volumul %c si costa %.2f lei.\n",
            c.id, c.nrPagini, c.volum, c.pret);
    }
}

void afisareVectorCarti(struct Carte* vector, int nrElemente) {
    for (int i = 0; i < nrElemente; i++) {
        afisareCarte(vector[i]);
    }
}

struct Carte* copiazaPrimeleNCarti(struct Carte* vector, int nrElemente, int nrCopiate) {
    if (nrCopiate > nrElemente) {
        nrCopiate = nrElemente;
    }

    struct Carte* copie = (struct Carte*)malloc(sizeof(struct Carte) * nrCopiate);

    for (int i = 0; i < nrCopiate; i++) {
        copie[i] = vector[i]; //shallow copy 
        copie[i].titlu = (char*)malloc(strlen(vector[i].titlu) + 1);
        strcpy(copie[i].titlu, vector[i].titlu); //deep copy pentru campul char*
    }

    return copie;
}

void copiazaCartiIeftine(struct Carte* vector, int nrElemente, float pragMaxim, struct Carte** rezultat, int* dimensiune) {
    *dimensiune = 0;

    for (int i = 0; i < nrElemente; i++) {
        if (vector[i].pret <= pragMaxim) {
            (*dimensiune)++;
        }
    }

    *rezultat = (struct Carte*)malloc(sizeof(struct Carte) * (*dimensiune));
    int k = 0;

    for (int i = 0; i < nrElemente; i++) {
        if (vector[i].pret <= pragMaxim) {
            (*rezultat)[k] = vector[i];
            (*rezultat)[k].titlu = (char*)malloc(strlen(vector[i].titlu) + 1);
            strcpy((*rezultat)[k].titlu, vector[i].titlu);
            k++;
        }
    }
}

void modificaPretCarte(struct Carte* c, float pretNou) {
    if (c != NULL && pretNou > 0) {
        c->pret = pretNou;
    }
}

void dezalocareCarte(struct Carte* c) {
    if (c != NULL && c->titlu != NULL) {
        free(c->titlu);
        c->titlu = NULL;
    }
}

void dezalocareVectorCarti(struct Carte** vector, int* nrElemente) {
    if (*vector != NULL) {
        for (int i = 0; i < *nrElemente; i++) {
            if ((*vector)[i].titlu != NULL) {
                free((*vector)[i].titlu);
            }
        }

        free(*vector);
        *vector = NULL;
        *nrElemente = 0;
    }
}

int main() {
    /*struct Carte c1 = initializareCarte(1, 320, "Morometii", 45.5f, '1');

    afisareCarte(c1);
    modificaPretCarte(&c1, 39.99f);
    afisareCarte(c1);

    dezalocareCarte(&c1);
    afisareCarte(c1);*/

    int nrCarti = 4;
    struct Carte* carti = (struct Carte*)malloc(sizeof(struct Carte) * nrCarti);

    carti[0] = initializareCarte(1, 320, "Morometii", 45.5f, '1');
    carti[1] = initializareCarte(2, 180, "Poezii", 22.0f, '2');
    carti[2] = initializareCarte(3, 250, "Chimie Organica", 89.9f, '2');
    carti[3] = initializareCarte(4, 140, "Retete rapide", 18.5f, '3');

    printf("Vector initial:\n");
    afisareVectorCarti(carti, nrCarti);


    int nrPrimele = 2;
    struct Carte* primele = copiazaPrimeleNCarti(carti, nrCarti, nrPrimele);
    printf("\nPrimele carti:\n");
    afisareVectorCarti(primele, nrPrimele);

    struct Carte* cartiIeftine = NULL;
    int nrCartiIeftine = 0;
    copiazaCartiIeftine(carti, nrCarti, 25.0f, &cartiIeftine, &nrCartiIeftine);
    printf("\nCarti ieftine:\n");
    afisareVectorCarti(cartiIeftine, nrCartiIeftine);


    dezalocareVectorCarti(&primele, &nrPrimele);
    dezalocareVectorCarti(&cartiIeftine, &nrCartiIeftine);
    dezalocareVectorCarti(&carti, &nrCarti);

    return 0;
}