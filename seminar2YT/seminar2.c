#include<stdio.h>
#include<malloc.h>
#include<string.h>

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

void afisareVector(struct Telefon* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare  
    for(int i = 0; i < nrElemente; i++){
        afisare(vector[i]);
    } 
}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Telefon *vectorNou=NULL;
    vectorNou = (Telefon*)malloc(sizeof(Telefon)*nrElementeCopiate);
    for(int i= 0; i < nrElementeCopiate; i++){
        vectorNou[i] = vector[i];
        vectorNou[i].model = (char*)malloc(sizeof(char) * (strlen(vector[i].model)+1));
        strcpy(vectorNou[i].model, vector[i].model);
    }
	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
    for(int i = 0; i < (*nrElemente); i++){
        if((*vector)[i].model != NULL){
            free((*vector)[i].model); 
        }
    }
    free(*vector);
    *vector = NULL;
    *nrElemente = 0;
}

void copiazaAnumiteElemente( Telefon* vector, char nrElemente, float prag, Telefon** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
    *dimensiune = 0;
    
    for(int i = 0; i < nrElemente; i++){
        if((vector[i].pret) < prag){
            (*dimensiune)++;
        }
    }
    if(*vectorNou != NULL){
        free(vectorNou);
    }

    *vectorNou = (Telefon*)malloc(sizeof(Telefon)*(*dimensiune));
    int k = 0;
    for(int i = 0; i < nrElemente; i++){
        if((vector[i].pret) < prag){
            (*vectorNou)[k] = vector[i];
            (*vectorNou)[k].model = (char*)malloc(sizeof(char)*(strlen(vector[i].model)+1));
            strcpy((*vectorNou)[i].model, vector[i].model);
            k++;
        }
    }
}

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Telefon s;
    s.model = NULL;
    int count = 0;
    for(int i = 0; i < nrElemente; i++){
        if((strcmp(vector[i].model, conditie) == 0) && count < 1){
            s = vector[i];
            s.model = (char*)malloc(sizeof(char)*(strlen(vector[i].model)+1));
            strcpy(s.model, vector[i].model);
            count++;
        }
    }
	return s;
}
	


int main() {
    Telefon *t = NULL;
    int nrtelefoane = 3;
    t = (Telefon*)malloc(sizeof(Telefon)*nrtelefoane);
    t[0] = initializare(1,16, "samsung", 2000.5, 'A');
    t[1] =  initializare(2, 24, "motorola", 1900.2, 'M');
    t[2] =  initializare(3, 24, "Apple", 5000.2, 'X');
    afisareVector(t, nrtelefoane);
    Telefon* t2 = NULL;
    t2 = copiazaPrimeleNElemente(t, nrtelefoane, 2);
    printf("\n");
    afisareVector(t2, 2);
    
    Telefon* t3 = NULL;
    int dimensiune = 0;
    copiazaAnumiteElemente(t, nrtelefoane,2100.5, &t3, &dimensiune);
    printf("\n");
    afisareVector(t3, dimensiune);

    Telefon t4 = getPrimulElementConditionat(t, nrtelefoane, "samsung");
    printf("\n");
    afisare(t4);
    if(t4.model != NULL){
        free(t4.model);
        t4.model=NULL;
    }
    dezalocare(&t, &nrtelefoane);
    nrtelefoane = 2;
    dezalocare(&t2, &nrtelefoane);
	return 0;
}