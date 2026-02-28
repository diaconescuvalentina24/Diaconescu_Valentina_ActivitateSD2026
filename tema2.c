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

int main() {
    struct Carte c1 = initializareCarte(1, 320, "Morometii", 45.5f, '1');

    afisareCarte(c1);
    modificaPretCarte(&c1, 39.99f);
    afisareCarte(c1);

    dezalocareCarte(&c1);
    afisareCarte(c1);

    return 0;
}