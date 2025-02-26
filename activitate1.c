#include<stdio.h>
#include<stdlib.h>
struct Carte
{
	int nrPagini;
	char* titlu;
	float pret;
	char cota;
};

struct Carte initializare(int nrPagini, const char* titlu, float pret, char cota)
{
	struct Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.cota = cota;
	c.titlu = (char*)malloc((strlen(titlu) + 1) * sizeof(char));
	strcpy_s(c.titlu,strlen(titlu)+1, titlu);
	return c;
}

void afisare(struct Carte c)
{
	printf("Titlul: %s, numar pagini: %d, pret: 4.2%f, cota: %c\n", c.titlu, c.nrPagini, c.pret, c.cota);
}

void modificarePret(struct Carte* c,float pretNou)
{
	if (pretNou > 0)
		c->pret = pretNou;
}
void afisarePret(struct Carte c)
{
	printf("Pretul este: %4.2f\n", c.pret);
}

void dezalocare(struct Carte* c)
{
	free(c->titlu);
	c->titlu = NULL;
}

int main()
{
	struct Carte c1;
	c1 = initializare(100, "Morometii", 24.99, 'B');
	afisare(c1);
	modificarePret(&c1, 34.50);
	afisarePret(c1);
	return 0;
}