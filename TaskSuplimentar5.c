#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct Nod Nod;


struct Nod {
	Masina info;
	Nod* urm;
};
Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->urm;
	}
	
}

void adaugaMasinaInLista(Nod**cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;

	nou->urm = NULL;
	if ((*cap) == NULL)
	{
		*cap = nou;
	}
	else
	{
		Nod* p = *cap;
		while (p->urm)
		{
			p = p->urm;
		}
		p->urm = nou;

	}
}

void adaugaLaInceputInLista(Nod**cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->urm = *cap;
	*cap = nou;

	
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier,"r");
	Nod* lista = NULL;
	while (!feof(f))
	{
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;

}

void dezalocareListaMasini(Nod**cap) {
	while ((*cap != NULL))
	{
		Nod* aux = (*cap);
		*cap = (*cap)->urm;
		free(aux->info.model);
		free(aux->info.numeSofer);
		free(aux);
	}
	
}

float calculeazaPretMediu(Nod*lista) {
	if (!lista)
		return 0;
	float suma = 0;
	int numar = 0;
	while (lista)
	{
		suma += lista->info.pret;
		numar++;
		lista = lista->urm;

	}
	return  suma/numar;
}



float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	float suma = 0;
	while (lista)
	{
		if (strcmp(lista->info.numeSofer, numeSofer) == 0)
		{
			suma += lista->info.pret;
		}
		lista = lista->urm;
		
	}
	return suma;
}
char* getCeaMaiScumpaMasina(Nod* lista)
{
	float pretMax = 0;
	char* modelScump=NULL;
	while (lista)
	{
		if (lista->info.pret > pretMax)
		{
			pretMax = lista->info.pret; modelScump = lista->info.model;
			
		}
		lista = lista->urm;
		if (pretMax > 0)
		{
			char* nou = malloc(strlen(modelScump) + 1);
			strcpy_s(nou, strlen(modelScump) + 1, modelScump);
			return nou;
		}
	}
	return NULL;
}

//functia care calculeaza lungimea listei
int lungimeLista(Nod* cap)
{
	int lungime = 0;
	while (cap)
	{
		lungime++;
		cap = cap->urm;
	}
	return lungime;
}

//functie care sterge nod de la pozitia index
void stergereNod(Nod** cap, int index)
{
	if (index == 0)//daca pozitia de sters e fix 0, adica stergwm capul listei
	{
		Nod* aux = *cap;
		*cap = (*cap)->urm;
		free(aux->info.model);
		free(aux->info.numeSofer);
		free(aux);
		return;
	}
	Nod* aux = (*cap);
	int nrNoduri = lungimeLista(*cap);
	if (index >= nrNoduri)//daca pozitia nu exista
		return;
	int poz = 0;
	while (poz<index-1)//vreau sa ajung la nodul de dinainte
	{
		poz++;
		aux = aux->urm;
	}
	if (aux->urm)//daca exista nodul de pe pozitia de sters
	{
		Nod* sters = aux->urm;
		if (aux->urm->urm)
			aux->urm = aux->urm->urm;
		else
			aux->urm = NULL;
		free(sters->info.model);
		free(sters->info.numeSofer);
		free(sters);
		sters = NULL;
	}
		
	

}

//adaugare lista crescator
void adaugaMasinaCrescator(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;

	nou->urm = NULL;
	if ((*cap) == NULL || masinaNoua.nrUsi <= (*cap)->info.nrUsi)
	{
		nou->urm = *cap;
		*cap = nou;
	}
	else
	{
		Nod* p = *cap;
		while (p->urm && masinaNoua.nrUsi> p->urm->info.nrUsi)
		{
			p = p->urm;
		}
		nou->urm = p->urm;
		p->urm = nou;

	}
}
//citire lista crescator
Nod* citireListaCrescatorFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f))
	{
		adaugaMasinaCrescator(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;

}
Masina* masiniCuAnumitNrUsi(Nod* cap, int*numar, int nrUsi)
{
	(*numar) = 0;
	Nod* aux = cap;
	while (aux)
	{
		if (aux->info.nrUsi == nrUsi)
			(*numar)++;
		aux = aux->urm;

	}
	if ((*numar) == 0)
		return NULL;
	Masina* vector = (Masina*)malloc(sizeof(Masina) * (*numar));
	int poz = 0;
	while (cap)
	{
		if (cap->info.nrUsi == nrUsi)
		{
			vector[poz].id = cap->info.id;
			vector[poz].nrUsi = cap->info.nrUsi;
			vector[poz].pret = cap->info.pret;
			vector[poz].serie = cap->info.serie;
			vector[poz].model = (char*)malloc(strlen(cap->info.model) + 1);
			strcpy_s(vector[poz].model, strlen(cap->info.model) + 1, cap->info.model);
			vector[poz].numeSofer = (char*)malloc(strlen(cap->info.numeSofer) + 1);
			strcpy_s(vector[poz].numeSofer, strlen(cap->info.numeSofer) + 1, cap->info.numeSofer);
			poz++;
		}
		cap = cap->urm;
	}
	return vector;
}
Masina* transformareVector(Nod* cap, int*numar)
{
	(*numar) = 0;
	Nod* aux = cap;
	while (aux)
	{
		(*numar)++;
		aux = aux->urm;
	}
	if ((*numar) == 0)
		return NULL;
	Masina* vector = (Masina*)malloc(sizeof(Masina) * (*numar));
	int poz = 0;
	while (cap)
	{
		vector[poz].id = cap->info.id;
		vector[poz].nrUsi = cap->info.nrUsi;
		vector[poz].pret = cap->info.pret;
		vector[poz].serie = cap->info.serie;
		vector[poz].model = (char*)malloc(strlen(cap->info.model) + 1);
		strcpy_s(vector[poz].model, strlen(cap->info.model) + 1, cap->info.model);
		vector[poz].numeSofer = (char*)malloc(strlen(cap->info.numeSofer) + 1);
		strcpy_s(vector[poz].numeSofer, strlen(cap->info.numeSofer) + 1, cap->info.numeSofer);
		poz++;
		
		cap = cap->urm;
	}
	return vector;
}
Nod* interschimbarePozitii(Nod* cap, int poz1, int poz2)
{
	int nrElemente = lungimeLista(cap);
	if (poz1 >= nrElemente || poz2 >= nrElemente)
		return cap;//daca pozitiile nu exista returnam aceeasi lista
	else
	{
		
		int nrElemente = 0;
		Masina* vectorInitial = transformareVector(cap, &nrElemente);
		Masina aux = vectorInitial[poz1];
		vectorInitial[poz1] = vectorInitial[poz2];
		vectorInitial[poz2] = aux;
		Nod* listaNoua = NULL;
		for (int i = 0; i < nrElemente; i++)
			adaugaMasinaInLista(&listaNoua, vectorInitial[i]);
		dezalocareListaMasini(&cap);
		free(vectorInitial);
		return listaNoua;
	}
	
}
int main() {
	
	Nod* crescator = citireListaCrescatorFisier("masini.txt");
	afisareListaMasini(crescator);


	int nrEl = 0;
	Masina* vector = masiniCuAnumitNrUsi(crescator,&nrEl,3);
	printf("\n\n\nMasinile cu 3 usi din vector sunt: \n\n");
	for (int i = 0; i < nrEl; i++)
		afisareMasina(vector[i]);
	Nod* nou = interschimbarePozitii(crescator, 2, 5);
	printf("\n\n\nLista noua cu pozitiile interschimbate: \n\n");
	afisareListaMasini(nou);

	return 0;
}