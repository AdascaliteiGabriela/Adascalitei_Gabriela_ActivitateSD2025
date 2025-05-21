#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

//ARTICOL care contine A si G
struct Agentie
{
	char* numeAgentie;//atribut alocat dinamic
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
Agentia citesteAgentie() //functie citire tastatura
{
	Agentia a;
	char buffer[100];
	printf("\nIntrodu numele agentiei: ");
	fgets(buffer, sizeof(buffer), stdin);
	char* aux = strtok(buffer, "\n");
	a.numeAgentie = (char*)malloc(strlen(aux) + 1);
	if (a.numeAgentie != NULL)
		strcpy(a.numeAgentie,aux);
	else {
		printf("\nEroare la alocarea memoriei!\n");
		a.numeAgentie = NULL;
	}
	printf("\nIntrodu numarul de angajati: ");
	fgets(buffer, sizeof(buffer), stdin);
	a.numarAngajati=atoi(buffer);
	printf("\nIntrodu valoarea incasarilor: ");
	fgets(buffer, sizeof(buffer), stdin);
	a.valoareIncasari=atof(buffer);
	printf("\nIntrodu anul infiintarii: ");
	fgets(buffer, sizeof(buffer), stdin);
	a.anInfiintare=atoi(buffer);
	printf("\n");
	return a;

}
float incasariPerAngajat(Agentia a)//functie de calcul a mediei de incasari pe angajat
{
	if (a.numarAngajati > 0)
		return a.valoareIncasari / a.numarAngajati;
	else
		return -1;
}
void afisareAgentie(Agentia a)//functie de afisare obiect in consola
{
	printf("Nume agentie: %s\nNumar angajati: %d\nValoare incasari: %3.2f\nAn infiintare: %d\n\n", a.numeAgentie, a.numarAngajati, a.valoareIncasari, a.anInfiintare);
}
void modificaNumarAngajati(Agentia* a,int numarNou)//functie modificare numarAngajati
{
	a->numarAngajati = numarNou;
}


//VECTORI 

//functie de copiere
Agentia* copiereAgentiiMari(int numarMinimAngajati,Agentia* a, int nrAgentii, int*numarNou)
{
	(*numarNou) = 0;
	for (int i = 0; i < nrAgentii; i++)
		if (a[i].numarAngajati >= numarMinimAngajati)
			(*numarNou)++;
	Agentia* nou = (Agentia*)malloc((*numarNou)*sizeof(Agentia));
	int index = 0;
	for (int i = 0; i < nrAgentii; i++)
		if (a[i].numarAngajati >= numarMinimAngajati)
		{
			nou[index] = a[i]; index++;//shallow copy pentru ca nu vom modifica numele Agentiei in main sau alta parte.
		}
	return nou;

}
//functie de mutare vector in functie de incasari
Agentia* mutare(Agentia** a1, int* lungime1, int* lungime2,float incasariMin)
{
	
	(*lungime2) = 0;
	for (int i = 0; i < (*lungime1); i++)
		if ((*a1)[i].valoareIncasari >= incasariMin)
			(*lungime2)++;
	Agentia* agentie2=(Agentia*)malloc((*lungime2)*sizeof(Agentia));
	int index = 0;
	Agentia* aux = (Agentia*)malloc(((*lungime1) - (*lungime2)) * sizeof(Agentia));
	int index2 = 0;
	for(int i=0;i<(*lungime1);i++)
		if ((*a1)[i].valoareIncasari >= incasariMin)
		{
			agentie2[index] = (*a1)[i];
			index++;
		}
		else
		{
			aux[index2] = (*a1)[i];
			index2++;
		}
	free(*a1);
	*a1 = aux;
	*lungime1 = index2;
	return agentie2;

}
//functie concaternare vectori
Agentia* concaternare(Agentia* a1, Agentia* a2, int l1, int l2, int* lungime)
{
	(*lungime) = l1 + l2;
	Agentia* concat = (Agentia*)malloc((*lungime) * sizeof(Agentia));
	for (int i = 0; i < l1; i++)
		concat[i] = a1[i];
	for (int i = 0; i < l2; i++)
		concat[i + l1] = a2[i];
	return concat;
}

//functie de afisare vector
void AfisareVector(Agentia* vector, int dimensiune)
{
	for (int i = 0; i < dimensiune; i++)
		afisareAgentie(vector[i]);
}
int main()
{
	Agentia a1;
	a1 = initializare("Workpress", 12, 20000.45f, 2000);
	//afisareAgentie(a1);
	printf("In agentia 1 valoarea incasarilor per angajat este de: %6.2f\n", incasariPerAngajat(a1));

	//Agentia a2 = citesteAgentie();
	//afisareAgentie(a2);
	int lungime = 5;
	Agentia* agentii = (Agentia*)malloc(lungime * sizeof(Agentia));//vector alocat dinamic
	agentii[0] = initializare("TransAlpina", 6, 15800.45f, 2007);
	agentii[1] = initializare("TransMobil", 9, 14300.05f, 1999);
	agentii[2] = initializare("SoftTrans", 21, 444321.00f, 2017);
	agentii[3] = initializare("GetoMove", 3, 4000.00f, 2024);
	agentii[4] = a1;//shallow copy pentru ca nu vom modifica
	for (int i = 0; i < lungime; i++)
		afisareAgentie(agentii[i]);
	printf("\n\n\n Agentiile cu peste 10 angajati sunt: \n\n");
	int lungimeNoua = 0;
	Agentia* agentiiMari = copiereAgentiiMari(10, agentii, lungime, &lungimeNoua);
	AfisareVector(agentiiMari, lungimeNoua);

	//apel functie de mutare:
	int lungimeProfitMinim = 0;
	Agentia* agentiiProfitMinim = mutare(&agentii, &lungime, &lungimeProfitMinim, 0);
	printf("\n\nAgentiile cu profit minim 0\n\n");
	AfisareVector(agentiiProfitMinim,lungimeProfitMinim);
	printf("\n\nAgentiile cu profit sub 0\n\n");
	AfisareVector(agentii,lungime);
	return 0;
}