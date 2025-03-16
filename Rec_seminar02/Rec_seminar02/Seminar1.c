#include<stdio.h>
#include<malloc.h>

struct Masina {
	int id;
	char* model;
	float tonaj;
	char serie;
};
struct Masina initializare(int id, const char* model, float tonaj, char serie) {
	//initializare structura 
	struct Masina s;
	s.id = 1;
	s.tonaj = tonaj;
	s.serie = serie;
	s.model = malloc(sizeof(char) * (strlen(model) + 1));
	strcpy_s(s.model, (strlen(model) + 1), model);
	return s;
}

void afisare(struct Masina s) {
	//afisarea tuturor atributelor.
	printf("\nId: %d\nmodel: %s\ntonaj: %.2f\nserie:%c", s.id, s.model, s.tonaj, s.serie);
}

void afisareVector(struct Masina* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna, primele nrElementeCopiate
	struct Masina*vectorNou=malloc(sizeof(struct Masina)*nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {
		vectorNou[i] = vector[i];
		vectorNou[i].model = malloc(sizeof(char) *(strlen(vector[i].model)+1));
		strcpy_s(vectorNou[i].model, strlen(vector[i].model) + 1, vector[i].model);
	}

	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].model); // primeiro dereferenciamos e depois acessamos o objeto e o atributo especifico
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaAnumiteElemente(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].tonaj < prag) {
			(*dimensiune)++; //colocamos entre parenteses, para nao passar para o proximo elemento e sim adicionar 1 ao elemento
		}
	}
	(*vectorNou) = malloc(sizeof(struct Masina) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].tonaj < prag) {
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].model = malloc(sizeof(char) * (strlen(vector[i].model) + 1));
			strcpy_s((*vectorNou)[k].model, strlen(vector[i].model) + 1, vector[i].model);
			k++;
		}
	}
}

//temaaaaa, usar strcmp
struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Masina s;
	s.id = 1;

	return s;
}
	


int main() {
	struct Masina m; 
	m = initializare(1, "audi", 100.45, 's');
	afisare(m);
	struct Masina* vectorMasini;
	int nrMasini = 3;
	vectorMasini = malloc(sizeof(struct Masina) * nrMasini);
	vectorMasini[0] = initializare(2, "BMW", 100.45, 's');
	vectorMasini[1] = initializare(3, "Dacia", 1.45, 'a');
	vectorMasini[2] = initializare(4, "Renault", 10.45, 'b');
	afisareVector(vectorMasini, nrMasini);
	int nrelementeCopiate = 2;
	struct Masina* vectorMasiniCopiate = copiazaPrimeleNElemente(vectorMasini, nrMasini, nrelementeCopiate);
	afisareVector(vectorMasiniCopiate, nrelementeCopiate);
	dezalocare(&vectorMasiniCopiate, &nrelementeCopiate);
	int dimensiune;
	copiazaAnumiteElemente(vectorMasini, nrMasini, 11.00, &vectorMasiniCopiate, &dimensiune);
	printf("\n");
	afisareVector(vectorMasiniCopiate, dimensiune);
	return 0;
}