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

}