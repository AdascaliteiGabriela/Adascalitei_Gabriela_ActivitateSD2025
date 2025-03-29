#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Tablou
{
	int numarInventar;
	float pret;
	char* titlu;
	char* autor;
};
typedef struct Tablou Tablou;
struct Nod
{
	struct Nod* urm;
	Tablou info;
};

typedef struct Nod Nod;
Tablou citireTablouFisier(FILE* f)
{
	Tablou c;
	c.titlu = NULL;
	c.autor = NULL;
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	c.numarInventar = atoi(strtok(buffer, sep));
	c.pret = atof(strtok(NULL, sep));
	char* aux;
	aux = strtok(NULL, sep);
	c.titlu = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c.titlu, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	c.autor = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c.autor, strlen(aux) + 1, aux);


	return c;
}
void afisareTablou(Tablou t)
{
	printf("Numar inventar: %i\nPret tablou: %.2f\nTitlu tablou: %s\nAutor Tablou: %s\n\n", t.numarInventar, t.pret, t.titlu, t.autor);
}
void adaugaTablouLista(Tablou t,Nod** cap)
{
	//intai imi creez un nod nou pe care sa il adaug la lista
	//ii aloc memorie si il initializez
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = t;
	nou->urm = NULL;
	
	if ((*cap))//daca exista capul listei
	{
		Nod* p = *cap;//iau un nod nou cu care sa parcurg lista pentru ca daca as parcurge direct cu cap, acesta s ar modifica si as pierde valori(Cap e transmis prin adresa!)
		while (p->urm)
			p = p->urm;
		p->urm = nou;
	}
	else
	{
		(*cap) = nou;
	}
	
}
Nod* citireListaFisier(FILE* f)
{
	Nod* cap = NULL;
	while (!feof(f))
	{
		adaugaTablouLista(citireTablouFisier(f), &cap);
	}
	return cap;
}
void afisareLista(Nod* cap)
{
	int i = 1;
	while (cap)
	{
		afisareTablou(cap->info);
		printf("\n\nAm ajuns pe pozitia %i\n\n", i);
		cap = cap->urm;
		i++;
	}
}
int main()
{
	Tablou t;
	FILE* f = fopen("tablouri.txt", "r");
	
	t = citireTablouFisier(f);
	afisareTablou(t);
	fclose(f);
	 f = fopen("tablouri.txt", "r");
	Nod* cap =  citireListaFisier(f);
	afisareLista(cap);

	return 0;
}