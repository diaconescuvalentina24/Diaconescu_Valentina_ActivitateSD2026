#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Reteta Reteta;
typedef struct Nod Nod;

struct Reteta {
	char* denumire;
	int nrIngrediente;
	float timpPreparare;
};

struct Nod {
	Reteta info;
	Nod* next;
};

typedef struct HashTable HashTable;

struct HashTable {
	int dimensiune;
	Nod** vector;
};

Reteta initReteta(const char* denumire,int nrIngrediente, float timpPreparare) {

	Reteta r;
	r.nrIngrediente = nrIngrediente;
	r.timpPreparare = timpPreparare;

	r.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(r.denumire, denumire);

	return r;
}

HashTable initHashTable(int size) {

	HashTable tabela;
	tabela.dimensiune = size;

	//alocam memorie pt vectorul in care pt fiecare pozitie incepe o lista
	tabela.vector = (Nod**)malloc(sizeof(Nod*) * size);

	for (int i = 0; i < size; i++) {
		//la inceput toate pozitiile sunt null
		tabela.vector[i] = NULL;
	}

	return tabela;
}

int hash(int dim, int nrIngrediente) {

	return nrIngrediente % dim;//pozitia de det pe baza lui modulo
}

void afisareReteta(Reteta r) {

	printf("\nReteta %s are %d ingrediente si se prepara in %.2f minute.",
		r.denumire, r.nrIngrediente, r.timpPreparare);
}

void afisareListaRetete(Nod* cap) {

	while (cap != NULL) {
		afisareReteta(cap->info);
		cap = cap->next;
	}
}

void inserareLaSfarsit(Nod** cap, Reteta r) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = r;

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




int main() {

	Nod* cap = NULL;

	//adaugam cateva retete in lista
	inserareLaSfarsit(&cap,initReteta("Paste carbonara", 6, 25.0f));
	inserareLaSfarsit(&cap,initReteta("Clatite", 5, 30.0f));
	inserareLaSfarsit(&cap,initReteta("Salata greceasca", 8, 15.0f));

	printf("\nLista retete:");

	afisareListaRetete(cap);


	return 0;
}