#include<stdio.h>
#include<stdlib.h>
#include <string.h>


typedef struct Telefon {
	int id;
	int RAM;
	char* model;
	float pret;
	char serie;
} Telefon;

Telefon initializare(int id, int RAM, char* model, float pret, char serie) {
	struct Telefon t;
	t.id = id;
	//initializare structura 
    t.RAM = RAM;
    t.model = (char*)malloc(sizeof(char)*(strlen(model)+1));
    strcpy(t.model, model);
    t.pret = pret;
    t.serie = serie;
	return t;
} 

void afisare(Telefon t) {
    if(t.model != NULL){
        printf("%d Telefonul %s seria %c are %d gb RAM si costa %5.2f RON\n", t.id, t.model, t.serie, t.RAM, t.pret);
    }
	else{
        printf("%d Telefonul din seria %c are %d gb RAM si costa %5.2f RON\n", t.id, t.serie, t.RAM, t.pret);
    }
}

void modificaPret(Telefon* t, float noulPret) {
	//modificarea unui atribut
    if(noulPret> 0){
        t->pret = noulPret;
    }
}

void dezalocare(Telefon *t) {
    if(t->model != NULL){
        free(t->model);
        t->model = NULL;
    }
	//dezalocare campuri alocate dinamic
}

int main() {
    Telefon t;
	t = initializare(1, 256, "samsung", 2000.5, 'A');
    afisare(t);
    modificaPret(&t, 1000);
    afisare(t);
    dezalocare(&t);
    afisare(t);
	return 0;
}