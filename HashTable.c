#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Eveniment
{
	int codEv;
	char* numeEveniment;
	int numarPersoane;
	float cost;

};
typedef struct Eveniment Eveniment;
struct Nod
{
	struct Nod* urm;
	Eveniment info;
};
typedef struct Nod Nod;
struct Hashtable {
	Nod** adrese;
	int dim;
};
typedef struct Hashtable Hashtable;
Hashtable initializareHT(int dimensiune)
{
	Hashtable ht;
	ht.adrese = (Nod**)malloc(sizeof(Nod*)*dimensiune);
	for (int i = 0; i < dimensiune; i++)
		ht.adrese[i] = NULL;
	ht.dim = dimensiune;
	return ht;
}
int calculeazaHash(int dimensiune, int cod)
{
	if (dimensiune == 0)
		return 0;
	return cod % dimensiune;
}
void adaugaListaFinal(Nod* cap, Eveniment e)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = e;
	nou->urm = NULL;
	while (cap->urm)
		cap = cap->urm;
	cap->urm = nou;

}


Eveniment citireEvFisier(FILE* f)
{
	Eveniment e;
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	fgets(buffer, 100, f);
	e.codEv = atoi(strtok(buffer, sep));
	aux = strtok(NULL, sep);
	e.numeEveniment = (char*)malloc(strlen(aux) + 1);
	strcpy_s(e.numeEveniment, strlen(aux) + 1, aux);
	e.numarPersoane = atoi(strtok(NULL, sep));
	e.cost = atof(strtok(NULL, sep));

	return e;
}
void adaugaHT(Hashtable h, Eveniment e)
{
	int poz = calculeazaHash(h.dim, e.codEv);
	if (h.adrese[poz] != NULL)
	{
		adaugaListaFinal(h.adrese[poz], e);
	}
	else
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = e;
		nou->urm = NULL;
		h.adrese[poz] = nou;

	}

}

Hashtable citireHTFisier(const char* numef, int dim)
{
	Hashtable ht= initializareHT(dim);
	ht.dim = dim;
	
	FILE* f = fopen(numef, "r");
	while (!feof(f))
	{
		adaugaHT(ht, citireEvFisier(f));
	}
	return ht;

}

void afisareEv(Eveniment e)
{
	printf("Cod eveniment: %d\n", e.codEv);
	printf("NumeEveniment: %s\n", e.numeEveniment);
	printf("Numar de persoane: %d\n", e.numarPersoane);
	printf("Cost: %.2f\n", e.cost);
	printf("\n");
}
void afisareLista(Nod* nod)
{
	while (nod)
	{
		afisareEv(nod->info);
		nod = nod->urm;
	}
}
void afisareHT(Hashtable h)
{
	for (int i = 0; i < h.dim; i++)
	{
		printf("Pozitia: %d\n", i);
		afisareLista(h.adrese[i]);
		printf("\n\n");
	}
}
void dezalocareLista(Nod** cap)
{
	Nod* aux ;
	while(*cap)
	{
		aux = (*cap);
		(*cap) = (*cap)->urm;
		if (aux->info.numeEveniment)
			free(aux->info.numeEveniment);
		free(aux);

	}
	*cap = NULL;
}
void dezalocaHT(Hashtable* h)
{
	for (int i = 0; i < h->dim; i++)
	{
		if(h->adrese[i])
			dezalocareLista(&h->adrese[i]);
	}
	free(h->adrese);
	h->dim = 0;
	h->adrese = NULL;
	

}
int main()
{
	Hashtable h = citireHTFisier("evenimente.txt", 5);
	afisareHT(h);
	dezalocaHT(&h);
	return 0;
}