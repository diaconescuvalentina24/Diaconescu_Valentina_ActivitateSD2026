#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Apartament Apartament;
typedef struct Nod Nod;

struct Apartament {
	int id;
	int nrCamere;
	float suprafata;
	float pret;
	char* proprietar;
};

struct Nod {
	Apartament info;
	Nod* st;
	Nod* dr;
};

Apartament initApartament(int id, int nrCamere,
	float suprafata, float pret, const char* proprietar) {

	Apartament a;

	a.id = id;
	a.nrCamere = nrCamere;
	a.suprafata = suprafata;
	a.pret = pret;

	a.proprietar = (char*)malloc(sizeof(char) * (strlen(proprietar) + 1));
	strcpy(a.proprietar, proprietar);

	return a;
}

void afisareApartament(Apartament a) {

	printf("\nId: %d", a.id);
	printf("\nNr camere: %d", a.nrCamere);
	printf("\nSuprafata: %.2f", a.suprafata);
	printf("\nPret: %.2f", a.pret);
	printf("\nProprietar: %s\n", a.proprietar);
}

void adaugaApartamentInArbore(Nod** rad, Apartament apartamentNou) {

	if (*rad == NULL) {

		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = apartamentNou;
		nod->st = NULL;
		nod->dr = NULL;

		//am gasit pozitia libera unde inseram nodul
		*rad = nod;
	}
	else {

		//id-urile mai mici merg in stanga
		if ((*rad)->info.id > apartamentNou.id) {
			adaugaApartamentInArbore(&((*rad)->st), apartamentNou);
		}

		//id-urile mai mari merg in dreapta
		if ((*rad)->info.id < apartamentNou.id) {
			adaugaApartamentInArbore(&((*rad)->dr), apartamentNou);
		}
	}
}

void afisareInordine(Nod* rad) {

	if (rad) {

		//inordine afiseaza apartamentele crescator dupa id
		afisareInordine(rad->st);
		afisareApartament(rad->info);
		afisareInordine(rad->dr);
	}
}

void afisarePreordine(Nod* rad) {

	if (rad) {

		afisareApartament(rad->info);
		afisarePreordine(rad->st);
		afisarePreordine(rad->dr);
	}
}

Apartament getApartamentByID(Nod* rad, int id) {

	Apartament a;
	a.id = -1;
	a.proprietar = NULL;

	if (rad) {

		if (rad->info.id == id) {

			a = rad->info;
			a.proprietar = (char*)malloc(sizeof(char) * (strlen(rad->info.proprietar) + 1));
			strcpy(a.proprietar, rad->info.proprietar);
		}

		if (id < rad->info.id) {
			a = getApartamentByID(rad->st, id);
		}

		if (id > rad->info.id) {
			a = getApartamentByID(rad->dr, id);
		}
	}

	return a;
}

int determinaNumarNoduri(Nod* rad) {

	if (rad) {
		return determinaNumarNoduri(rad->st) +
			determinaNumarNoduri(rad->dr) + 1;
	}
	return 0;
}

int maxim(int a, int b) {
	return (a > b ? a : b);
}

int calculeazaInaltimeArbore(Nod* rad) {

	if (rad) {
		return maxim(calculeazaInaltimeArbore(rad->st),
			calculeazaInaltimeArbore(rad->dr)) + 1;
	}

	return 0;
}


float sumaPretPeMetruPatrat(Nod* rad) {

	if (rad) {

		float pretMp = 0;

		//calculam doar daca suprafata este diferita de 0
		if (rad->info.suprafata > 0) {
			pretMp = rad->info.pret / rad->info.suprafata;
		}

		return pretMp +
			sumaPretPeMetruPatrat(rad->st) +
			sumaPretPeMetruPatrat(rad->dr);
	}

	return 0;
}

float calculeazaPretMediuPeMetruPatrat(Nod* rad) {

	int nr = determinaNumarNoduri(rad);

	//daca arborele este gol, nu avem ce medie sa calculam
	if (nr == 0) {
		return 0;
	}

	return sumaPretPeMetruPatrat(rad) / nr;
}

void dezalocareArbore(Nod** rad) {

	if (*rad) {

		dezalocareArbore(&((*rad)->st));
		dezalocareArbore(&((*rad)->dr));

		free((*rad)->info.proprietar);

		free(*rad);
		*rad = NULL;
	}
}

int main() {

	Nod* rad = NULL;

	adaugaApartamentInArbore(&rad,
		initApartament(10, 2, 55.5f, 85000, "Popescu"));

	adaugaApartamentInArbore(&rad,
		initApartament(5, 3, 72.0f, 120000, "Ionescu"));

	adaugaApartamentInArbore(&rad,
		initApartament(15, 1, 38.0f, 65000, "Popescu"));

	adaugaApartamentInArbore(&rad,
		initApartament(7, 4, 90.0f, 170000, "Georgescu"));

	printf("\n-----Afisare preordine-----");
	afisarePreordine(rad);

	printf("\n------Afisare inordine-----");
	afisareInordine(rad);

	printf("\n------Apartament cautat------");
	Apartament cautat = getApartamentByID(rad, 15);

	if (cautat.id != -1) {
		afisareApartament(cautat);
		free(cautat.proprietar);
	}

	printf("\nNumar noduri:%d", determinaNumarNoduri(rad));
	printf("\nInaltime arbore:%d", calculeazaInaltimeArbore(rad));

	printf("\nPret mediu pe metru patrat:%.2f",
		calculeazaPretMediuPeMetruPatrat(rad));

	dezalocareArbore(&rad);

	return 0;
}

