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
//int calculeazaInaltimeArbore(Nod* nod) {
//	//calculeaza inaltimea arborelui care este data de 
//	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
//	if (!nod) {
//		return 0;
//	}
//
//	int st = calculeazaInaltimeArbore(nod->st);
//	int dr = calculeazaInaltimeArbore(nod->dr);
//	return 1 + (st > dr ? st : dr);
//}
//
////ALTE FUNCTII NECESARE:
//// - aici veti adauga noile functii de care aveti nevoie.
//Nod* rotireLaDreapta(Nod* nod) {
//	if (nod) {
//		Nod* savatorAdresaST = nod->st; // fazemos isso pq vamos usar essa funcao apenas para quando o desequelibrio for na esquerda
//		nod->st = savatorAdresaST->dr;
//		savatorAdresaST->dr = nod;
//		return savatorAdresaST;
//	}
//	return nod;
//}
//
//Nod* rotureLaSt(Nod* nod) {
//	if (nod) {
//		Nod* savatorAdresaDR = nod->dr;
//		nod->dr = savatorAdresaDR->st;
//		savatorAdresaDR->st = nod;
//		return savatorAdresaDR;
//	}
//	return nod;
//}
//
//int calcularBalanta(Nod* nod){
//	if (nod) {
//		int inaltimeST = calculeazaInaltimeArbore(nod->st);
//		int inaltimeDR = calculeazaInaltimeArbore(nod->dr);
//
//		int balanta = inaltimeST - inaltimeDR;
//		return balanta;
//	}
//	else {
//		return 0;
//	}
//}
//
//Nod* adaugaMasinaInArboreEchilibrat(Nod* nod, Masina masinaNoua) {
//	//adauga o noua masina pe care o primim ca parametru in arbore,
//	//astfel incat sa respecte principiile de arbore binar de cautare ECHILIBRAT
//	//dupa o anumita cheie pe care o decideti - poate fi ID
//	if (!nod) {
//		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//		nodNou->dr = NULL;
//		nodNou->st = NULL;
//		nodNou->info = masinaNoua;
//		return nodNou;
//	}
//	if (nod->info.pret < masinaNoua.pret) {
//		nod->st = adaugaMasinaInArboreEchilibrat(nod->st, masinaNoua);
//	}
//	else {
//		nod->dr = adaugaMasinaInArboreEchilibrat(nod->dr, masinaNoua);
//	}
//
//	if (calcularBalanta(nod) == 2) { //se entrar no if, temos um desequilibio na esquerda
//		if (calcularBalanta(nod->st) != 1) { // se isso for verdadeira, temos a terceira opcao da imaem 
//			nod->st = rotureLaSt(nod->st);
//		}
//		nod = rotireLaDreapta(nod);
//	}
//	if (calcularBalanta(nod) == -2) { //se tiver uma balnça de -2, com certeza, desequilibrio na parte direita.
//		if (calcularBalanta(nod->dr) != -1) // se isso for verdadeiro, temos a 4º opçao da imaem no watsapp
//		{
//			nod->dr = rotireLaDreapta(nod->dr);
//		}
//		nod = rotureLaSt(nod);
//		
//	}
//	return nod; // ai so depois retornamos o no
//}
//
//Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Nod* nod = NULL;
//	while (!feof(file)) {
//		Masina m = citireMasinaDinFisier(file);
//		nod = adaugaMasinaInArboreEchilibrat(nod, m);
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
//	//preordine->RSD(radacina - st - dr)
//	/*if (!nod) {
//		return;
//	}
//	afisareMasina(nod->info);
//	if (nod->st) {
//		afisareMasiniDinArbore(nod->st);
//	}
//	if (nod->dr) {
//		afisareMasiniDinArbore(nod->dr);
//	}*/
//	
//	//inordine -> SRD (st - radacina - dr)
//	
//	if (nod->st) {
//		afisareMasiniDinArbore(nod->st);
//	}
//
//	afisareMasina(nod->info);
//
//	if (nod->dr) {
//		afisareMasiniDinArbore(nod->dr);
//	}
//
//	//post ordine -> SDR (st - dr - radacina)
//	 
//	/*if (nod->st) {
//		afisareMasiniDinArbore(nod->st);
//	}
//	if (nod->dr) {
//		afisareMasiniDinArbore(nod->dr);
//	}
//	afisareMasina(nod->info);*/
//
//}
//
//void dezalocareArboreDeMasini(Nod* nod) {
//	//sunt dezalocate toate masinile si arborele de elemente
//	if (!nod) {
//		return;
//	}
//	if (nod->st) {
//		dezalocareArboreDeMasini(nod->st);
//	}
//	if (nod->dr) {
//		dezalocareArboreDeMasini(nod->dr);
//	}
//	free(nod->info.model);
//	free(nod->info.numeSofer);
//	free(nod);
//}
//
////Preluati urmatoarele functii din laboratorul precedent.
////Acestea ar trebuie sa functioneze pe noul arbore echilibrat.
//
//Masina getMasinaByID(Nod* nod, int id) {
//	Masina m;
//	m.id = -1;
//	m.model = NULL;
//	m.nrUsi = 0;
//	m.numeSofer = NULL;
//	m.pret = 0.0;
//	m.serie = '0';
//
//	if (!nod) {
//		return m;
//	}
//	if (nod->info.id == id) {
//		return nod->info;
//	}
//	
//	if (nod->st) {
//		m = getMasinaByID(nod->st, id);
//		if (m.id != -1) {
//			return m;
//		}
//	}
//	if (nod->dr) {
//		m = getMasinaByID(nod->dr, id);
//		if (m.id != -1) {
//			return m;
//		}
//	}
//
//	return m;
//}
//
//int determinaNumarNoduri(Nod* nod) {
//	if (!nod) {
//		return 0;
//	}
//	int st = determinaNumarNoduri(nod->st);
//	int dr = determinaNumarNoduri(nod->dr);
//
//	return 1 + st + dr;
//}
//
//float calculeazaPretTotal(Nod* nod){
//	if (!nod) {
//		return  0;
//	}
//	int st = calculeazaPretTotal(nod->st);
//	int dr = calculeazaPretTotal(nod->dr);
//	
//	return nod->info.pret + st + dr;
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* nod, const char* numeSofer) {
//	if (!nod) {
//		return 0;
//	}
//	float st = calculeazaPretulMasinilorUnuiSofer(nod->st, numeSofer);
//	float dr = calculeazaPretulMasinilorUnuiSofer(nod->dr, numeSofer);
//
//	return (strcmp(nod->info.numeSofer, numeSofer) == 0 ? nod->info.pret + st + dr : 0 + st + dr);
//}
//
//int main() {
//
//	Nod* nod = citireArboreDeMasiniDinFisier("masini_arbore.txt");
//	afisareMasiniDinArbore(nod);
//
//	Masina m = getMasinaByID(nod, 10);
//	printf("\nMasina cu id %d:\n", 1);
//	afisareMasina(m);
//
//
//	int nr = determinaNumarNoduri(nod);
//	printf("\nNr noduri: %d\n", nr);
//
//
//	float pretTotal = calculeazaPretTotal(nod);
//	printf("\nPret Total: %.2f\n", pretTotal);
//
//	float pretMasiniSofer = calculeazaPretulMasinilorUnuiSofer(nod, "Gheorghe");
//	printf("\nPret masinilor unui sofer: %.2f\n\n", pretMasiniSofer);
//
//
//	Masina m_new;
//	m_new.id = 10000000000000000;
//	m_new.model = NULL;
//	m_new.numeSofer = NULL;
//	m_new.nrUsi = 10000000000;
//	m_new.pret = 100000000000;
//	m_new.serie = 'S';
//
//	nod = adaugaMasinaInArboreEchilibrat(nod, m_new);
//	afisareMasiniDinArbore(nod);
//
//	dezalocareArboreDeMasini(nod);
//	return 0;
//}