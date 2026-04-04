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
		//la inceput toate poz sunt null
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

void inserareHashTable(HashTable tabela, Reteta r) {

	if (tabela.dimensiune > 0) {

		//calculam pozitia unde ar trebui pusa reteta
		int pozitie = hash(tabela.dimensiune, r.nrIngrediente);

		if (pozitie >= 0 && pozitie < tabela.dimensiune) {

			//daca ajung mai multe retete pe aceeasi pozitie
			//le pastram in lista de la acea pozitie
			inserareLaSfarsit(&(tabela.vector[pozitie]), r);
		}
	}
}

void afisareHashTable(HashTable tabela) {

	for (int i = 0; i < tabela.dimensiune; i++) {
		printf("\n\nPozitie:%d", i);

		//afisam lista formata pe pozitia curenta
		afisareListaRetete(tabela.vector[i]);
	}
}

float calculTimpPrimaLista(HashTable tabela) {

	float total = 0;

	//luam lista de pe pozitia 0
	Nod* capLista0 = tabela.vector[0];

	while (capLista0 != NULL) {
		total += capLista0->info.timpPreparare;

		//trecem la urmatoarea reteta din lista
		capLista0 = capLista0->next;
	}

	return total;
}

void dezalocareLista(Nod** cap) {

	while ((*cap) != NULL) {

		Nod* copie = *cap;

		//mutam capul inainte de free ca sa nu pierdem lista
		*cap = (*cap)->next;

		free(copie->info.denumire);
		free(copie);
	}
}

void dezalocareHashTable(HashTable tabela) {

	for (int i = 0; i < tabela.dimensiune; i++) {

		//fiecare pozitie poate avea propria lista
		dezalocareLista(&(tabela.vector[i]));
	}

	free(tabela.vector);
}


int main() {

	Nod* cap = NULL;

	//adaugam cateva retete in lista
	inserareLaSfarsit(&cap,initReteta("Paste carbonara", 6, 25.0f));
	inserareLaSfarsit(&cap,initReteta("Clatite", 5, 30.0f));
	inserareLaSfarsit(&cap,initReteta("Salata greceasca", 8, 15.0f));

	printf("\nLista retete:");

	afisareListaRetete(cap);

	HashTable tabela = initHashTable(4);

	inserareHashTable(tabela, initReteta("Paste carbonara", 6, 25.0f));
	inserareHashTable(tabela, initReteta("Clatite", 5, 30.1f));
	inserareHashTable(tabela, initReteta("Salata greceasca", 8, 15.5f));
	inserareHashTable(tabela, initReteta("Omleta", 4, 10.0f));

	afisareHashTable(tabela);

	printf("\nTimp total pentru prima lista: %.2f",calculTimpPrimaLista(tabela));

	dezalocareHashTable(tabela);


	return 0;
}