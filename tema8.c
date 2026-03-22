#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Concurs Concurs;
typedef struct Nod Nod;

struct Concurs {
	char* denumire;
	int nrParticipanti;
	float taxa;
};

struct Nod {
	Concurs info;
	Nod* next;
};

Concurs initConcurs(const char* denumire,
	int nrParticipanti, float taxa) {

	Concurs c;
	c.nrParticipanti = nrParticipanti;
	c.taxa = taxa;

	c.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(c.denumire, denumire);

	return c;
}

void afisareConcurs(Concurs c) {
	printf("\nConcursul %s are %d participanti si taxa %.2f lei.",
		c.denumire, c.nrParticipanti, c.taxa);
}

void afisareListaConcursuri(Nod* cap) {

	while (cap != NULL) {
		afisareConcurs(cap->info);
		cap = cap->next;
	}
}

void inserareLaSfarsit(Nod** cap, Concurs c) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = c;

	//daca lista este goala, nodul nou devine primul
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		Nod* aux = *cap;

		//parcurgem lista ca sa inseram la final
		while (aux->next != NULL) {
			aux = aux->next;
		}

		aux->next = nou;
	}
}

int main() {

	Nod* cap = NULL;

	//adaugam cateva concursuri in lista
	inserareLaSfarsit(&cap,
		initConcurs("Ciclism montan", 60, 120.5f));

	inserareLaSfarsit(&cap,
		initConcurs("Maraton urban", 75, 80.0f));

	inserareLaSfarsit(&cap,
		initConcurs("Concurs inot", 48, 150.0f));

	printf("\nLista concursuri:");

	//afisam elementele introduse
	afisareListaConcursuri(cap);

	return 0;
}