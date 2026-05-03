#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Eveniment {
	int id;
	char* descriere;
	int zi;
	float suma;
};
typedef struct Eveniment Eveniment;

struct Nod {
	Eveniment info;
	struct Nod* stg;
	struct Nod* dr;
	int inaltime;

};
typedef struct Nod Nod;

Eveniment initEveniment(int id,
	const char* descriere,
	int zi,
	float suma) {
	Eveniment e;
	e.id = id;
	e.descriere = (char*)malloc(strlen(descriere) + 1);
	strcpy_s(e.descriere, strlen(descriere) + 1, descriere);
	e.zi = zi;
	e.suma = suma;
	return e;

}

void afisareEveniment(Eveniment e) {
	printf("id: %d\n", e.id);
	printf("descriere eveniment: %s\n", e.descriere);
	printf("zi eveniment: %d\n", e.zi);
	printf("suma eveniment: %.2f\n", e.suma);
	printf("-------------------\n");

}

//INSERARE IN ARBORE

// 1) fct maxim
int maxim(int a, int b) {
	return (a > b ? a : b);
}


//2) fct inaltime nod
int inaltimeNod(Nod* rad) {
	if (rad) {
		return rad->inaltime;
	}
	return 0;
}

//3) fct inaltime arbore, recursiva
int inaltimeArbore(Nod* rad) {
	if (rad) {
		return maxim(inaltimeArbore(rad->stg), inaltimeArbore(rad->dr)) + 1;
	}
	return 0;
}

//4) fct diferenta h pt dezechilibre
int diferentaInaltime(Nod* rad) {
	if (rad) {
		return inaltimeNod(rad->stg) - inaltimeNod(rad->dr) + 1;
	}
	return 0;

}

//5) rotiri stg/dr
void rotireLaDreapta(Nod** rad) {//arborele se modifica
	Nod* aux = (*rad)->stg;
	(*rad)->stg = aux->dr;
	aux->dr = *rad;

	(*rad)->inaltime = inaltimeArbore(*rad);
	aux->inaltime = inaltimeArbore(aux);

	*rad = aux;
}

void rotireLaStanga(Nod** rad) {//** arborele se modifica
	Nod* aux = (*rad)->dr;
	(*rad)->dr = aux->stg;
	aux->dr = *rad;

	(*rad)->inaltime = inaltimeArbore(*rad);
	aux->inaltime = inaltimeArbore(aux);

	*rad = aux;
}

//6) inserare, 2 parametrii, caz fara nod, caz cu nod recursiv, 
// verificare echilibru
void inserareEvenimentInArbore(Nod** rad, Eveniment e) {
	if ((*rad) == NULL) {	//daca e null pun nod
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = e;
		nod->stg = NULL;
		nod->dr = NULL;
		nod->inaltime = 1;
		*rad = nod;
	}
	else {
		//daca are nod verific sa vad unde trebuie pus, apel recursiv, &
		if (e.id < (*rad)->info.id) {
			inserareEvenimentInArbore(&((*rad)->stg), e);
		}
		else if (e.id > (*rad)->info.id) {
			inserareEvenimentInArbore(&((*rad)->dr), e);
		}
		else {
			return; //pt duplicate
		}

		(*rad)->inaltime = inaltimeArbore(*rad);
		//studiem echilibrul, depind de id si diferenta, &
		int dif = diferentaInaltime(*rad);

		if (dif > 1 && e.id < (*rad)->stg->info.id) {
			rotireLaDreapta(rad);
		}
		if (dif <-1 && e.id>(*rad)->dr->info.id) {
			rotireLaStanga(rad);
		}
		else if (dif > 1 && e.id > (*rad)->stg->info.id) {
			rotireLaStanga(&(*rad)->stg);
			rotireLaDreapta(rad);
		}
		else if (dif < -1 && e.id < (*rad)->dr->info.id) {
			rotireLaDreapta(&(*rad)->dr);
			rotireLaStanga(rad);
		}

	}
}

//abc 5 elemente de tip Eveniment, info se citesc din fisier text
//1) conversie text - obiect eveniment
Eveniment citireEvenimentDinFisier(FILE* f) {
	Eveniment e; //declaram un obiect si initializam atributele
	e.id = -1;
	e.descriere = NULL;
	e.zi = 0;
	e.suma = 0;

	char buffer[100];
	char sep[3] = ",\n";

	if (fgets(buffer, 100, f) == NULL) {//daca nu s-a putut citi o linie
		return e;
	}

	char* aux = strtok(buffer, sep);
	e.id = atoi(aux);

	aux = strtok(NULL, sep);
	e.descriere = (char*)malloc(strlen(aux) + 1);
	strcpy(e.descriere, aux);

	aux = strtok(NULL, sep);
	e.zi = atoi(aux);

	aux = strtok(NULL, sep);
	e.suma = atof(aux);

	return e;//returnam obiectul

}

//citim din fisier, inseram in arbore
Nod* citireArboreDinFisier(const char* numeFis) {
	Nod* rad = NULL;

	FILE* f = fopen(numeFis, "r");
	if (f) {
		while (!feof(f)) {
			Eveniment e = citireEvenimentDinFisier(f);
			/*if (e.id == -1) {
				break;
			}*/
			inserareEvenimentInArbore(&rad, e); //aici parametrul este de tip Nod**
		}
		fclose(f);
	}

	return rad;
}



//functiile de afisare pre/post/in ordine sunt recursive
void afisareINordine(Nod* rad) {
	if (rad) {
		afisareINordine(rad->stg);
		afisareEveniment(rad->info);
		afisareINordine(rad->dr);
	}
}

void afisarePreordine(Nod* rad) {
	if (rad) {
		afisareEveniment(rad->info);
		afisarePreordine(rad->stg);
		afisarePreordine(rad->dr);
	}
}



//fct pt nr total de noduri e recursiva !!!!
int determinaNrTotalDeNoduri(Nod* rad) {
	if (rad) {
		return determinaNrTotalDeNoduri(rad->stg) +
			determinaNrTotalDeNoduri(rad->dr) + 1;

	}
	return 0;
}

//suma valorilor pt evenimentele aflate in frunze

float SumaFrunze(Nod* rad) {
	if (rad) {
		if (rad->stg == NULL && rad->dr == NULL) {
			return rad->info.suma;
		}
		return SumaFrunze(rad->stg) + SumaFrunze(rad->dr);
	}
	return 0;
}


//dezalocare arbore, primeste ca param un arbore care sufera modificari, tb verificat arborele daca NULL

void dezalocareArbore(Nod** rad) {
	if (*rad) {
		dezalocareArbore(&((*rad)->stg));
		dezalocareArbore(&((*rad)->dr));
		free((*rad)->info.descriere);
		free(*rad);
		*rad = NULL;
	}
}

int main() {
	Eveniment e = initEveniment(10, "festival", 17, 2500.5);
	afisareEveniment(e);


	Nod* rad = citireArboreDinFisier("evenimente.txt");//dupa ce citim
	//ca sa afisam trebuie sa parcurgem arborele

	printf("Afisare INordine\n\n");
	afisareINordine(rad);

	printf("Afisare Preordine\n\n");
	afisarePreordine(rad);

	printf("Inaltimea arborelui:%d\n",
		inaltimeArbore(rad));

	printf("Suma frunze: %.2f\n", SumaFrunze(rad));

	printf("Nr total de noduri: %d\n", determinaNrTotalDeNoduri(rad));
	dezalocareArbore(&rad);//cand apelam dezalicarea dam &

	return 0;
}













