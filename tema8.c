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

typedef struct HashTable HashTable;

struct HashTable {
	int dimensiune;
	Nod** vector;
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

HashTable initHashTable(int size) {

	HashTable tabela;
	tabela.dimensiune = size; //salvam dimensiunea tabelei
	//alocam memorie pentru vectorul de liste
	tabela.vector = (Nod**)malloc(sizeof(Nod*) * size);

	//fiecare pozitie va avea initial lista goala
	for (int i = 0; i < size; i++) {
		tabela.vector[i] = NULL;
	}

	return tabela;
}

int hash(int dim, int nrParticipanti) {

	//pe baza fct hash se stabileste pozitia in tabela
	return nrParticipanti % dim;
}

void afisareConcurs(Concurs c) {
	printf("\nConcursul de %s are %d participanti si taxa %.2f lei.",
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

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		Nod* aux = *cap;

		while (aux->next != NULL) {
			aux = aux->next;
		}

		aux->next = nou;
	}
}

void inserareHashTable(HashTable tabela, Concurs c) {
	//verificam daca tabela a fost initializata
	if (tabela.dimensiune > 0) {
		//calculam pozitia folosind functia hash
		int pozitie = hash(tabela.dimensiune, c.nrParticipanti);

		//verificam daca pozitia este in intervalul tabelei
		if (pozitie >= 0 && pozitie < tabela.dimensiune) {

			//daca exista deja elemente pe aceeasi pozitie => coliziune
			//acestea se vor lega intr-o lista
			inserareLaSfarsit(&(tabela.vector[pozitie]), c);
		}
	}
}

void afisareHashTable(HashTable tabela) {

	for (int i = 0; i < tabela.dimensiune; i++) {
		printf("\nPozitie: %d", i);

		//afisam lista de concursuri de pe fiecare pozitie
		afisareListaConcursuri(tabela.vector[i]);
	}
}

int main() {

	Nod* cap = NULL;
	//adaugam cateva concursuri in lista
	inserareLaSfarsit(&cap,initConcurs("Ciclism", 60, 120.5f));
	inserareLaSfarsit(&cap,initConcurs("Maraton", 75, 80.0f));
	inserareLaSfarsit(&cap,initConcurs("Inot", 48, 150.0f));

	printf("\nLista concursuri:");
	afisareListaConcursuri(cap);


	HashTable tabela = initHashTable(4);

	inserareHashTable(tabela, initConcurs("Ciclism", 67, 120.5f));
	inserareHashTable(tabela, initConcurs("Maraton", 175, 80.0f));
	inserareHashTable(tabela, initConcurs("Inot", 400, 150.0f));

	afisareHashTable(tabela);

	return 0;
}