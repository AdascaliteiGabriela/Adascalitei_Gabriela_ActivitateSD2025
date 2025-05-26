#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//arbore=graf conex si aciclic


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
struct NodPrincipal {
	NodPrincipal* urm;
	NodSecundar* vecini;
	Masina info;

};
struct NodSecundar {
	NodPrincipal* info;
	NodSecundar* urm;
};

NodPrincipal* inserareListaPrincipala(NodPrincipal* cap, Masina info)
{
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = info;
	nou->vecini = NULL;
	nou->urm = NULL;
	if (!cap)
		return nou;
	else
	{
		NodPrincipal* aux = cap;
		while (aux->urm)
			aux = aux->urm;
		aux->urm = nou;
		return cap;
	}
}
NodSecundar* inserareListaSecundara(NodSecundar* cap, NodPrincipal* info)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->info = info;
	nou->urm = cap;
	return nou;
}

NodPrincipal* cautaNodDupaID(NodPrincipal* listaPrincipala, int id) {
	while (listaPrincipala && listaPrincipala->info.id != id)
	{
		listaPrincipala = listaPrincipala->urm;
	}
	return listaPrincipala;
}

void inserareMuchie(NodPrincipal* listaPrincipala, int idStart, int idStop) {
	NodPrincipal* nodStart = cautaNodDupaID(listaPrincipala, idStart);
	NodPrincipal* nodStop = cautaNodDupaID(listaPrincipala, idStop);
	if (nodStart && nodStop) {
		nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
		nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);
	}
}


NodPrincipal* citireNoduriMasiniDinFisier(const char* numeFisier) {
	NodPrincipal* listaPrincipala = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f))
	{
		listaPrincipala=inserareListaPrincipala(listaPrincipala, citireMasinaDinFisier(f));
	}
	fclose(f);
	return listaPrincipala;
}

void citireMuchiiDinFisier(NodPrincipal* listaPrincipala, const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f))
	{
		int idStart;
		int idStop;
		fscanf(f, "%d %d", &idStart, &idStop);
		inserareMuchie(listaPrincipala, idStart, idStop);
	}
}
void stergereListaSecundara(NodSecundar** cap)
{
	NodSecundar* aux = (*cap)->urm;
	while (*cap)
	{
		aux = (*cap)->urm;
		free(*cap);
		(*cap) = aux;
	}
}
void dezalocareNoduriGraf(NodPrincipal** listaPrincipala) {
	NodPrincipal* aux;
	while ((*listaPrincipala))
	{
		stergereListaSecundara(&((*listaPrincipala)->vecini));
		aux = (*listaPrincipala)->urm;
		if ((*listaPrincipala)->info.numeSofer)
			free((*listaPrincipala)->info.numeSofer);
		if ((*listaPrincipala)->info.model)
			free((*listaPrincipala)->info.model);
		free(*listaPrincipala);
		(*listaPrincipala) = aux;
		

	}
}

int main() {
	NodPrincipal* graf = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");
	dezalocareNoduriGraf(&graf);

	return 0;
}
