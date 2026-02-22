#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* next;
};
//creare structura pentru un nod dintr-o lista simplu inlantuita
//ce este o lista= o colectie de elemente in care fiecare elem retine adresa urmatorului element
//nu mai avem zona de memorie contigua
//nu mai avem acces direct - dezavantaj

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	//citim linie cu linie
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	//despartim
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	//atoi e o functie ascii to int
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* lista) {
	//afiseaza toate elemente de tip masina din lista simplu inlantuita
	//prin apelarea functiei afisareMasina()
	while (lista) {
		afisareMasina(lista->info);
		lista = lista->next;
	}
	printf("==========================");
}

void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masinaNoua;// ne asumam ca realizam shallow copy
	//dereferentiere +accesare (conteaza ordinea)
	//indexul face deplasare + dereferentiere
	nou->next = NULL; // next e null pentru ca adaugam nodul la final

	if (*lista == NULL) {
		//cream un nou nod
		*lista = nou;
	}
	else {
		Nod* p = *lista;

		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
}

void adaugaLaInceputInLista(Nod** lista, Masina masinaNoua) {
	Nod* primul = malloc(sizeof(Nod));
	primul->info = masinaNoua;
	primul->next = *lista; // legam noul nod la lista veche
	*lista = primul; // actualizam inceputul listei
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		//adaugam masina in lista
		adaugaMasinaInLista(&lista, m);

	}
	fclose(f);
	return lista;
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareListaMasini(Nod** lista) {
	//sunt dezalocate toate masinile si lista de elemente
	while (*lista) {
		free((*lista)->info.model);
		free((*lista)->info.numeSofer);
		Nod* p = *lista;
		*lista = (*lista)->next;
		free(p);
	}
}

float calculeazaPretMediu(/*lista de masini*/) {
	//calculeaza pretul mediu al masinilor din lista.
	return 0;
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* lista = citireListaMasiniDinFisier("masini.txt");
	//afisareListaMasini(lista);
	//dezalocareListaMasini(&lista);
	Masina m;

	m.id = 0;
	m.nrUsi = 4;
	m.pret = 7500.5;
	m.serie = 'A';
	m.model = (char*)malloc(strlen("Dacia Logan") + 1);
	strcpy(m.model, "Dacia Logan");

	m.numeSofer = (char*)malloc(strlen("Popescu Ion") + 1);
	strcpy(m.numeSofer, "Popescu Ion");
	adaugaLaInceputInLista(&lista, m);
	afisareListaMasini(lista);
	return 0;
}