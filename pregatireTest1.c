#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
struct Monitor {
	int codMonitor;
	char* producator;
	float diagonala;
	int nrPorturi;

};

typedef struct Monitor Monitor;

struct Nod {
	struct Nod* urm;
	Monitor info;
 };
typedef struct Nod Nod;

Monitor initializare(int codMonitor, const char* producator, float diagonala, int nrPorturi)
{
	Monitor m;
	m.codMonitor = codMonitor;
	m.diagonala = diagonala;
	m.nrPorturi = nrPorturi;
	m.producator = (char*)malloc(strlen(producator) + 1);
	strcpy_s(m.producator, strlen(producator) + 1, producator);

	return m;
}
Monitor citireFisier(FILE* f)
{
	Monitor m;
	char buffer[100];
	char* aux;
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	m.codMonitor = atoi(strtok(buffer, sep));
	aux = strtok(NULL, sep);
	m.producator = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m.producator, strlen(aux) + 1, aux);
	m.diagonala = atof(strtok(NULL, sep));
	m.nrPorturi = atoi(strtok(NULL, sep));
	

	return m;
}

void adaugareInLista(Nod** cap, Monitor m)
{
	Nod* nou=(Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->urm = NULL;
	if ((*cap) == NULL)
		(*cap) = nou;
	else
	{
		Nod* aux = (*cap);
		while (aux->urm)//ne oprim pe ultimul
			aux = aux->urm;
		//am ajuns la ultimul nod din lista aici
		aux->urm = nou;
	}

}
Nod* citireListaFisier(const char* numef)
{
	FILE* f = fopen(numef, "r");
	Monitor m;
	Nod* cap = NULL;
	while (!feof(f))
	{
		m = citireFisier(f);
		adaugareInLista(&cap, m);
	}
	return cap;
}
void afisareMonitor(Monitor m)
{
	printf("ID monitor: %d\n", m.codMonitor);
	printf("Producator: %s\n", m.producator);
	printf("Diagonala: %.3f\n", m.diagonala);
	printf("Numar de porturi: %i\n", m.nrPorturi);
	printf("\n\n");
}
void afisareLista(Nod* cap)
{
	while (cap)
	{
		afisareMonitor(cap->info);
		cap = cap->urm;
	}
}
void sterereLista(int cod,Nod**nod)
{
	
	while ((*nod) && (*nod)->info.codMonitor == cod)
	{
		Nod* aux = (*nod);
		(*nod) = aux->urm;
		if (aux->info.producator)
			free(aux->info.producator);
		free(aux);
	}
	if(*nod)
	{
		Nod* p = (*nod);
		while (p) {
			while (p->urm && p->urm->info.codMonitor != cod) {
				p = p->urm;
			}
			if (p->urm) {
				Nod* aux = p->urm;
				p->urm = aux->urm;
				if (aux->info.producator) {
					free(aux->info.producator);
				}
				free(aux);
			}
			else {
				p = NULL;
			}
		}

		
			
	}
}
void dezalocareMonitor(Monitor m)
{
	if (m.producator != NULL)
		free(m.producator);
}
void dezalocareListaMonitoare(Nod**cap) {
	while ((*cap != NULL))
	{
		Nod* aux = (*cap);
		*cap = (*cap)->urm;
		free(aux->info.producator);
		free(aux);
	}
	
}
int main()
{
	Monitor m[5];
	m[0] = initializare(4, "Sony", 44.2, 4);
	m[1] = initializare(4, "Samsung", 23.5, 2);
	m[2] = initializare(2, "Huawei", 34.5, 4);
	m[3] = initializare(4, "Lenovo", 45, 5);
	m[4] = initializare(6, "Sony", 52.9, 3);
	Nod* cap = NULL;
	for (int i = 0; i < 5; i++)
	{
		adaugareInLista((&cap), m[i]);
	}
	//afisareLista(cap);
	sterereLista(4, &cap);
	//afisareLista(cap);
	dezalocareListaMonitoare(&cap);
	//afisareLista(cap);
	
	Nod* cap2 = citireListaFisier("monitoare.txt");
	afisareLista(cap2);


}