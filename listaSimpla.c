//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Tricou
//{
//	char* producator;
//	char* material;
//	int marime;
//	float pret;
//
//};
//typedef struct Tricou Tricou;
//struct Nod {
//	struct Nod* urm;
//	Tricou info;
//
//};
//typedef struct Nod Nod;
//Tricou citireFisierTricou(FILE* f)
//{
//	Tricou t;
//	char buffer[100];
//	char sep[3] = ",\n";
//	char* aux;
//	fgets(buffer, 100, f);
//	aux = strtok(buffer, sep);
//	t.producator = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(t.producator, strlen(aux) + 1, aux);
//	aux = strtok(NULL, sep);
//	t.material = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(t.material, strlen(aux) + 1, aux);
//	t.marime = atoi(strtok(NULL, sep));
//	t.pret = atof(strtok(NULL, sep));
//
//	return t;
//
//}
//void afisareTricou(Tricou t)
//{
//	printf("Producator: %s\n", t.producator);
//	printf("Material: %s\n", t.material);
//	printf("Marime: %d\n", t.marime);
//	printf("Pret: %.2f\n", t.pret);
//	printf("\n");
//}
//void adaugaNodListaFinal(Nod** cap, Tricou t)
//{
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = t;
//	nou->urm = NULL;
//	if ((*cap) == NULL)
//	{
//		(*cap) = nou;
//	}
//	else
//	{
//		Nod* aux = (*cap);
//		while (aux->urm)
//		{
//			aux = aux->urm;
//		}
//		aux->urm = nou;
//	}
//}
//Nod* citireLista(const char* numeF)
//{
//	FILE* f = fopen(numeF, "r");
//	Nod* cap = NULL;
//	while (!feof(f))
//	{
//		adaugaNodListaFinal(&cap, citireFisierTricou(f));
//	}
//
//	return cap;
//}
//void afisareLista(Nod* cap)
//{
//	while (cap)
//	{
//		afisareTricou(cap->info);
//		cap = cap->urm;
//	}
//}
//
//int main()
//{
//	Nod* cap = citireLista("tricouri.txt");
//	afisareLista(cap);
//	return 0;
//}