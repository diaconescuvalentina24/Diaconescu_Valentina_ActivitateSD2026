#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Parfum Parfum;
typedef struct Nod Nod;

struct Parfum {
	char* denumire;
	char* brand;
	float pret;
	int cantitateMl;
};

struct Nod {
	Parfum info;
	Nod* next;
};

Parfum initializareParfum(const char* denumire,
	const char* brand,
	float pret,
	int cantitateMl) {
	Parfum p;
	p.pret = pret;
	p.cantitateMl = cantitateMl;

	p.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(p.denumire, denumire);
	p.brand = (char*)malloc(sizeof(char) * (strlen(brand) + 1));
	strcpy(p.brand, brand);

	return p;
}

void afisareParfum(Parfum p) {

	printf("\nParfumul %s de la brandul %s costa %.2f lei si are %d ml.",
		p.denumire, p.brand, p.pret, p.cantitateMl);
}

void inserareLaSfarsit(Nod** cap, Parfum p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = NULL;

	if (*cap == NULL) {
		//daca lista este goala, nodul nou devine primul
		*cap = nou;
	}
	else {
		Nod* aux = *cap;

		//mergem pana la ultimul nod
		while (aux->next != NULL) {
			aux = aux->next;
		}

		//legam ultimul nod de nodul nou
		aux->next = nou;
	}
}

void afisareListaParfumuri(Nod* cap) {
	//parcurgem lista de la primul nod
	while (cap != NULL) {
		afisareParfum(cap->info);
		cap = cap->next;
	}
}

void dezalocareLista(Nod** cap) {
	while (*cap != NULL) {
		Nod* copie = *cap;

		//mutam capul inainte sa stergem nodul curent
		*cap = (*cap)->next;

		free(copie->info.denumire);
		free(copie->info.brand);
		free(copie);
	}
}

int main() {
	Nod* cap = NULL;

	//adaugam cateva parfumuri in lista
	inserareLaSfarsit(&cap, initializareParfum("L'Homme", "Dior", 450.0f, 90));
	inserareLaSfarsit(&cap, initializareParfum("Light Blue", "Dolce Gabanna", 520.5f, 80));
	inserareLaSfarsit(&cap, initializareParfum("La Vie Est Belle", "Lancome", 390.0f, 75));

	printf("\nLista parfumuri:");

	//verificam daca parfumurile au fost inserate corect
	afisareListaParfumuri(cap);

	dezalocareLista(&cap);

	return 0;
}