#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Farmacie {
	char* denumire;
	float suprafata;
	unsigned char nrAngajati;
	char* adresa;
}Farmacie;

typedef struct Nod {
	Farmacie farmacie;
	struct Nod* next;
	struct Nod* prev;

}Nod;

typedef struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
}ListaDubla;

Farmacie initializareFarmacie(const char* denumire,
	float suprafata,
	unsigned char nrAngajati,
	const char* adresa) {
	Farmacie f;

	f.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(f.denumire, denumire);
	f.suprafata = suprafata;
	f.nrAngajati = nrAngajati;
	f.adresa = (char*)malloc(sizeof(char) * (strlen(adresa) + 1));
	strcpy(f.adresa, adresa);
	return f;

}

void afisareFarmacie(Farmacie f) {
	printf("Nume farmacie: %s\n", f.denumire);
	printf("Suprafata farmaciei: %.2f\n", f.suprafata);
	printf("Numarul de angajati: %d\n", f.nrAngajati);
	printf("Adresa farmaciei: %s\n\n\n", f.adresa);
}

void afisareListaDeLaInceput(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareFarmacie(p->farmacie);
		p = p->next;
	}
}

void adaugareFarmacieInLista(ListaDubla* lista, Farmacie farmacieNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->farmacie = farmacieNoua;
	nou->next = NULL;
	nou->prev = lista->last;
	if (lista->last != NULL) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->last = nou;
	lista->nrNoduri++;


}

void inversareListaDubla(ListaDubla* lista) {

	Nod* p = lista->first;
	Nod* temp = NULL;

	//parcurgem toate nodurile si schimbam legaturile
	while (p != NULL) {

		//salvam fostul next
		temp = p->next;

		//inversam directiile
		p->next = p->prev;
		p->prev = temp;

		//trecem la urmatorul nod din lista initiala
		p = temp;
	}

	//schimbam intre ele inceputul si sfarsitul listei
	temp = lista->first;
	lista->first = lista->last;
	lista->last = temp;
}

int verificareListaCirculara(ListaDubla lista) {

	//daca lista este goala nu o consideram circulara
	if (lista.first == NULL || lista.last == NULL) {
		return 0;
	}
	//verificam daca primul si ultimul nod sunt legate intre ele
	if (lista.first->prev == lista.last && lista.last->next == lista.first) {
		return 1;
	}

	return 0;
}

void stergeFarmacieDupaDenumire(ListaDubla* lista,const char* denumire) {

	Nod* p = lista->first;

	//cautam farmacia dupa denumire
	while (p != NULL &&
		strcmp(p->farmacie.denumire,denumire) != 0) {
		p = p->next;
	}

	//daca farmacia nu exista iesim
	if (p == NULL) {
		return;
	}

	//daca stergem primul nod
	if (p->prev == NULL) {
		lista->first = p->next;

		if (lista->first != NULL) {

			//noul prim nod nu mai are element in stanga
			lista->first->prev = NULL;
		}
	}
	else {
		//legam nodul anterior cu urmatorul
		p->prev->next = p->next;
	}

	//daca stergem ultimul nod
	if (p->next == NULL) {
		lista->last = p->prev;

		if (lista->last != NULL) {
			//noul ultim nod nu mai are element in dreapta
			lista->last->next = NULL;
		}
	}
	else {
		p->next->prev = p->prev;
	}

	free(p->farmacie.denumire);
	free(p->farmacie.adresa);
	free(p);

	lista->nrNoduri--;
}

int main() {
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;

	adaugareFarmacieInLista(&lista, initializareFarmacie("Catena", 88.2f, 11, "Sos. Colentina nr.6"));
	adaugareFarmacieInLista(&lista, initializareFarmacie("Dona", 100.2f, 12, "Calea Vitan nr.7"));
	adaugareFarmacieInLista(&lista, initializareFarmacie("HelpNet", 60.4f, 13, "Bd. Unirii nr.8"));
	adaugareFarmacieInLista(&lista, initializareFarmacie("SensiBlue", 140.0f, 15, "Bd. Aviatorilor nr.9"));
	adaugareFarmacieInLista(&lista, initializareFarmacie("Tei", 200.0f, 7, "Calea Victoriei nr.10"));
	printf("\n-----Afisare lista de la inceput------\n");
	afisareListaDeLaInceput(lista);

	printf("\n------Lista inversata----------\n");
	inversareListaDubla(&lista);
	afisareListaDeLaInceput(lista);

	printf("\n -------Lista dupa stergere-------\n");

	stergeFarmacieDupaDenumire(&lista, "Dona");

	afisareListaDeLaInceput(lista);

	printf("\n------Verificare lista circulara------\n");

	if (verificareListaCirculara(lista)) {
		printf("Lista este circulara\n");
	}
	else {
		printf("Lista nu este circulara\n");
	}

	//legam primul si ultimul nod
	lista.first->prev = lista.last;
	lista.last->next = lista.first;

	printf("\n-------Dupa legare primul de ultimul nod-------\n");

	if (verificareListaCirculara(lista)) {
		printf("Lista este circulara\n");
	}
	else {
		printf("Lista nu este circulara\n");
	}

}