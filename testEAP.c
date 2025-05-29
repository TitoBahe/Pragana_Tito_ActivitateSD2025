//#define _CRT_SECURE_NO_WARNINGS
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//struct Competitor {
//	char* nume;
//	float scorTotal;
//	int numarVerificare;
//	char* nationalitate;
//};
//typedef struct Competitor Competitor;
//
//struct Heap {
//	int lungime;
//	int nrCompetitori;
//	Competitor* vector;
//};
//typedef struct Heap Heap;
//
//Competitor citesteFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	Competitor c;
//	if (!fgets(buffer, 100, file)) {
//		printf("couldnt read line");
//	}
//	char* aux = strtok(buffer, sep);
//	float scor = atof(strtok(NULL, sep));
//	int numarVerificare = atoi(strtok(NULL, sep));
//	char* nationalitate = strtok(NULL, sep);
//
//	c.scorTotal = scor;
//	c.numarVerificare = numarVerificare;
//
//	c.nume = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy_s(c.nume, strlen(aux) + 1, aux);
//
//	c.nationalitate = (char*)malloc(sizeof(char) * (strlen(nationalitate) + 1));
//	strcpy_s(c.nationalitate, strlen(nationalitate) + 1, nationalitate);
//
//	return c;
//
//}
//
//void afisareCompetitor(Competitor competitor) {
//	printf("scorTotal: %.1f\n", competitor.scorTotal);
//	printf("numarVerificare : %d\n", competitor.numarVerificare);
//	printf("nume: %s\n", competitor.nume);
//	printf("Nationalitate: %s\n", competitor.nationalitate);
//
//}
//
//Heap* initializeazaHeap(int lun) {
//	Heap* heap = (Heap*)malloc(sizeof(Heap));
//	heap->lungime = lun;
//	heap->nrCompetitori = 0;
//	heap->vector = (Competitor*)malloc(sizeof(Competitor) * lun);
//	return heap;
//}
//
//void filtreazaHeap(Heap* heap, int pozitieNod) {
//	if (!heap) {
//		printf("heap is null in filtreaza heap");
//		return;
//	}
//	int pozMax = pozitieNod;
//	int pozNodSt = 2 * pozitieNod + 1;
//	int pozNodDr = 2 * pozitieNod + 2;
//
//	if (pozNodSt < heap->nrCompetitori && heap->vector[pozMax].scorTotal < heap->vector[pozNodSt].scorTotal) {
//		pozMax = pozNodSt;
//	}
//	if (pozNodDr < heap->nrCompetitori && heap->vector[pozMax].scorTotal < heap->vector[pozNodDr].scorTotal) {
//		pozMax = pozNodDr;
//	}
//	if (pozMax != pozitieNod) {
//		Competitor c = heap->vector[pozMax];
//		heap->vector[pozMax] = heap->vector[pozitieNod];
//		heap->vector[pozitieNod] = c;
//		filtreazaHeap(heap, pozMax);
//	}
//}
//
//Heap* citireCompetitorDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	if (!file) {
//		printf("File was not open");
//		return;
//	}
//	Heap* heap = initializeazaHeap(4);
//	while (!feof(file)) {
//		Competitor c = citesteFisier(file);
//		heap->vector[heap->nrCompetitori] = c;
//		(heap->nrCompetitori)++;
//	}
//	fclose(file);
//	for (int i = (heap->nrCompetitori - 2) / 2; i >= 0; i--) {
//		filtreazaHeap(heap, i);
//	}
//	return heap;
//}
//Competitor extrasCompetitor(Heap* heap) {
//	Competitor c;
//	c.nationalitate = NULL;
//	c.numarVerificare = -1;
//	c.scorTotal = 1;
//	c.nume = NULL;
//	if (!heap) {
//		printf("heap null in extrasCompetitor");
//		return;
//	}
//
//	if (heap->nrCompetitori > 0) {
//		c = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrCompetitori - 1];
//		heap->vector[heap->nrCompetitori - 1] = c;
//		(heap->nrCompetitori)--;
//	}
//	return c;
//
//}
//
//void dezalocare(Heap* heap) {
//	if (!heap) {
//		printf("heap null in dezalocare");
//		return;
//	}
//	for (int i = 0; i < heap->lungime; i++) {
//		afisareCompetitor(heap->vector[i]);
//		if (heap->vector[i].nationalitate) {
//			free(heap->vector[i].nationalitate);
//		}
//		if (heap->vector[i].nume) {
//			free(heap->vector[i].nume);
//		}
//	}
//	free(heap->vector);
//	free(heap);
//}
//
//int main() {
//	Heap* heap = citireCompetitorDinFisier("test.txt");
//
//	Competitor c = extrasCompetitor(heap);
//	afisareCompetitor(c);
//
//	dezalocare(heap);
//
//	return 0;
//}