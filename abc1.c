#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct StructuraAvion {
	int nrLocuri;
	float pretBilet;
	char* pilot;
	unsigned char tipLoc;
};

typedef struct StructuraAvion Avion;

struct Nod {
	Avion info;
	struct Nod* stg;
	struct Nod* dr;
};
typedef struct Nod Nod;


//afisare un nod
void afisareAvion(Avion a) {
	printf("Avionul are %d locuri.\n", a.nrLocuri);
	printf("Pretul unui bilet de avion este %.2f.\n", a.pretBilet);
	printf("Pilotul avionului se numeste %s.\n", a.pilot);
	printf("Tipul de loc ales de dvs. este %c.\n", a.tipLoc);
}

//functie de initializare
Avion initAvion(int nrLocuri,
	float pretBilet,
	const char* pilot,
	unsigned char tipLoc) {

	Avion a;
	a.nrLocuri = nrLocuri;
	a.pretBilet = pretBilet;
	a.pilot = (char*)malloc(strlen(pilot) + 1);
	strcpy(a.pilot, pilot);
	a.tipLoc = tipLoc;

	return a;
}


//adaugare nod in arbore
void adaugaAvionInArbore(Nod** rad, Avion a) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = a;
		nod->stg = NULL;
		nod->dr = NULL;
		*rad = nod;
	}
	else {
		if ((*rad)->info.pretBilet > a.pretBilet) {
			adaugaAvionInArbore(&((*rad)->stg), a);
		}
		if ((*rad)->info.pretBilet < a.pretBilet) {
			adaugaAvionInArbore(&((*rad)->dr), a);
		}
	}

}


//in ordine
void afisareArboreAvioane(Nod* rad) {
	if (rad) {
		afisareArboreAvioane(rad->stg);
		afisareAvion(rad->info);
		afisareArboreAvioane(rad->dr);
	}

}




int main() {
	Nod* rad = NULL;

	Avion a1 = initAvion(180, 321.1, "Popescu", 'A');
	Avion a2 = initAvion(180, 221.0, "Stanescu", 'A');
	Avion a3 = initAvion(180, 500.0, "Ionescu", 'A');

	adaugaAvionInArbore(&rad, a1);
	adaugaAvionInArbore(&rad, a2);
	adaugaAvionInArbore(&rad, a3);

	afisareArboreAvioane(rad);

	return 0;
}