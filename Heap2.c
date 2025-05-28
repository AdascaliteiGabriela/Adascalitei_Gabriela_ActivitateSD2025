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
typedef struct Heap Heap;

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

//structura Heap
struct Heap {
	int lungime;
	Tablou* tablouri;
	int nrTablouri;
};

//functie initializare

Heap initializareHeap(int numar)
{
	Heap heap;
	heap.lungime = numar;
	heap.nrTablouri = 0;
	heap.tablouri = (Tablou*)malloc(sizeof(Tablou) * numar);
	return heap;
}
//functie de filtrare
void filtrare(Heap heap, int poz)
{
	if (poz < heap.nrTablouri && poz >= 0)
	{
		int stg = 2 * poz + 1;
		int drp = 2 * poz + 2;
		int pozMin = poz;
		if (stg < heap.nrTablouri && heap.tablouri[stg].numarInventar < heap.tablouri[pozMin].numarInventar)
			pozMin = stg;
		if (drp < heap.nrTablouri && heap.tablouri[drp].numarInventar < heap.tablouri[pozMin].numarInventar)
			pozMin = drp;
		if (pozMin != poz)
		{
			Tablou aux = heap.tablouri[pozMin];
			heap.tablouri[pozMin]=heap.tablouri[poz];
			heap.tablouri[poz] = aux;

			filtrare(heap, pozMin);
		}
	}
}
//functie de citire Heap
Heap citireHeap(const char* numef)
{
	Heap heap = initializareHeap(10);
	FILE* f = fopen(numef, "r");
	while (!feof(f))
	{
		Tablou t = citireTablouFisier(f);
		heap.tablouri[heap.nrTablouri] = t;
		heap.nrTablouri++;
	}
		fclose(f);//INCHIDERE FISIER!
		for(int i=(heap.nrTablouri-1)/2;i>=0;i--)
			filtrare(heap, i);

		return heap;//ATentie!! sa nu uiti asta
}

//functie de afisare Heap
void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.nrTablouri; i++)
		afisareTablou(heap.tablouri[i]);
}

//functie de extragere din heap

int main()
{
	FILE* f = fopen("tablouri.txt", "r");
	

	Heap heap = citireHeap("tablouri.txt");
	afisareHeap(heap);
}