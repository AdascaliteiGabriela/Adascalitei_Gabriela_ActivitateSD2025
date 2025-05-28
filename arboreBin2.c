#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
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
typedef struct Nod Nod;

struct Nod {
	Nod* stg;
	Nod* drp;
	Chirias info;
};

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
Nod* adaugaArbore(Nod* cap, Chirias c)
{
	if (cap)
	{
		if (cap->info.codApartament > c.codApartament)//ATENTIE!! CONDITII
			cap->stg=adaugaArbore(cap->stg, c);
		else if (cap->info.codApartament < c.codApartament)
			cap->drp=adaugaArbore(cap->drp, c);
		else
		{
			if (cap->info.nume)
				free(cap->info.nume);
			cap->info.nume = (char*)malloc(strlen(c.nume) + 1);
			strcpy_s(cap->info.nume, strlen(c.nume) + 1, c.nume);
			cap->info.chirie = c.chirie;
			cap->info.codApartament = c.codApartament;
			cap->info.varsta = c.varsta;
		}
	}
	else
	{
		cap = (Nod*)malloc(sizeof(Nod));
		cap->stg = NULL;//ATENTIE!! initializareS
		cap->drp = NULL;
		cap->info.nume = (char*)malloc(strlen(c.nume) + 1);
		strcpy_s(cap->info.nume, strlen(c.nume) + 1, c.nume);
		cap->info.chirie = c.chirie;
		cap->info.codApartament = c.codApartament;
		cap->info.varsta = c.varsta;
	}
	return cap;
}
Nod* citireArbore(const char* numef)
{
	Nod* cap = NULL;
	FILE* f = fopen(numef, "r");
	while (!feof(f))
	{
		cap = adaugaArbore(cap, citireChirias(f));
	}
	fclose(f);
	return cap;
}
void afisareArbore(Nod* cap)
{
	if (cap) {//ATENTIE!! verificare
		afisareArbore(cap->stg);
		afisareChirias(cap->info);
		afisareArbore(cap->drp);
	}
}
int main()
{
	Nod* arbore = citireArbore("chiriasi.txt");
	afisareArbore(arbore);
}