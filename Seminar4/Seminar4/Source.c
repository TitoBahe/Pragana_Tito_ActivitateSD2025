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

//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod {
	Masina info;
	struct Nod* next; //isso e de tipo Node pq vamos guardar um endereco de um Node
};
typedef struct Nod Nod;

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

Masina citireMasinaDinFisier(FILE* file) {
	//1, 3, 5000, Astra, Ionescu, A
	char buffer[100];
	fgets(buffer, 100, file);
	char sep[4] = ",\n;";
	Masina m;
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

void afisareListaMasini(Nod* cap) {
	//afiseaza toate elemente de tip masina din lista simplu inlantuita
	//prin apelarea functiei afisareMasina()
	while (cap != NULL) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua; //shallow copy
	nou->next = NULL;

	if (*cap) {
		Nod* aux = *cap;
		while ((aux->next) != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		(*cap) = nou;
	}
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua; //shallow copy
	nou->next = *cap;
	*cap = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	Nod* cap = NULL;
	FILE* file = fopen(numeFisier, "r");
	Masina m;
	if (file != NULL) {
		while (!feof(file)) {
			m = citireMasinaDinFisier(file);
			adaugaMasinaInLista(&cap, m);
		}
	}
	fclose(file);
	return cap;
}

void dezalocareListaMasini(Nod** cap) {
	//sunt dezalocate toate masinile si lista de elemente
	while (*cap) {
		Nod* aux = *cap;
		(*cap) = aux->next;

		if (aux->info.model) {
			free(aux->info.model);
		}
		if (aux->info.numeSofer) {
			free(aux->info.numeSofer);
		}
		free(aux);
	}
}

float calculeazaPretMediu(Nod* cap) {
	//calculeaza pretul mediu al masinilor din lista.
	float pretTotal = 0;
	int nrMasini = 0;
	while (cap) {
		pretTotal += cap->info.pret;
		nrMasini++;
		cap = cap->next;
	}
	if (nrMasini > 0) {
		float media = pretTotal / nrMasini;
		return media;
	}
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	float pret = 0;
	if (cap) {
		while (cap)
		{
			if (strcmp(cap->info.numeSofer, numeSofer) == 0) {
				pret += cap->info.pret;
				
			}
			cap = cap->next;
		}
	}
	return pret;
}

void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	Nod* aux = NULL;
	while (*cap && (*cap)->info.serie == serieCautata) // fazemos isso pq pode começar tipo: A, A, B, A, ... -> queremos deletar os primeiros
	{
		aux = *cap;
		*cap = aux->next;
		if (aux->info.model) {
			free(aux->info.model);
		}
		if (aux->info.numeSofer) {
			free(aux->info.numeSofer);
		}
		free(aux);
		aux = NULL;
	}
	if (*cap) { //aqui verificamos se a lista ainda existe

		Nod* p = *cap;
		while (p) {
			while (p->next && p->next->info.serie != serieCautata) { // verficar o aux->next é a coisa mais importante a se fazer
				p = p->next;
			}
			if (p->next) { //ele so entra aqui quando o aux->next tem a serie procurada
				Nod* aux2 = p->next;
				p->next = aux2->next;
				if (aux2->info.model) {
					free(aux2->info.model);
				}
				if (aux2->info.numeSofer) {
					free(aux2->info.numeSofer);
				}
				free(aux2);
			}
			else { //ele so entra aqui se o qaundo aux for o ultimo elemento, que ja foi verificado pelo while.
				p = NULL;
			}
		}
		
	}
}

int main() {
	Nod* cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);
	printf("Pretul mediu este %5.2f\n", calculeazaPretMediu(cap));
	printf("Pretul masinilor unui sofer este %5.2f\n", calculeazaPretulMasinilorUnuiSofer(cap, "Ionescu"));

	printf("\nErase seria A:\n");

	stergeMasiniDinSeria(&cap, 'A');
	afisareListaMasini(cap);

	dezalocareListaMasini(&cap);
	return 0;
}