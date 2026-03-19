#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct TraseuMontan TraseuMontan;
typedef struct Nod Nod;

struct TraseuMontan {
	char* denumire;
	int durataOre;
	float dificultate;
};

struct Nod {
	TraseuMontan info;
	Nod* next;
};

TraseuMontan initTraseuMontan(const char* denumire,int durataOre,float dificultate) {

	TraseuMontan t;

	t.durataOre = durataOre;
	t.dificultate = dificultate;
	t.denumire =(char*)malloc(sizeof(char)* (strlen(denumire) + 1));
	strcpy(t.denumire, denumire);

	return t;
}

void afisareTraseuMontan(TraseuMontan t) {

	printf("\nTraseul %s dureaza %d ore si are dificultatea %.2f.",t.denumire,
		t.durataOre,t.dificultate);
}

void push(Nod** varf, TraseuMontan t) {

	Nod* nou =(Nod*)malloc(sizeof(Nod));
	nou->info = t;

	//se pastreaza legatura catre vechiul varf
	nou->next = *varf;

	//noul element devine primul din stiva
	*varf = nou;
}

TraseuMontan pop(Nod** varf) {

	//nu putem extrage un element dintr-o stiva goala
	if ((*varf) == NULL) {
		return initTraseuMontan("Necunoscut", 0, 0);
	}

	//salvam info din varf
	TraseuMontan t = (*varf)->info;
	Nod* aux = *varf;
	*varf = (*varf)->next;

	free(aux);

	return t;
}

void put(Nod** coada, TraseuMontan t) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = t;

	//daca lista este goala, nodul nou = inceputul cozii
	if (*coada == NULL) {
		*coada = nou;
	}
	else {
		Nod* aux = *coada;

		//cautam ultimul nod pentru inserare la final
		while (aux->next != NULL) {
			aux = aux->next;
		}

		aux->next = nou;
	}
}

int main() {

	Nod* stiva = NULL;

	//adaugam trasee in stiva
	push(&stiva, initTraseuMontan("Cabana Babele", 3, 6.5f));
	push(&stiva, initTraseuMontan("Varful Omu", 5, 8.0f));
	push(&stiva, initTraseuMontan("Cascada Urlatoarea", 2, 4.0f));

	TraseuMontan t;

	printf("\nTraversare stiva:");

	//stiva:LIFO Last In First Out
	while (stiva != NULL) {
		t = pop(&stiva);

		afisareTraseuMontan(t);

		free(t.denumire);
	}

	Nod* coada = NULL;
	//adaugam trasee in coada
	put(&coada, initTraseuMontan("Cabana Babele", 3, 6.5f));
	put(&coada, initTraseuMontan("Varful Omu", 5, 8.0f));
	put(&coada, initTraseuMontan("Cascada Urlatoarea", 2, 4.0f));

	printf("\nTraversare coada:");

	//coada:FIFO First In First Out
	while (coada != NULL) {
		t = pop(&coada);

		afisareTraseuMontan(t);

		free(t.denumire);
	}
	return 0;
}