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
struct Caiet citireCaietFisier(char* numef, struct Caiet* c)
{
	FILE* f = fopen(numef, "r");
	
	

		char buffer[100];
		fgets(buffer, 100, f);
		char separatori[3] = "/\n";
		
		
		(*c).numarPagini = atoi(strtok(buffer, separatori));
		char* aux;
		aux = strtok(NULL, separatori);
		(*c).disciplina = (char*)malloc(strlen(aux) + 1);
		strcpy_s((*c).disciplina, strlen(aux) + 1, aux);
		(*c).tip = strtok(NULL, separatori)[0];
		
	

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
int main()
{
	struct Caiet c1;
	citireCaietFisier("caiete.txt", &c1);
	afisareCaiet(c1);
	dezalocareCaiet(&c1);
	return 0;
}