#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Ceai
{
	char* nume;
	float pret;
	int cantitate;
	char* taraProvenienta;
};

typedef struct Ceai Ceai;
Ceai citireCeaiDinFisier(FILE* f)
{
	char buffer[100];//aici citesc din fisier intai
	
	fgets(buffer, 100, f);
	char sep[3] = ",\n";//aici am pus separatorii ca sa pot delimita atributele de pe fiecare rand
	Ceai c1;

	char* aux;
	aux = strtok(buffer, sep);
	c1.nume = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c1.nume, strlen(aux) + 1, aux);
	c1.pret = atof(strtok(NULL, sep));
	c1.cantitate = atoi(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	c1.taraProvenienta = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c1.taraProvenienta, strlen(aux) + 1, aux);



	return c1;
}

void afisareCeai(Ceai c1)
{
	printf("Nume ceai: %s\nPret: %3.2f\nCantitate: %i\nTara de provenienta: %s\n\n", c1.nume, c1.pret, c1.cantitate, c1.taraProvenienta);
}

int main()
{
	Ceai c1;
	FILE* f = fopen("ceaiuri.txt", "r");

	for (int i = 0; i < 5; i++) {
		c1 = citireCeaiDinFisier(f);
		afisareCeai(c1);
	}

	return 0;
}