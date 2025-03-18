#include <stdio.h>
#include<stdlib.h>
#include <string.h>
struct Agentie
{
	char* numeAgentie;
	int numarAngajati;
	float valoareIncasari;
	int anInfiintare;
};
typedef struct Agentie Agentia;

Agentia initializare(const char* numeAgentie, int numarAngajati, float valoareIncasari, int anInfiintare)
{
	Agentia a;
	if (numarAngajati >= 0)
		a.numarAngajati = numarAngajati;
	else
		a.numarAngajati = 0;
	if (valoareIncasari >= 0)
		a.valoareIncasari = valoareIncasari;
	else
		a.valoareIncasari = 0;
	a.anInfiintare = anInfiintare;
	
	if (numeAgentie != NULL)
	{
		a.numeAgentie = (char*)malloc((strlen(numeAgentie) + 1) * sizeof(char));
		strcpy_s(a.numeAgentie, strlen(numeAgentie) + 1, numeAgentie);
	}
	else
	{
		a.numeAgentie = NULL;
	}
	return a;
}
float incasariPerAngajat(Agentia a)
{
	if (a.numarAngajati > 0)
		return a.valoareIncasari / a.numarAngajati;
	else
		return -1;
}
void afisareAgentie(Agentia a)
{
	printf("Nume agentie: %s\nNumar angajati: %d\nValoare incasari: %3.2f\nAn infiintare: %d\n\n", a.numeAgentie, a.numarAngajati, a.valoareIncasari, a.anInfiintare);
}
void modificaNumarAngajati(Agentia* a,int numarNou)
{
	a->numarAngajati = numarNou;
}
int main()
{
	Agentia a1;
	a1 = initializare("Workpress", 12, 20000.45f, 2000);
	afisareAgentie(a1);
	printf("In agentia 1 valoarea incasarilor per angajat este de: %6.2f", incasariPerAngajat(a1));
	return 0;
}