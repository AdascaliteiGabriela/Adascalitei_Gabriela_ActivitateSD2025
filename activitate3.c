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

void adaugaCeaiInVector(Ceai** ceaiuri, int* numarCeaiuri, Ceai ceaiNou)
{
	Ceai* copie = (Ceai*)malloc(((*numarCeaiuri) + 1) * sizeof(Ceai));//creez un vector nou si aloc spatiu pentru inca un ceai
	for (int i = 0; i < (*numarCeaiuri); i++)
	{
		copie[i] = (*ceaiuri)[i];
	}
	copie[*numarCeaiuri] = ceaiNou;
	free(*ceaiuri);
	(*ceaiuri) = copie;	
	(*numarCeaiuri)++;
	
	

}
Ceai* citireVectorFisier(int* numarCeaiuri,char*numeFisier)
{
	Ceai* ceaiuri=NULL;
	FILE*f=fopen(numeFisier, "r");
	(*numarCeaiuri) = 0;
	while (!feof(f))
	{
		Ceai c1 = citireCeaiDinFisier(f);
		adaugaCeaiInVector(&ceaiuri, &(*numarCeaiuri), c1);

	}
	return ceaiuri;
}

void afisareCeai(Ceai c1)
{
	printf("Nume ceai: %s\nPret: %3.2f\nCantitate: %i\nTara de provenienta: %s\n\n", c1.nume, c1.pret, c1.cantitate, c1.taraProvenienta);
}
void afisareVectorCeai(Ceai* c, int numar)
{
	for (int i = 0; i < numar; i++)
		afisareCeai(c[i]);
}
void dezalocareVectorCeai(Ceai** ceaiuri,int* numarCeaiuri)
{
	for (int i = 0; i < *numarCeaiuri; i++)
	{
		free((*ceaiuri)[i].nume);
		free((*ceaiuri)[i].taraProvenienta);
		free(*ceaiuri);
		*ceaiuri = NULL;
		*numarCeaiuri = 0;
	}
}
void dezalocareCeai(Ceai* c)
{
	if ((c != NULL)) {
		free(c->nume);
		free(c->taraProvenienta);

		c->nume = NULL;
		c->taraProvenienta = NULL;
	}
}
int main()
{
	Ceai c1;
	FILE* f = fopen("ceaiuri.txt", "r");

	c1 = citireCeaiDinFisier(f);
	afisareCeai(c1);
	
	int numar = 0;
	Ceai* c=NULL;
	for (int i = 0; i < 5; i++)
	{
		adaugaCeaiInVector(&c, &numar, c1);
		c1 = citireCeaiDinFisier(f);
	}
	dezalocareVectorCeai(&c, &numar);
	for (int i = 0; i < numar; i++)
		afisareCeai(c[i]);
	printf("\n\nAm citit %d ceaiuri pana acum.\n\n\n", numar);
	Ceai* cc = NULL;
	numar = 0;
	dezalocareCeai(&c1);
	cc=citireVectorFisier(&numar, "ceaiuri.txt");
	afisareVectorCeai(cc, numar);
	printf("\n\nAm citit %d ceaiuri pana acum.\n\n\n", numar);
	dezalocareVectorCeai(&cc, &numar);
	return 0;
}