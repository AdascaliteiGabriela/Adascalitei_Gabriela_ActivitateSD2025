#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Elev
{
	int codInmatriculare;
	float medieAnuala;
	char* nume;
	int varsta;
};
typedef struct Elev Elev;
typedef struct Nod Nod;
struct Nod
{
	Nod* stg;
	Nod* drp;
	Elev info;
};

Elev citireFisier(FILE* f)
{
	Elev e;
	char buffer[100];
	char sep[] = ",\n";
	fgets(buffer, 100, f);
	char* aux = strtok(buffer, sep);
	if (aux)
	{
		e.nume = (char*)malloc(strlen(aux) + 1);
		strcpy_s(e.nume, strlen(aux) + 1, aux);
	}
	aux = strtok(NULL, sep);
	if (aux)
		e.codInmatriculare = atoi(aux);
	else
		e.codInmatriculare = 0;
	aux = strtok(NULL, sep);
	if (aux)
		e.varsta = atoi(aux);
	else
		e.varsta = 0;
	aux = strtok(NULL, sep);
	if (aux)
		e.medieAnuala = atof(aux);
	else
		e.medieAnuala = 0.0;
	return e;
}

void adaugaElevArbore(Nod** cap, Elev nou)
{
	if (*cap)
	{
		if (nou.codInmatriculare < (*cap)->info.codInmatriculare)
			adaugaElevArbore(&((*cap)->stg), nou);
		else if (nou.codInmatriculare > (*cap)->info.codInmatriculare)
			adaugaElevArbore(&((*cap)->drp), nou);
		else
		{
			(*cap)->info.medieAnuala = nou.medieAnuala;
			(*cap)->info.varsta = nou.varsta;
			if ((*cap)->info.nume)
				free((*cap)->info.nume);
			(*cap)->info.nume = (char*)malloc(strlen(nou.nume) + 1);
			strcpy_s((*cap)->info.nume, strlen(nou.nume) + 1, nou.nume);


		}
	}
	else
	{
		(*cap) = (Nod*)malloc(sizeof(Nod));
		(*cap)->stg = NULL;
		(*cap)->drp = NULL;
		(*cap)->info.codInmatriculare = nou.codInmatriculare;
		(*cap)->info.medieAnuala = nou.medieAnuala;
		(*cap)->info.varsta = nou.varsta;
		(*cap)->info.nume = (char*)malloc(strlen(nou.nume) + 1);
		strcpy_s((*cap)->info.nume, strlen(nou.nume) + 1, nou.nume);
	}
}
Nod* citireArboreFisier(const char* numef)
{
	FILE* f = fopen(numef,"r");
	Nod* cap = NULL;
	while (!feof(f))
	{
		Elev a = citireFisier(f);
		adaugaElevArbore(&cap, a);
		free(a.nume);
	}
	fclose(f);
	return cap;
}
void afisareElev(Elev e)
{
	printf("Elevul %s are varsta %d si are media %.2f\n", e.nume, e.varsta, e.medieAnuala);
	printf("Acesta are codul de inmatriculare: %d\n\n", e.codInmatriculare);
}
void afisareArbore(Nod* cap)
{
	if (cap)
	{
		afisareArbore(cap->stg);
		afisareElev(cap->info);
		
		afisareArbore(cap->drp);
	}
}
int main()
{
	Nod* cap = citireArboreFisier("elevi.txt");
	afisareArbore(cap);
	return 0;
}