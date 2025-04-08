#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct Telefon {
	char* producator;
	int codFabricatie;
	float pret;
	int capacitateBaterie;
};
typedef struct Telefon Telefon;
struct NodD
{
	struct NodD* pre;
	struct NodD* urm;
	Telefon info;

};
typedef struct NodD NodD;
struct Lista
{
	NodD* prim;
	NodD* ultim;
};
typedef struct Lista Lista;

Telefon initializareTastatura(const char* producator, int codFabricatie, float pret, int capacitateBaterie)
{
	Telefon t;
	t.capacitateBaterie = capacitateBaterie;
	t.codFabricatie = codFabricatie;
	t.pret = pret;
	t.producator = (char*)malloc(strlen(producator) + 1);
	strcpy_s(t.producator, strlen(producator) + 1, producator);
	return t;
}
Telefon citireFisier(FILE* f)
{
	Telefon t;
	char buffer[100];
	char* aux;
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	t.codFabricatie = atoi(strtok(buffer, sep));
	aux = strtok(NULL, sep);
	t.producator = (char*)malloc(strlen(aux) + 1);
	strcpy_s(t.producator, strlen(aux) + 1, aux);
	t.pret = atof(strtok(NULL, sep));
	t.capacitateBaterie = atoi(strtok(NULL, sep));
	return t;
}
void afisareTelefon(Telefon t)
{
	printf("Cod telefon: %d\n", t.codFabricatie);
	printf("Producator: %s\n", t.producator);
	printf("Pret: %.3f\n", t.pret);
	printf("Capacitate baterie: %d\n", t.capacitateBaterie);
	printf("\n");
}
void adaugareListaDublaFinal(Lista*l, Telefon m)
{
	NodD* nou=(NodD*)malloc(sizeof(NodD));
	nou->info = m;
	nou->pre = l->ultim;
	nou->urm = NULL;
	if (l->ultim == NULL)
	{
		l->prim = nou;
	}
	else
	{
		l->ultim->urm = nou;
	}
	l->ultim = nou;

}
void adaugareListaInceput(Lista* l, Telefon t)
{
	NodD* nou = (NodD*)malloc(sizeof(NodD));
	nou->pre = NULL;
	nou->info = t;
	nou->urm = l->prim;
	if (l->prim)
	{
		l->prim->pre = nou;

	}
	else
	{
		l->ultim = nou;
	}
	l->prim = nou;
}
void citireListaD(Lista* l, const char* numef)
{
	FILE* f = fopen(numef, "r");
	while (!feof(f))
	{
		adaugareListaInceput(l, citireFisier(f));
	}
	fclose(f);
}
void afisarelistaD(Lista l)
{
	NodD *nou= l.prim;
	while (nou)
	{
		afisareTelefon(nou->info);
		nou = nou->urm;
	}
}

int main()
{
	Telefon t1 = initializareTastatura("Samsung", 23, 2254.99, 5000);
	//afisareTelefon(t1);
	
	Lista l;
	l.prim = NULL;
	l.ultim = NULL;
	citireListaD(&l,"telefoane.txt");
	afisarelistaD(l);
}