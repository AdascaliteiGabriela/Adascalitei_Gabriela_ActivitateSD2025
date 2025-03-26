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
struct Nod
{
	struct Caiet info;
	struct Nod* urmator;//adresa la urmatorul nod pt a continua lista
};
typedef struct Nod Nod;
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
void dezalocareVector(struct Caiet** c, int* numar)
{
	for (int i = 0; i < (*numar); i++)
		dezalocareCaiet( & (*c)[i]);
	free(*c);
	(*c) = NULL;
	(*numar) = 0;
}


//PARTEA CU LISTA SIMPLU INLANTUITA
void afisareListaCaiete(Nod* cap)//ne trebuie primul nod neaparat
{
	while (cap != NULL)
	{
		afisareCaiet(cap->info);//am dereferentiat pt ca aveam adresa, dar eu vreau efectiv obiectul pentru a apela functia
		cap = cap->urmator;//trec la nodul urmator ca sa continui cu parcurgerea listei
	}

}
void adaugareCaietFinal(Nod** cap, struct Caiet c)//asa identific lista,iar cap e transmis prin dublu pointer ca sa putem modifica daca este cazul(daca initial e null si adaug primul element->cap de modifica)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->urmator = NULL;//pt ca inseram la final, deci e ultimul
	if ((*cap))
	{
		//daca parcurg direct cu cap se modifica si nu ma mai pot intoarce la inceput->am pierdut elementele de dinainte de ultimul
		//ne trebuie un nod nou
		Nod* p = (*cap);
		while (p->urmator != NULL)//ma deplasez pana ajung la final
			p = p->urmator;
		p->urmator = nou;
	}
	else
		*cap = nou;
}
void adaugareCaietInceput(Nod** cap, struct Caiet c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->urmator = (*cap);
	(*cap) = nou;
}
Nod* citireListaFisier(const char* numef)//vom returna nodul cap
{
	Nod* cap = NULL;
	FILE* f = fopen(numef, "r");
	if (f)
	{
		while (!feof(f))
			//folosim inserare la sfarsit ca sa le am in ordine
			adaugareCaietFinal(&cap, citireCaietFisier(f));
		fclose(f);
	}
	return cap;
}


void dezalocareLista(Nod** cap)
{
	while (*cap)
	{
		Nod* p=(*cap);
		(*cap) = (*cap)->urmator;
		if (p->info.disciplina != NULL)
			dezalocareCaiet(&(p->info));
		free(p);
	}

}
float calculeazaPaginiMedii(Nod* cap)
{
	int numar = 0;
	float suma = 0;
	while (cap)
	{
		numar++;
		suma += (float)cap->info.numarPagini;
		cap = cap->urmator;
	}
	if (numar > 0)
		return suma / numar;
	else
		return 0;
}
int numarPaginiAnumitTip(Nod* cap, char c)
{
	int numar = 0;
	while (cap)
	{
		if (cap->info.tip == c)
			numar += cap->info.numarPagini;
		cap = cap->urmator;
	}
	return numar;
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

	//listele nu ocupa o zona de mem contigua
	//din acest motiv trb sa retinem acele adrese pentru a sti unde sa cautam elementele
	//vom retine adresele in cate un nod care va contine informatia utila si adresa urmatorului element
	//adresa aceea e de forma pointer la nodul urmator adica la locatia unde se gaseste stocata urmatoarea informatie
	//ultimul nod va contine null in loc de adresa la urmatorul nod(nu exista urmatorul)
	//trebuie sa stim care e primul nod(capul) adica de unde incepe lista pentru a o parcurge
	//DECI ne trebuie o structura nod pentru a stoca toate informatiile

	Nod* cap = citireListaFisier("caiete.txt");
	afisareListaCaiete(cap);


	printf("\n\n\nNumarul mediu de pagini este: %3.2f\n", calculeazaPaginiMedii(cap));

	printf("\n\nNumarul de pagini de matematica este: %d", numarPaginiAnumitTip(cap, 'M'));
	dezalocareLista(&cap);

	dezalocareVector(&c, &numar);
	return 0;
}