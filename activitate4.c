#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Caiet
{
	int numarPagini;
	char* disciplina;
	char tip;//o litera care simbolizeaza daca e caiet dictando(D), matematica(M) sau cu foi albe(V)

};
struct Caiet initializareCaiet(int numarPagini, const char* disciplina, char tip)
{
	struct Caiet c;
	c.numarPagini = numarPagini;
	c.tip = tip;
	if (disciplina != NULL)
	{
		c.disciplina = (char*)malloc(strlen(disciplina) + 1);
		strcpy_s(c.disciplina, strlen(disciplina) + 1, disciplina);
	}
	else
	{
		c.disciplina = (char*)malloc(strlen("Necunoscut") + 1);
		strcpy_s(c.disciplina, strlen("Necunoscut") + 1, "Necunoscut");
	}
	return c;
}
struct Caiet citireCaietFisier(FILE*f)
{
	struct Caiet c;
	char buffer[100];
	fgets(buffer, 100, f);
	char separatori[3] = "/\n";
	c.numarPagini = atoi(strtok(buffer, separatori));
	char* aux;
	aux = strtok(NULL, separatori);
	c.disciplina = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c.disciplina, strlen(aux) + 1, aux);
	c.tip = strtok(NULL, separatori)[0];
		
	return c;

}
void afisareCaiet(struct Caiet c)
{
	printf("Disciplina: %s\nNumar pagini%i\nTip foaie: %c\n\n", c.disciplina, c.numarPagini, c.tip);
}
void dezalocareCaiet(struct Caiet* c)
{
	if(c!=NULL)
		free((*c).disciplina);
		//echivalent cu free(c->disciplina);
	
}
void caietInVector(struct Caiet** caiete, int* numarCaiete, struct Caiet caietNou)
{
	struct Caiet* aux=(struct Caiet*)malloc((*numarCaiete+1)*sizeof(struct Caiet));
	for (int i = 0; i < *numarCaiete; i++)
		aux[i] = (*caiete)[i];
	aux[*numarCaiete] = caietNou;
	free(*caiete);
	(*caiete) = aux;
	(*numarCaiete)++;
}
struct Caiet* citireVectorFisier(int* numar, FILE* f)
{
	struct Caiet* caiete = NULL;
	(*numar) = 0;
	while (!feof(f))
	{
		struct Caiet c1 = citireCaietFisier(f);
		caietInVector(&caiete, &(*numar), c1);
	}
	return caiete;

}
void afisareVector(struct Caiet* c, int numar)
{
	for (int i = 0; i < numar; i++)
		afisareCaiet(c[i]);
}
int main()
{
	struct Caiet c1;
	FILE* f = fopen("caiete.txt", "r");
	c1=citireCaietFisier(f);
	afisareCaiet(c1);
	dezalocareCaiet(&c1);
	struct Caiete* c = NULL;
	int numar = 0;
	c=citireVectorFisier(&numar, f);
	afisareVector(c, numar);
	return 0;
}