#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina; //in loc sa scriu struct StructuraMasina am definit un alias Masina 

void afisareMasina(Masina masina) {
	printf("ID masina: %d\nNumar usi: %d \nPretul: %5.2f \nModelul: %s \nNume sofer: %s \nSerie: %c\n\n", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	for (int i = 0; i < nrMasini; i++)
		afisareMasina(masini[i]);

}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	Masina* copie = (Masina*)malloc(((*nrMasini) + 1) * sizeof(Masina));
	for (int i = 0; i < (*nrMasini); i++)
	{
		copie[i] = (*masini)[i];//fac shallow copy si nu modific pointerii ca sa fie legaturile bune sau daca fac deep copy, trebuie intai sterse inainte de realocare
	}
	copie[(*nrMasini)] = masinaNoua;
	free((*masini));//free e o functie
	(*masini) = copie;//am mutat pointer ul la adresa lui copie

}

Masina citireMasinaFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	fgets(buffer, 100, file);
	Masina m1;
	aux= strtok(buffer, sep);
	m1.id = atoi(aux);//cast din codul ASCII la int prin functia atoi()
	m1.nrUsi = atoi(strtok(NULL, sep));//ca sa se uite/sa continue cautarea de unde a ramas 
	m1.pret = atof(strtok(NULL, sep));//atof e importat doar in stdlib
	//trb citit intr un buffer, apoi alocam spatiu pentru char* si copiem, altfel s ar pierde valorile cum tot ce citim aici e salvat local in stack-ul functiei si nu in heap
	aux = strtok(NULL, sep);
	m1.model = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
	m1.serie = strtok(NULL, sep)[0];//dereferentiere sau indexare de 0 ca sa luam doar un caracter(primul)
	return m1;




}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
}

int main() 
{
	//in masini.txt despartitorul e virgula pentru a putea citi denumiri cu spatiu
	return 0;
}