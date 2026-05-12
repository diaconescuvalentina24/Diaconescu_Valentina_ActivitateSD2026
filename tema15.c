#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Tableta Tableta;
typedef struct Nod Nod;

struct Tableta {
	int id;
	char* denumire;
	float pret;
	int memorieGB;
};

struct Nod {
	Tableta info;
	Nod* st;
	Nod* dr;
};

Tableta initTableta(int id, const char* denumire,
	float pret, int memorieGB) {

	Tableta t;

	t.id = id;
	t.pret = pret;
	t.memorieGB = memorieGB;

	t.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(t.denumire, denumire);

	return t;
}

void afisareTableta(Tableta t) {

	printf("\nId: %d", t.id);
	printf("\nDenumire: %s", t.denumire);
	printf("\nPret: %.2f", t.pret);
	printf("\nMemorie: %d GB\n", t.memorieGB);
}

void inserareArbore(Nod** rad, Tableta tabletaNoua) {

	if (*rad == NULL) {

		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = tabletaNoua;
		nod->st = NULL;
		nod->dr = NULL;

		//am gasit o pozitie libera in arbore
		*rad = nod;
	}
	else {
		//incercam sa inseram mai intai in partea stanga
		if ((*rad)->st == NULL) {
			inserareArbore(&((*rad)->st), tabletaNoua);
		}
		else {
			//daca stanga exista, incercam sa inseram in dreapta
			inserareArbore(&((*rad)->dr), tabletaNoua);
		}
	}
}

void afisarePreordine(Nod* rad) {

	if (rad) {

		afisareTableta(rad->info);
		afisarePreordine(rad->st);
		afisarePreordine(rad->dr);
	}
}

void dezalocareArbore(Nod** rad) {

	if (*rad) {

		dezalocareArbore(&((*rad)->st));
		dezalocareArbore(&((*rad)->dr));

		free((*rad)->info.denumire);
		free(*rad);

		*rad = NULL;
	}
}

int main() {

	Nod* rad = NULL;

	//adaugam tablete in arbore normal
	inserareArbore(&rad, initTableta(1, "iPad Air", 3200.0f, 256));
	inserareArbore(&rad, initTableta(2, "Samsung Tab", 2100.0f, 128));
	inserareArbore(&rad, initTableta(3, "Lenovo Tab", 1200.0f, 64));
	inserareArbore(&rad, initTableta(4, "Huawei Tab", 1800.0f, 128));

	printf("\nAfisare preordine:");
	afisarePreordine(rad);

	dezalocareArbore(&rad);

	return 0;
}