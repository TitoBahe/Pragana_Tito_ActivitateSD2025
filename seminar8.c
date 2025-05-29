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
////creare structura pentru un nod dintr-un arbore binar de cautare
//struct Nod {
//	Masina info;
//	struct Nod* st;
//	struct Nod* dr;
//};
//typedef struct Nod Nod;
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
//	m1.pret= atof(strtok(NULL, sep));
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
//Nod* adaugaMasinaInArbore(Nod* nod, Masina masinaNoua) {
//	//adauga o noua masina pe care o primim ca parametru in arbore,
//	//astfel incat sa respecte princiippile de arbore binar de cautare
//	//dupa o anumita cheie pe care o decideti - poate fi ID
//	if (!nod) {
//		nod = (Nod*)malloc(sizeof(Nod));
//		nod->info = masinaNoua;
//		nod->st = NULL;
//		nod->dr = NULL;
//		return nod;
//	}
//	if (masinaNoua.pret >= nod->info.pret) {
//		nod->dr = adaugaMasinaInArbore(nod->dr, masinaNoua);
//	}
//	else{
//		nod->st = adaugaMasinaInArbore(nod->st, masinaNoua);
//	}
//	return nod;
//}
//
//Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Nod* nod = NULL;
//	if (file) {
//		while (!feof(file)) {
//			Masina m = citireMasinaDinFisier(file);
//			nod = adaugaMasinaInArbore(nod, m);
//		}
//	}
//	else {
//		printf("file n-a fost descis");
//	}
//	fclose(file);
//	return nod;
//}
//
//void afisareMasiniDinArbore(Nod* nod) {
//	//afiseaza toate elemente de tip masina din arborele creat
//	//prin apelarea functiei afisareMasina()
//	//parcurgerea arborelui poate fi realizata in TREI moduri
//	//folositi toate cele TREI moduri de parcurgere
//
//	//printf("\nPreordine:\n");
//	////preordine -> RSD (radacina - st - dr)
//	//if (!nod) {
//	//	printf("\nNod este null in afisareMasiniDinArbore\n");
//	//}
//	//else {
//	//	afisareMasina(nod->info);
//
//	//	if (nod->st) {
//	//		afisareMasiniDinArbore(nod->st);
//	//	}
//	//	if (nod->dr) {
//	//		afisareMasiniDinArbore(nod->dr);
//	//	}
//	//}
//
//	//printf("\nInordine:\n");
//	////inordine -> SRD (st - radacina - dr)
//	//if (!nod) {
//	//	printf("\nNod este null in afisareMasiniDinArbore\n");
//	//}
//	//else {
//	//	if (nod->st) {
//	//		afisareMasiniDinArbore(nod->st);
//	//	}
//
//	//	afisareMasina(nod->info);
//
//	//	if (nod->dr) {
//	//		afisareMasiniDinArbore(nod->dr);
//	//	}
//	//}
//
//	printf("\nPostordine:\n");
//	//postordine -> SDR (st - dr - radacina)
//	if (!nod) {
//		printf("\nNod este null in afisareMasiniDinArbore\n");
//	}
//	else {
//		if (nod->st) {
//			afisareMasiniDinArbore(nod->st);
//		}
//
//		if (nod->dr) {
//			afisareMasiniDinArbore(nod->dr);
//		}
//
//		afisareMasina(nod->info);
//		
//	}
//} 
// 
//
//void dezalocareArboreDeMasini(Nod* nod) {
//	//sunt dezalocate toate masinile si arborele de elemente
//	if (nod) {
//		dezalocareArboreDeMasini(nod->dr);
//		dezalocareArboreDeMasini(nod->st);
//		free(nod->info.model);
//		free(nod->info.numeSofer);
//		free(nod);
//	}
//
//}
//
//Masina getMasinaByID(Nod* nod, int id) {
//	Masina m;
//	m.id = -1;
//	m.model = NULL;
//	m.nrUsi = 0;
//	m.pret = 0.0;
//	m.serie = 'A';
//	m.numeSofer = NULL;
//	if (nod) {
//		if (nod->info.id == id) {
//			m = nod->info;
//			return m;
//		}
//		if (nod->dr) {
//			Masina dr = getMasinaByID(nod->dr, id);
//			if (dr.id != -1) {
//				return dr;
//			}
//		}
//		if (nod->st) {
//			Masina st = getMasinaByID(nod->st, id);
//			if (st.id != -1) {
//				return st;
//			}
//		}
//	}
//	return m;
//}
//
//int determinaNumarNoduri(Nod* nod) {
//	//calculeaza numarul total de noduri din arborele binar de cautare
//	if (!nod) {
//		return 0;
//	}
//
//	int st = determinaNumarNoduri(nod->st);
//	int dr = determinaNumarNoduri(nod->dr);
//	return 1 + dr + st; // a soma acumula o resultado
//}
//
//int calculeazaInaltimeArbore(Nod* nod) {
//	//calculeaza inaltimea arborelui care este data de 
//	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
//	if (!nod) {
//		return 0;
//	}
//	int dr = calculeazaInaltimeArbore(nod->dr);
//	int st = calculeazaInaltimeArbore(nod->st);
//	return 1 + (dr < st ? st : dr); //a comparacao nao muda o resultado
//}
//
//float calculeazaPretTotal(Nod* nod) {
//	//calculeaza pretul tuturor masinilor din arbore.
//	if (!nod) {
//		return 0;
//	}
//
//	int st = calculeazaPretTotal(nod->st);
//	int dr = calculeazaPretTotal(nod->dr);
//	return nod->info.pret + st + dr;
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* nod, const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//	if (!nod) {
//		return 0;
//	}
//	int dr = calculeazaPretulMasinilorUnuiSofer(nod->dr, numeSofer);
//	int st = calculeazaPretulMasinilorUnuiSofer(nod->st, numeSofer);
//
//	if (strcmp(nod->info.numeSofer, numeSofer) == 0) {
//		return nod->info.pret + st + dr;
//	}
//	return st + dr;
//}
//
//int main() {
//	Nod* nod = citireArboreDeMasiniDinFisier("masini_arbore.txt");
//	afisareMasiniDinArbore(nod);
//
//	Masina m = getMasinaByID(nod, 12);
//	printf("\nAfisare Masina:\n");
//	afisareMasina(m);
//
//	int nrNod = determinaNumarNoduri(nod);
//	printf("\nNr Nod: %d\n", nrNod);
//
//	int inaltime = calculeazaInaltimeArbore(nod);
//	printf("\n Inaltime arbore: %d\n", inaltime);
//
//	float pretTotal = calculeazaPretTotal(nod);
//	printf("\ncalcula pret total: %.2f\n", pretTotal);
//
//	float pretTotalSofer = calculeazaPretulMasinilorUnuiSofer(nod, "Ionescu");
//	printf("\ncalcula pret total unui sofer: %.2f\n", pretTotalSofer);
//
//	dezalocareArboreDeMasini(nod);
//	
//	return 0;
//}