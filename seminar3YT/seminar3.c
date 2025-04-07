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

    for(int i = 0; i < (*nrMasini); i++){
        m[i] = (*masini)[i];
    }
    m[(*nrMasini)] = masinaNoua;

    free((*masini));
    (*masini) = m;
    (*nrMasini)++;

}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;
    Masina m;
    char buffer[100];
    char sep[4]=",;\n";
    fgets(buffer, 100, file);
    printf("Buffer: %s\n", buffer);
    m.id = atoi(strtok(buffer, sep)); //usamos o _CRT_SECURE_NO_WARNINGS
    //atoi -> Ascii TO Integer
    m.nrUsi = atoi(strtok(NULL, sep)); //damos NULL aqui para ele continuar de onde parou, se dermos buffer de novo, ele vai dar o primeiro item de novo
    m.pret= atof(strtok(NULL, sep));

    char*aux;
    aux = strtok(NULL, sep); //usamos um char* aqui pq nao sabemos o tamanho da string e precisamos 
    m.model = (char*)malloc(sizeof(char)*(strlen(aux)+1)); //agora aqui podemos alocar a quant certa pq temos o valor no aux
    strcpy(m.model, aux);

    aux = strtok(NULL, sep);
    m.numeSofer = (char*)malloc(sizeof(char)*(strlen(aux)+1));
    strcpy(m.numeSofer, aux);

    m.serie = strtok(NULL, sep)[0];//usamos [0] pq strtok returna um char* entao pegamos o primeiro elemenot que e nosso char

    return m;

}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul

    FILE* file = fopen(numeFisier, "r");
    Masina *masini = NULL;
    (*nrMasiniCitite) = 0;
    while(!feof(file)){
        adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
    } 
    fclose(file);
    return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
    for(int i  = 0; i < (*nrMasini); i++){
        if((*vector)[i].model != NULL){
            free((*vector)[i].model);
        }
        if((*vector)[i].numeSofer != NULL){
            free((*vector)[i].numeSofer);
        }
    }
    free(*vector);
    (*nrMasini) = 0;
    (*vector) = NULL;
}

int main() {
    Masina* m;
    int nrMasiniCitite = 0;
    m = citireVectorMasiniFisier("masini.txt", &nrMasiniCitite);
    afisareVectorMasini(m, nrMasiniCitite);
    dezalocareVectorMasini(&m, &nrMasiniCitite);
	return 0;
}