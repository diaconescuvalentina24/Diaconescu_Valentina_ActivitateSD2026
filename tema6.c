//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<malloc.h>
//#include<string.h>
//
//typedef struct Antrenament Antrenament;
//typedef struct Nod Nod;
//
//struct Antrenament
//{
//	char* tipAntrenament;
//	int nrParticipanti;
//	float durata;
//};
//
//struct Nod {
//	Antrenament info;
//	Nod* next;
//};
//
//Antrenament initAntrenament(const char* tipAntrenament,
//	int nrParticipanti,float durata){
//
//	Antrenament a;
//	a.nrParticipanti = nrParticipanti;
//	a.durata = durata;
//
//	a.tipAntrenament =(char*)malloc(sizeof(char)* (strlen(tipAntrenament) + 1));
//	strcpy(a.tipAntrenament,tipAntrenament);
//
//	return a;
//}
//
//void afisareAntrenament(Antrenament a) {
//
//	printf("\nLa antrenamentul %s au participat %d persoane. Durata a fost %.2f ore!",
//		a.tipAntrenament,
//		a.nrParticipanti,
//		a.durata);
//}
//
//void push(Nod** varf, Antrenament a) {
//
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = a;
//
//	//noul nod pastreaza legatura catre fostul varf
//	nou->next = *varf;
//
//	//noul element devine primul din stiva
//	*varf = nou;
//}
//
//Antrenament pop(Nod** varf) {
//	//nu putem extrage un element dintr-o stiva goala
//	if ((*varf) == NULL) {
//		return initAntrenament("Necunoscut", 0, 0);
//	}
//
//	//salvam informatia din varf
//	Antrenament a = (*varf)->info;
//	Nod* aux = *varf;
//
//	//varful se muta pe elementul urmator
//	//deoarece primul nod va fi eliminat
//	*varf = (*varf)->next;
//
//	//eliberam memoria nodului extras
//	free(aux);
//
//	return a;
//}
//
//void put(Nod** coada, Antrenament a) {
//
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->next = NULL;
//	nou->info = a;
//
//	//daca nu exista elemente, nodul nou devine inceputul cozii
//	if (*coada == NULL) {
//		*coada = nou;
//	}
//	else {
//		Nod* aux = *coada;
//
//		//cautam ultimul nod pentru a adauga noul element la final
//		while (aux->next != NULL) {
//			aux = aux->next;
//		}
//		aux->next = nou;
//	}
//}
//
//int main() {
//	Nod* stiva = NULL;
//
//	//test adaugare elemente in stiva
//	push(&stiva,initAntrenament("Cardio",20,1.5f));
//	push(&stiva,initAntrenament("Fitness",15,2.0f));
//	push(&stiva,initAntrenament("Yoga",10,1.0f));
//
//	Antrenament a;
//	printf("\nTraversare stiva:");
//
//	//stiva functioneaza dupa principiul LIFO
//	//ultimul element introdus este primul eliminat
//	while (stiva != NULL) {
//		a = pop(&stiva);
//		afisareAntrenament(a);
//		free(a.tipAntrenament);
//	}
//	Nod* coada = NULL;
//
//	//test adaugare elemente in coada
//	put(&coada,initAntrenament("Cardio",20,1.5f));
//	put(&coada,initAntrenament("Fitness",15,2.0f));
//	put(&coada,initAntrenament("Yoga",10,1.0f));
//
//	printf("\nTraversare coada:");
//
//	//coada functioneaza dupa principiul FIFO
//	//primul element introdus este primul eliminat
//	while (coada != NULL) {
//		a = pop(&coada);
//		afisareAntrenament(a);
//
//		free(a.tipAntrenament);
//	}
//	return 0;
//}