#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	//afiseaza toate atributele unei masini
    printf("%d Masina, nrUsi %d, pret %5.2f, model %s, numeSofer %s, seria %c\n", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector
	//prin apelarea functiei afisareMasina()
    if(masini != NULL){
        for(int i = 0; i < nrMasini; i++){
            afisareMasina(masini[i]);
        }
    }
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	//adauga in vectorul primit o noua masina pe care o primim ca parametru
	//ATENTIE - se modifica numarul de masini din vector;
    Masina* m = (Masina*)malloc(sizeof(Masina) * ((*nrMasini)+1));
    int nrMasiniOld = (*nrMasini);

    for(int i = 0; i < nrMasini; i++){
        m[i] = (*masini)[i];
        m[i].model = (char*)malloc(sizeof(char)*(strlen((*masini)[i].model)+1));
        strcpy(m[i].model, (*masini)[i].model);
    }
    m[*nrMasini] = masinaNoua;
    m[*nrMasini].model = (char*)malloc(sizeof(char)* (strlen(masinaNoua.model)+1));
    strcpy(m[*nrMasini].model, masinaNoua.model);

    dezalocareVectorMasini(masini, nrMasini);

    *masini = (Masina*)malloc(sizeof(Masina) * ((nrMasiniOld)+1));

    for(int i = 0; i < nrMasiniOld; i++){
        (*masini)[i] = m[i];
        (*masini)[i].model = (char*)malloc(sizeof(char)*(strlen(m[i].model)+1));
        strcpy((*masini)[i].model, m[i].model);
    }

}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
    for(int i  = 0; i < (*nrMasini); i++){
        free((*vector)[i].model);
    }
    free(*vector);
    *nrMasini = 0;
    *vector = NULL;
}

int main() {
    Masina m;
    m.id = 1;
    m.nrUsi = 4;
    m.model = "Dacia";
    m.numeSofer = "Tito";
    m.pret = 24000.5;
    m.serie = 'A';
    afisareMasina(m);

	return 0;
}