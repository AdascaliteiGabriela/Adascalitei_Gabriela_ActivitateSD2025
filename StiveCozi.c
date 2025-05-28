#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
struct Chirias
{
	int codApartament;
	char* nume;
	int varsta;
	float chirie;
};
typedef struct Chirias Chirias;

Chirias citireChirias(FILE* f)
{
	Chirias c;
	char buffer[100];
	char sep[] = ",\n";
	fgets(buffer, 100,f);
	char* aux;
	aux = strtok(buffer, sep);
	if (aux)
		c.codApartament = atoi(aux);
	else
		c.codApartament = 0;
	aux = strtok(NULL, sep);
	if (aux)
	{
		c.nume = (char*)malloc(strlen(aux) + 1);
		strcpy_s(c.nume, strlen(aux) + 1, aux);
	}
	else
		c.nume = NULL;
	aux = strtok(NULL, sep);
	if (aux)
		c.varsta = atoi(aux);
	else
		c.varsta = 0;
	aux = strtok(NULL, sep);
	if (aux)
		c.chirie = atof(aux);
	else
		c.chirie = 0.0;
	return c;
}
void afisareChirias(Chirias c)
{
	printf("Cod apartament: %d\n", c.codApartament);
	printf("Nume chirias: %s\n", c.nume);
	printf("Varsta: %d\n", c.varsta);
	printf("Chirie de plata: %.2f\n\n", c.chirie);
}
typedef struct Nod Nod;
typedef struct ListaD ListaD;
struct Nod {
	Nod* pre;
	Nod* urm;
	Chirias info;
};
struct ListaD {
	Nod* prim;
	Nod* ultim;
};
//STIVA: LIFO->inserare si extragere acelasi capat ->push si pop
//COADA FIFO->inserare un capat, extragere alt capat ->enqueue si dequeue


//COADA
void enqueue(ListaD* coada, Chirias c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->pre = NULL;
	if (coada->prim)
	{
		coada->prim->pre = nou;
		nou->urm = coada->prim;
	}
	else
		coada->ultim = nou;
	coada->prim = nou;
	
}
Chirias dequeue(ListaD* coada)
{
	Chirias c;
	if (coada->ultim)
	{
		Nod* aux = coada->ultim;
		c = aux->info;
		coada->ultim = aux->pre;
		if (coada->ultim)
			coada->ultim->urm = NULL;
		else
			coada->prim = NULL;
		free(aux);
	}
	else
		c.codApartament = -1;
	return c;
}
void dezalocareCoada(ListaD* coada) {
	Nod* p = coada->prim;
	while (p) {
		Nod* aux = p;
		p = p->urm;
		free(aux->info.nume);
		free(aux);
	}
	coada->prim = NULL;
	coada->ultim = NULL;
}
ListaD citireCoadaFisier(const char* numef)
{
	FILE* f = fopen(numef, "r");
	ListaD coada;
	coada.prim = NULL;
	coada.ultim = NULL;

	while (!feof(f))
	{
		enqueue(&coada, citireChirias(f));
	}
	fclose(f);
	return coada;
}

int main()
{
	ListaD coada = citireCoadaFisier("chiriasi.txt");
	afisareChirias(dequeue(&coada));

}