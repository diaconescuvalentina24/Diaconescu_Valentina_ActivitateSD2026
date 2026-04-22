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

void inversareLista(Nod** cap) {
	Nod* anterior = NULL;
	Nod* curent = *cap;
	Nod* urmator = NULL;

	//refacem legaturile dintre noduri
	while (curent != NULL) {
		//salvam urmatorul nod
		urmator = curent->next;

		//intoarcem legatura spre stanga
		curent->next = anterior;

		anterior = curent;
		curent = urmator;
	}

	//ultimul nod devine primul
	*cap = anterior;
}

int esteListaCirculara(Nod* cap) {
	//lista vida nu este considerata circulara
	if (cap == NULL) {
		return 0;
	}

	Nod* p = cap->next;

	//mergem pana ajungem la final sau pana revenim la primul nod
	while (p != NULL && p != cap) {
		p = p->next;
	}

	if (p == cap) {
		return 1;
	}

	return 0;
}

float calculPretMediu(Nod* cap) {
	float suma = 0;
	int nrParfumuri = 0;
	Nod* p = cap;

	//parcurgem toata lista
	while (p != NULL) {
		//adunam preturile parfumurilor
		suma += p->info.pret;
		nrParfumuri++;
		p = p->next;
	}

	return suma / nrParfumuri;
}

float calculSumaBrand(Nod* cap,
	const char* brand) {
	float suma = 0;
	Nod* p = cap;

	//parcurgem toate parfumurile
	while (p != NULL) {
		//adunam doar parfumurile de la brandul cautat
		if (strcmp(p->info.brand,
			brand) == 0) {
			suma += p->info.pret;
		}
		p = p->next;
	}
	return suma;
}





int main() {
	Nod* cap = NULL;

	//adaugam parfumuri in lista
	inserareLaSfarsit(&cap, initializareParfum("L'Homme", "Dior", 450.0f, 90));
	inserareLaSfarsit(&cap, initializareParfum("Light Blue", "Dolce Gabanna", 520.5f, 80));
	inserareLaSfarsit(&cap, initializareParfum("Light Blue Men", "Dolce Gabanna", 120.5f, 80));
	inserareLaSfarsit(&cap, initializareParfum("La Vie Est Belle", "Lancome", 390.0f, 75));

	printf("\nLista parfumuri:");
	//verificam daca parfumurile au fost inserate corect
	afisareListaParfumuri(cap);

	float pretMediu =
		calculPretMediu(cap);

	float sumaBrand =
		calculSumaBrand(
			cap,
			"Dolce Gabanna");

	printf(
		"\n\nSuma parfumurilor de la Dolce Gabanna: %.2f",
		sumaBrand);

	printf("\n\nPret mediu: %.2f",
		pretMediu);

	printf("\n\nLista inversata:\n");
	inversareLista(&cap);
	afisareListaParfumuri(cap);
	printf("\n\nVerificare lista circulara:\n");

	if (esteListaCirculara(cap)) {
		printf("Lista este circulara");
	}
	else {
		printf("Lista nu este circulara");
	}

	//test pentru lista circulara
	Nod* aux = cap;
	while (aux->next != NULL) {
		aux = aux->next;
	}

	//ultimul nod va indica spre primul
	aux->next = cap;

	printf("\nDupa legare:\n");
	if (esteListaCirculara(cap)) {
		printf("Lista este circulara");
	}
	else {
		printf("Lista nu este circulara");
	}

	return 0;
}