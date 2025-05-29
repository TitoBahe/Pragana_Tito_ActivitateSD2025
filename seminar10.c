//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//struct Nod {
//	Masina info;
//	struct Nod* next;
//	struct Nod* prev;
//};
//typedef struct Nod Nod;
//																//STACK	
//
////Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
////putem reprezenta o stiva prin LSI, LDI sau vector													
//
//struct Stiva {
//	Nod* top;
//};
//typedef struct Stiva Stiva;
//
//void pushStack(Stiva* stiva, Masina masina) {
//	if (!stiva) {
//		printf("Stiva top is NULL");
//		return;
//	}
//	Nod* nod = (Nod*)malloc(sizeof(Nod));
//	
//	nod->info = masina;
//	nod->next = stiva->top;
//	stiva->top = nod;
//}
//
//Masina popStack(Stiva* stiva) {
//	Masina m;
//	m.id = -1;
//	m.model = NULL;
//	m.numeSofer = NULL;
//	m.nrUsi = 0;
//	m.pret = 0.0;
//	m.serie = '0';
//	if (!stiva || !stiva->top) {
//		printf("Stiva is NULL in popStack");
//		return m;
//	}
//	Nod* nod = stiva->top;
//	if (nod) {
//
//		stiva->top = nod->next;
//		m = nod->info;
//
//		if (nod->info.numeSofer) {
//			m.numeSofer = (char*)malloc(sizeof(char) * (strlen(nod->info.numeSofer) + 1));
//			strcpy_s(m.numeSofer, strlen(nod->info.numeSofer) + 1, nod->info.numeSofer);
//			free(nod->info.numeSofer);
//		}
//
//		if (nod->info.model) {
//			m.model = (char*)malloc(sizeof(char) * (strlen(nod->info.model) + 1));
//			strcpy_s(m.model, strlen(nod->info.model) + 1, nod->info.model);
//			free(nod->info.model);
//		}
//
//		free(nod);
//	}
//	return m;
//}
//
//int isStackEmpty(Stiva* stiva) {
//	return (stiva->top != NULL);
//}
//
//Stiva* citireStackMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Stiva* stiva = (Stiva*)malloc(sizeof(Stiva));
//	stiva->top = NULL;
//
//	while (!feof(file)) {
//		Masina m = citireMasinaDinFisier(file);
//		pushStack(stiva, m);
//	}
//	fclose(file);
//	return stiva;
//}
//
//void dezalocareStivaDeMasini(Stiva* stiva) {
//	//sunt dezalocate toate masinile si stiva de elemente
//	if (!stiva) {
//		printf("Stiva in dezalocare e null");
//		return;
//	}
//	printf("\n\nMasini dezalocate stiva:\n\n");
//	while (isStackEmpty(stiva)) {
//		Masina m = popStack(stiva);
//		afisareMasina(m);
//		if (m.numeSofer) {
//			free(m.numeSofer);
//		}
//		if(m.model){
//			free(m.model);
//		}
//	}
//	free(stiva);
//}
//
//int size(Stiva* stiva) {
//	//returneaza numarul de elemente din stiva
//	int size = 0;
//	if (!stiva) {
//		printf("Stiva is null in size function");
//		return 0;
//	}
//	Nod* nod = stiva->top;
//	while (nod) {
//		size++;
//		nod = nod->next;
//	}
//	return size;
//}
//
//																	//QUEUE
//																	
////Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
////putem reprezenta o coada prin LSI, LDI sau vector
//struct Queue {
//	Nod* cap;
//	Nod* coada;
//};typedef struct Queue Queue;
//
//void enqueue(Queue* queue, Masina masina) {
//	//adauga o masina in coada
//	if (!queue) {
//		printf("queue is null in enqueue");
//		return;
//	}
//	Nod* nod = (Nod*)malloc(sizeof(Nod));
//	nod->info = masina;
//	nod->next = queue->coada;
//	if (queue->coada) {
//		queue->coada->prev = nod;
//		queue->coada = nod;
//	}
//	else {
//		queue->coada = nod;
//		queue->cap = nod;
//	}
//	nod->prev = NULL;
//	
//}
//
//Masina dequeue(Queue* queue) {
//	//extrage o masina din coada
//	Masina m;
//	m.id = -1;
//	m.model = NULL;
//	m.numeSofer = NULL;
//	m.nrUsi = 0;
//	m.pret = 0.0;
//	m.serie = '0';
//
//	if (!queue) {
//		printf("queue null in dequeue");
//		return m;
//	}
//	Nod* nod = queue->cap;
//	if (nod) {
//		queue->cap = nod->prev;
//		m = nod->info;
//		if (nod->info.model) {
//			m.model = (char*)malloc(sizeof(char) * (strlen(nod->info.model) + 1));
//			strcpy_s(m.model, strlen(nod->info.model) + 1, nod->info.model);
//			free(nod->info.model);
//		}
//		if (nod->info.numeSofer) {
//			m.numeSofer = (char*)malloc(sizeof(char) * (strlen(nod->info.numeSofer) + 1));
//			strcpy_s(m.numeSofer, strlen(nod->info.numeSofer) + 1, nod->info.numeSofer);
//			free(nod->info.numeSofer);
//		}
//		free(nod);
//	}
//	return m;
//}
//
//Queue* citireCoadaDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Queue* queue = (Queue*)malloc(sizeof(Queue));
//	queue->cap = NULL;
//	queue->coada = NULL;
//	while (!feof(file)) {
//		Masina m = citireMasinaDinFisier(file);
//		enqueue(queue, m);
//	}
//	fclose(file);
//	return queue;
//}
//
//void dezalocareCoadaDeMasini(Queue* queue) {
//	//sunt dezalocate toate masinile si coada de elemente
//	if (queue) {
//		printf("\n\nMasini dezalocate:\n\n");
//		while (queue->cap) {
//			Masina m = dequeue(queue);
//
//			afisareMasina(m);
//
//			if (m.model) {
//				free(m.model);
//			}
//			if (m.numeSofer) {
//				free(m.numeSofer);
//			}
//		}
//		free(queue);
//	}
//}
//
//
////metode de procesare
//Masina getMasinaByID(/*stiva sau coada de masini*/int id);
//
//float calculeazaPretTotal(/*stiva sau coada de masini*/);
//
//int main() {
//
//	//Stiva
//	Stiva* stiva;
//	stiva = citireStackMasiniDinFisier("masini.txt");
//
//	Masina m;
//	m.id = 10000;
//	m.model = NULL;
//	m.nrUsi = 10;
//	m.numeSofer = NULL;
//	m.pret = 10000.0;
//	m.serie = 'A';
//
//	pushStack(stiva, m);
//	Masina m2 = popStack(stiva);
//
//	afisareMasina(m2);
//
//	dezalocareStivaDeMasini(stiva);
//
//	//Queue
//
//	Queue* queue = citireCoadaDeMasiniDinFisier("masini.txt");
//
//	enqueue(queue, m);
//
//	Masina m3 = dequeue(queue);
//	printf("\n\nMaisina dequeued:\n");
//	afisareMasina(m3);
//
//	dezalocareCoadaDeMasini(queue);
//	return 0;
//}