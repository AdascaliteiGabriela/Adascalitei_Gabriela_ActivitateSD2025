//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct Animal
//{
//	int codIdentificare;
//	char* specie;
//	int varsta;
//	float greutate;
//
//};
//typedef struct Animal Animal;
//struct NodDublu
//{
//	struct NodDublu* pre;
//	struct NodDublu* urm;
//	Animal info;
//};
//typedef struct NodDublu NodDublu;
//struct Lista
//{
//	NodDublu* prim;
//	NodDublu* ultim;
//};
//typedef struct Lista Lista;
//Animal citireAnimlFisier(FILE* f)
//{
//	Animal a;
//	char buffer[100];
//	char* aux;
//	char sep[3] = ",\n";
//	fgets(buffer, 100, f);
//	a.codIdentificare = atoi(strtok(buffer, sep));
//	aux = strtok(NULL, sep);
//	a.specie = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(a.specie, strlen(aux) + 1, aux);
//	a.varsta = atoi(strtok(NULL, sep));
//	a.greutate = atof(strtok(NULL, sep));
//
//	return a;
//}
//void afisareAnimal(Animal a)
//{
//	printf("Cod animal: %d\n", a.codIdentificare);
//	printf("Specie: %s\n", a.specie);
//	printf("Varsta: %d\n", a.varsta);
//	printf("Greutate: %.2f\n", a.greutate);
//	printf("\n");
//}
//
//void adaugaListaFinal(Lista* l, Animal a)
//{
//	NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
//	nou->info = a;
//	nou->urm = NULL;
//	nou->pre = l->ultim;
//	if (l->ultim == NULL)
//	{
//		l->prim = nou;
//	}
//	else
//	{
//		l->ultim->urm = nou;
//	}
//	l->ultim = nou;
//}
//Lista citireLista(const char* numef)
//{
//	Lista l;
//	l.prim = NULL;
//	l.ultim = NULL;
//	FILE* f;
//	f = fopen(numef, "r");
//	while (!feof(f))
//	{
//		adaugaListaFinal(&l, citireAnimlFisier(f));
//	}
//	return l;
//}
//afisareLista(Lista l)
//{
//	NodDublu* aux = l.prim;
//	while (aux)
//	{
//		afisareAnimal(aux->info);
//		aux = aux->urm;
//
//	}
//}
//int main()
//{
//	Lista l = citireLista("animale.txt");
//	afisareLista(l);
//	
//	return 0;
//}