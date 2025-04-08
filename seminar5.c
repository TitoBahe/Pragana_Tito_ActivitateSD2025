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

//creare structura pentru un nod dintr-o lista dublu inlantuita
struct Nod {
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

//creare structura pentru Lista Dubla 
struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};
typedef struct ListaDubla Lista;

//while
//1, 3, 5000, Astra, Ionescu, A
Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	fgets(buffer, 100, file);
	Masina m;
	char sep[4] = ",;\n";
	m.id = atoi(strtok(buffer, sep));
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));
	char* aux = strtok(NULL, sep);
	m.model = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(m.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m.numeSofer = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(m.numeSofer, strlen(aux) + 1, aux);
	m.serie = *strtok(NULL, sep);
	return m;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasiniDelaInceput(Lista lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* cap = lista.first;
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void afisareListaMasiniDeLaFinal(Lista lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* coada = lista.last;
	while (coada) {
		afisareMasina(coada->info);
		coada = coada->prev;
	}
}

void adaugaMasinaInLista(Lista* lista, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua; //sallow copy
	nou->next = NULL;
	nou->prev = lista->last;
	
	if (lista->last) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->nrNoduri++;
	lista->last = nou;
	
	
}

void adaugaLaInceputInLista(Lista* lista, Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua; //sadow copy
	nou->next = lista->first;
	if (lista->first) {
		lista->first->prev = nou;
	}
	else {
		lista->last = nou;
	}
	lista->nrNoduri++;
	lista->first = nou;
}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	Lista lista;
	lista.last = NULL;
	lista.first = NULL;
	lista.nrNoduri = 0;
	while (!feof(file))
	{
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(file));
	}
	fclose(file);
	return lista;
}

void dezalocareLDMasini(Lista* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	Nod* cap = lista->first;
	while (cap)
	{
		Nod* aux = cap;
		cap = aux->next;
		if (aux->info.model) {
			free(aux->info.model);
		}
		if (aux->info.numeSofer) {
			free(aux->info.numeSofer);
		}
		free(aux);
		lista->nrNoduri--;
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

float calculeazaPretMediu(Lista lista) {
	//calculeaza pretul mediu al masinilor din lista.
	Nod* cap = lista.first;
	float pret = 0;
	while (cap)
	{
		pret += cap->info.pret;
		cap = cap->next;
	}
	if (lista.nrNoduri > 0) {
		return pret / lista.nrNoduri;
	}
	return 0;
	
}

void stergeMasinaDupaID(Lista* lista, int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	if (lista->first == NULL) { //se o primeiro for nulo, retornamos pois nao temos mais pq ler a lista
		return;
	}
	Nod* p = lista->first;
	while (p && p->info.id != id) { //como e por id, so tem um carro com esse id, por isso fazemos assim
		p = p->next;
	}
	if (p == NULL) { //no caso de nao existir mais lista
		return;
	}
	//se p nao for nulo, temos o que apaar
	//agora precisamos verificar se p é o primeiro, do meio ou último nó.
	//começamos supondo que seja o primeiro
	if (p->prev == NULL) {// se p for o primeiro no, o prev dele sera nulo, entao se ele entrar nesse if, significa que ele é o primeiro nó
		lista->first = p->next;
		if (lista->first) {
			lista->first->prev = NULL;
		}
	}
	else { //ele entra no else se nao for o primeiro nó, portanto vamos considerar, primeiro, que ele está no meio da lista
		p->prev->next = p->next;
		
	}
	if (p->next != NULL) {
		p->next->prev = p->prev;
	}
	else {
		lista->last = p->prev;
	}
	if (p->info.model) {
		free(p->info.model);
	}
	if (p->info.numeSofer) {
		free(p->info.numeSofer);
	}
	free(p);
	lista->nrNoduri--;

	//testar depois verificar se o temp->next->prev, se o temp->next for null, semdo o temp = cap->next, entao ele e o ultimo item, faz o free e transofrma o cap em NULL
	//e colocar o lista->last = temp->prev;
	//tmb nao esquecer que nesse caso, depois que encontrei o com o id certo, como so existe um, posso tranforma cap em NULL para quebrar o wile 
	// ou dar o return
	//testar com o id sendo o primeiro, um do meio e o ultimo
}

char* getNumeSoferMasinaScumpa(Lista lista) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	float pretMaiScump = 0;
	char* numerSofer = NULL;
	Nod* cap = lista.first;
	if (cap) {
		while (cap)
		{
			if (cap->info.pret > pretMaiScump) {
				pretMaiScump = cap->info.pret;
				//numerSofer = cap->info.numeSofer;

				//so to fazendo assim pq o professor fez um deep copy no video... Escolher na hora como fazer
				if (numerSofer != NULL) {
					free(numerSofer);
				}
				numerSofer = (char*)malloc(sizeof(char) * (strlen(cap->info.numeSofer) + 1));
				strcpy_s(numerSofer, strlen(cap->info.numeSofer) + 1, cap->info.numeSofer);
			}
			cap = cap->next;
		}
		return numerSofer;
	}
	return NULL;
}

int main() {
	Lista lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDelaInceput(lista);
	printf("\n\nDE LA FINAL \n\n");
	afisareListaMasiniDeLaFinal(lista);

	printf("\n\n PRETUL MEDIU \n\n");
	float pret = calculeazaPretMediu(lista);
	printf("%.2f", pret);

	printf("\n\nERASE ID = 2\n\n");
	stergeMasinaDupaID(&lista, 2);
	afisareListaMasiniDelaInceput(lista);

	printf("\n\n SOFER CU CEA MAI SCUMPA MASINA \n\n");
	char* numerSofer = getNumeSoferMasinaScumpa(lista);
	printf("%s", numerSofer);
	if (numerSofer) {
		free(numerSofer);
	}
	dezalocareLDMasini(&lista);
	return 0;
}