#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

//ARTICOL care contine A si G
struct Agentie
{
	char* numeAgentie;//atribut alocat dinamic
	int numarAngajati;
	float valoareIncasari;
	int anInfiintare;
};
typedef struct Agentie Agentie;
void afisareAgentie(Agentie a)
{
	printf("Agentia %s a fost infiintata in anul %d si are %d angajati.\n", a.numeAgentie, a.anInfiintare, a.numarAngajati);
	printf("Valoarea incasarilor este : %.2f\n\n", a.valoareIncasari);
}
Agentie citireAgentie(FILE* f)
{
	Agentie a;
	char buffer[100];
	char sep[] = ",\n";
	fgets(buffer, 100, f);
	char* aux = strtok(buffer, sep);
	if (aux)
	{
		a.numeAgentie = (char*)malloc(strlen(aux) + 1);
		strcpy_s(a.numeAgentie, strlen(aux) + 1, aux);

	}
	aux = strtok(NULL, sep);
	if (aux)
		a.numarAngajati = atoi(aux);
	else
		a.numarAngajati = 0;
	aux = strtok(NULL, sep);
	if (aux)
	{
		a.anInfiintare = atoi(aux);
	}
	else
		a.anInfiintare = 1700;
	aux = strtok(NULL, sep);
	if (aux)
	{
		a.valoareIncasari = atof(aux);
	}
	else
		a.anInfiintare = 0.0;
	return a;
}
//am nev de 
//	-functie de filtrare
//	-functie initializare heap
//	-functie de citire heap din fisier
//	-structura heap
//	-functie de afisare heap(el vizibile) + eventual pt el ascunse
//	-functie de extragere element din heap
struct Heap {
	int lungime;//va fi egal cu totalul capacitatii din heap
	Agentie* agentii; //vector de agentii
	int nrAgentii;//elementele vizibile
};
typedef struct Heap Heap; //heap heap ura :)
Heap initializareHeap(int numar)
{
	Heap nou;
	nou.lungime = numar;
	nou.nrAgentii = 0;//la initializare avem 0 agentii efectiv
	nou.agentii = (Agentie*)malloc(numar * sizeof(Agentie));//alocat memorie!!!!
	return nou;
}
//voi face un MINHEAP in functie de numarul de angajati
void filtrareHeap(Heap heap, int pozitie)
{
	//intai verific daca pozitia corespunde adica daca e mai mare ca 0 si daca e intre numarul vizibil de agentii(filtram doar pe cele vizibile)
	if (pozitie >= 0 && pozitie < heap.nrAgentii)
	{
		//imi salvez pozitiile copiilor
		int stg = 2 * pozitie + 1;
		int drp = 2 * pozitie + 2;
		//salvez pozitia minima ca fiind asta, iar apoi verific daca copiii sunt mai mici, daca da pozitia maxima devine poz copilului
		int pozMin = pozitie;
		//compar copiii cu parintele, daca exista copilul(!!!!!!)
		if (stg < heap.nrAgentii && (heap.agentii[stg].numarAngajati < heap.agentii[pozMin].numarAngajati))//ATENTIE!!! compar cu pozMin nu cu pozitie!!!!
			pozMin = stg;
		if (drp < heap.nrAgentii && heap.agentii[drp].numarAngajati < heap.agentii[pozMin].numarAngajati)
			pozMin= drp;
		if (pozitie != pozMin)//daca am gasit un copil mai mare fac interschimbul celor 2 obiecte in vector
		{
			Agentie aux = heap.agentii[pozitie];
			heap.agentii[pozitie] = heap.agentii[pozMin];
			heap.agentii[pozMin] = aux;
			//daca am interschimbat trebuie iar sa filtrez
			filtrareHeap(heap, pozMin);
		}
		
	}
}
//functie de citire heap
Heap citireHeap(const char* numef)
{
	Heap heap = initializareHeap(10);//intai initializez ca sa am ce modifica/citi :)
	FILE* f = fopen(numef, "r");
	while (!feof(f))
	{
		heap.agentii[heap.nrAgentii] = citireAgentie(f);
		heap.nrAgentii++;
	}
	fclose(f);
	for (int i = (heap.nrAgentii-1)/2; i >= 0; i--)
		filtrareHeap(heap, i);

	return heap;
}

//functie afisare heap
void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.nrAgentii; i++)
		afisareAgentie(heap.agentii[i]);
		
}
//functie de extragere heap
Agentie extragere(Heap* heap)//transmit prin adresa pt ca modific nrAgentii (va scadea) 
{
	if (heap->nrAgentii > 0) {
		Agentie a = heap->agentii[0];
		heap->agentii[0] = heap->agentii[heap->nrAgentii - 1];
		heap->agentii[heap->nrAgentii - 1] = a;
		heap->nrAgentii--;
		for (int i = (heap->nrAgentii - 1) / 2; i >= 0; i--)//!!!!!TREBUIE SA FILTRAM IAR HEAP!!!!!!!!!
			filtrareHeap(*heap, i);
			return a;
	}
	else
	{
		Agentie a;
		a.numarAngajati = -1;
		return a;
	}
}
int main()
{
	Heap heap = citireHeap("agentii.txt");
	afisareHeap(heap);
	printf("\n\nExtragere prima agentie: \n");
	afisareAgentie(extragere(&heap));
	printf("\n\nExtragere prima agentie: \n");
	afisareAgentie(extragere(&heap));
	printf("\n\nExtragere prima agentie: \n");
	afisareAgentie(extragere(&heap));
	printf("\n\nExtragere prima agentie: \n");
	afisareAgentie(extragere(&heap));
	printf("\n\nExtragere prima agentie: \n");
	afisareAgentie(extragere(&heap));
}