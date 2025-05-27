#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structura pacient
struct Pacient {
	char* nume;
	int grad;//voi salva gradul printr-un char, poate fi reprezentat alfabetic de la A la Z(A cel mai grav, Z cel mai usor)
	char* CNP;
	int ambulanta;

};
typedef struct Pacient Pacient;

struct Heap {
	int lungime; //nr vizibil pacienti
	Pacient* pacienti; //vector pacienti
	int nrPacient; //total pacienti 
};
typedef struct Heap Heap;

void afisarePacient(Pacient p)
{
	printf("Nume pacient: %s\n", p.nume);
	printf("Grad urgenta: %d\n", p.grad);
	printf("CNP: %s\n", p.CNP);
	printf("Transportat cu ambulanta?");
	if (p.ambulanta == 0) 
		printf(" NU!\n\n");
	else 
		printf(" DA!\n\n");
}

Pacient citirePacientFisier(FILE* f)
{
	Pacient p;
	char buffer[100];
	char sep[] = ",\n";
	fgets(buffer, 100, f);
	char* aux = strtok(buffer, sep);
	p.nume = (char*)malloc(strlen(aux) + 1);
	strcpy_s(p.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	if(aux)
		p.grad = atoi(aux);
	aux = strtok(NULL, sep);
	p.CNP = (char*)malloc(strlen(aux) + 1);
	strcpy_s(p.CNP, strlen(aux) + 1, aux);
	
	aux = strtok(NULL, sep);
	if (aux)
		p.ambulanta = atoi(aux);
	
	return p;
}
Heap initializareHeap(int lungime)
{
	Heap heap;
	heap.lungime = lungime;
	heap.pacienti = (Pacient*)malloc(sizeof(Pacient) * lungime);
	heap.nrPacient = 0;
	return heap;
}

void filtreazaHeap(Heap heap, int pozNod)
{
	if (pozNod >= 0 && pozNod < heap.nrPacient)
	{
		int stg = 2 * pozNod + 1;
		int drp = 2 * pozNod + 2;
		int pozMax = pozNod;
		if (stg < heap.nrPacient && heap.pacienti[pozMax].grad < heap.pacienti[stg].grad)//trb si conditii de verificat sa nu mergem in partea ascunsa(daca stg sau drp e intre nrMasini si lungime atunci e pe o poz ascunsa, nu e bine asa
			pozMax = stg;//e esential sa pun stg<heap.nrMasini
		if (drp < heap.nrPacient && heap.pacienti[pozMax].grad < heap.pacienti[drp].grad)
			pozMax = drp;
		if (pozMax != pozNod)
		{
			Pacient aux= heap.pacienti[pozMax];
			heap.pacienti[pozMax] = heap.pacienti[pozNod];
			heap.pacienti[pozNod] = aux;
			//if (pozMax < ((heap.nrPacient - 1) / 2)) //am comentat pentru ca am observat ca fara linia aceasta functioneaza mai bine(se filtreaza si copiii in ordine)
				filtreazaHeap(heap, pozMax);
		}
	}
}
Heap citireHeap(const char* numef)
{
	Heap heap = initializareHeap(10);
	FILE* f = fopen(numef, "r");
	while (!feof(f))
	{
		heap.pacienti[heap.nrPacient] = citirePacientFisier(f);
		heap.nrPacient++;
	}
	fclose(f);
	for (int i = (heap.nrPacient - 1) / 2; i >= 0; i--)//parcurgem parintii de jos in sus
		filtreazaHeap(heap, i);

	return heap;
}
Pacient extrageHeap(Heap* heap)
{
	Pacient aux = heap->pacienti[0];
	heap->pacienti[0] = heap->pacienti[heap->nrPacient - 1];
	heap->pacienti[heap->nrPacient - 1] = aux;
	heap->nrPacient--;
	for (int i = (heap->nrPacient - 1) / 2; i >= 0; i--)
		filtreazaHeap(*heap, i);
	return aux;

}
void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.nrPacient; i++)
		afisarePacient(heap.pacienti[i]);
}
int main()
{
	Heap heap = citireHeap("pacient.txt");
	//afisareHeap(heap);
	Pacient	p1 = extrageHeap(&heap);
	Pacient p2 = extrageHeap(&heap);
	afisareHeap(heap);
}