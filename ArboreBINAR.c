#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Animal
{
	int codIdentificare;
	char* specie;
	int varsta;
	float greutate;

};
typedef struct Animal Animal;
typedef struct Nod Nod;
Animal citireAnimlFisier(FILE* f)
{
	Animal a;
	char buffer[100];
	char* aux;
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	a.codIdentificare = atoi(strtok(buffer, sep));
	aux = strtok(NULL, sep);
	a.specie = (char*)malloc(strlen(aux) + 1);
	strcpy_s(a.specie, strlen(aux) + 1, aux);
	a.varsta = atoi(strtok(NULL, sep));
	a.greutate = atof(strtok(NULL, sep));

	return a;
}
void afisareAnimal(Animal a)
{
	printf("Cod animal: %d\n", a.codIdentificare);
	printf("Specie: %s\n", a.specie);
	printf("Varsta: %d\n", a.varsta);
	printf("Greutate: %.2f\n", a.greutate);
	printf("\n");
}
//pentru arbore binar am nevoie de
//	structura arbore (Nod* stg,Nod*drp, info)
//		functie de adaugare nod in arbore
//		functie de citire arbore
//		functie de afisare arbore

struct Nod {
	Nod* stg;
	Nod* drp;
	Animal info;
};
void adaugareNodArbore(Nod** cap, Animal a)
{
	if (*cap)
	{
		if (a.codIdentificare < (*cap)->info.codIdentificare)
			adaugareNodArbore(&((*cap)->stg), a);
		else if (a.codIdentificare > (*cap)->info.codIdentificare)
			adaugareNodArbore(&((*cap)->drp), a);
		else
		{
			(*cap)->info.codIdentificare = a.codIdentificare;
			(*cap)->info.greutate = a.greutate;
			(*cap)->info.varsta = a.varsta;
			if (a.specie)
			{
				if ((*cap)->info.specie)
					free((*cap)->info.specie);
				(*cap)->info.specie = (char*)malloc(strlen(a.specie) + 1);
				strcpy_s((*cap)->info.specie, strlen(a.specie) + 1, a.specie);
			}
			else
				a.specie = NULL;
		}
	}
	else {
		(*cap) = (Nod*)malloc(sizeof(Nod));
		(*cap)->drp = NULL;
		(*cap)->stg = NULL;
		(*cap)->info.codIdentificare = a.codIdentificare;
		(*cap)->info.greutate = a.greutate;
		(*cap)->info.varsta = a.varsta;
		if (a.specie)
		{
			(*cap)->info.specie = (char*)malloc(strlen(a.specie) + 1);
			strcpy_s((*cap)->info.specie, strlen(a.specie) + 1, a.specie);
		}
		else
			a.specie = NULL;
	}
}
Nod* citireArbore(const char* numef)
{
	Nod* cap = NULL;

	FILE* f = fopen(numef, "r");
	while (!feof(f))
	{
		Animal a = citireAnimlFisier(f);
		adaugareNodArbore(&cap, a);
		free(a.specie);
	}

	fclose(f);
	return cap;
}
void afisareArboreOrdine(Nod* cap)
{
	if (cap) {
		afisareArboreOrdine(cap->stg);
		afisareAnimal(cap->info);//ATENTIE AICI!!!
		afisareArboreOrdine(cap->drp);
	}
}

int main()
{
	Nod* arbore = citireArbore("animale.txt");
	afisareArboreOrdine(arbore);
}