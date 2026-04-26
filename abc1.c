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

Avion citireAvionDinFisier(FILE* file) {
	Avion a;

	char buffer[100];
	char sep[3] = ",\n";
	char* aux;

	fgets(buffer, 100, file);
	aux = strtok(buffer, sep);
	a.nrLocuri = atoi(aux);

	aux = strtok(NULL, sep);
	a.pretBilet = atof(aux);

	aux = strtok(NULL, sep);
	a.pilot = malloc(strlen(aux) + 1);
	strcpy(a.pilot, aux);



	a.tipLoc = *strtok(NULL, sep);

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

Nod* citireArboreAvioaneDinFisier(const char* numeFis) {

	Nod* rad = NULL;
	FILE* f = fopen(numeFis, "r");
	//printf("hello0");
	if (f) {
		//printf("hello1");
		while (!(feof(f))) {
			//printf("hello2");
			Avion a = citireAvionDinFisier(f);
			adaugaAvionInArbore(&rad, a);
		}
		fclose(f);
	}
	return rad;
}

//in ordine
void afisareArboreAvioane(Nod* rad) {
	if (rad) {
		afisareArboreAvioane(rad->stg);
		afisareAvion(rad->info);
		afisareArboreAvioane(rad->dr);
	}

}

Avion getAvionByNumePilot(Nod* rad, const char* numePilot) {
	Avion a;
	//a.nrLocuri = -1;
	a.pilot = "";

	if (rad) {
		if (strcmp(rad->info.pilot, numePilot) == 0) {
			a = rad->info;
			a.pilot = malloc(sizeof(strlen(rad->info.pilot) + 1));
			strcpy(a.pilot, numePilot);
		}
		Avion avionulDinSubarboreleStang = getAvionByNumePilot(rad->stg, numePilot);
		Avion avionulDinSubarboreleDrept = getAvionByNumePilot(rad->dr, numePilot);

		if (strcmp(avionulDinSubarboreleStang.pilot, numePilot) == 0) {
			return avionulDinSubarboreleStang;
		}

		if (strcmp(avionulDinSubarboreleDrept.pilot, numePilot) == 0) {
			return avionulDinSubarboreleDrept;
		}
	}

	return a;

}

void dezalocareArboreDeAvioane(Nod** rad) {
	if (*rad) {
		dezalocareArboreDeAvioane(&(*rad)->stg);
		dezalocareArboreDeAvioane(&(*rad)->dr);
		free((*rad)->info.pilot);
		free(*rad);
		*rad = NULL;
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

	rad = citireArboreAvioaneDinFisier("avioane.txt");
	printf("\n---Afisare din fisier---\n");
	afisareArboreAvioane(rad);

	Avion x = getAvionByNumePilot(rad, "Popescu Ion");
	printf("Cauta avion dupa nume pilot\n");
	afisareAvion(x);


	dezalocareArboreDeAvioane(&rad);
	return 0;
}