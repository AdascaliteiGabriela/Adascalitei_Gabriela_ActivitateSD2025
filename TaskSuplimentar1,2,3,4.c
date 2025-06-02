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


//FISIERE

//functie de citire obiect din fisier
Agentia citireAgentieFisier(FILE* f)
{
	Agentia a;
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	char* aux;
	aux = strtok(buffer, sep);
	if (aux)
	{
		a.numeAgentie = (char*)malloc(strlen(aux) + 1);
		strcpy_s(a.numeAgentie, strlen(aux) + 1, aux);

	}
	else
		a.numeAgentie = NULL;
	aux = strtok(NULL, sep);
	if(aux)
		a.numarAngajati = atoi(aux);
	aux = strtok(NULL, sep);
	if (aux)
		a.anInfiintare = atoi(aux);
	aux = strtok(NULL, sep);
	if (aux)
		a.valoareIncasari = atof(aux);
	
	return a;
}

//functie citire numarElemente
int numarElemente(const char* numef)
{
	FILE* f = fopen(numef, "r");
	if (!f) return 0;

	int nrAgentii = 0;
	char buffer[100];
	while (fgets(buffer, 100, f))
		nrAgentii++;

	fclose(f);
	return nrAgentii;
}

//functie de citire vector
Agentia* citireVectorFisier(const char* numef, int * dim)
{
	(*dim) = numarElemente(numef);
	if (*dim == 0) return NULL;
	Agentia* agentii = (Agentia*)malloc(sizeof(Agentia) * (*dim));
	FILE* f = fopen(numef, "r");
	for(int i=0;i<(*dim);i++)
	{
		agentii[i] = citireAgentieFisier(f);

	}
	fclose(f);
	return agentii;
}
//salvare obiect fisier
void salvareAgentieInFisier(FILE* f, Agentia a)
{
	if (f && a.numeAgentie != NULL)
	{
		fprintf(f, "%s,%d,%d,%.2f\n",a.numeAgentie,a.numarAngajati,a.anInfiintare,a.valoareIncasari);
	}
}
//salvare vector fisier
void salvareVectorInFisier(const char* numefisier, Agentia* vector, int dim)
{
	FILE* f = fopen(numefisier, "w");
	if (!f)
	{
		printf("Nu s-a pupt deschide fisierul :( \n");
		return;
	}

	for (int i = 0; i < dim; i++)
	{
		salvareAgentieInFisier(f, vector[i]);
	}

	fclose(f);
}
//sortare vector
Agentia* sortareCrescatorAngajati(Agentia* v, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (v[i].numarAngajati > v[j].numarAngajati) {
				Agentia aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

//construire matrice
Agentia** matrice(Agentia* vector, int nrElemente, int* nrLinii, int* nrColoane)
{
	//voi grupa pe 2 linii in functie de nr angajati
	(*nrLinii) = 2;
	(*nrColoane) = nrElemente / (*nrLinii);
	Agentia** matrice = (Agentia**)malloc((*nrLinii) * sizeof(Agentia*));//am alocat un vector de pointeri la linii
	for (int i = 0; i < *nrLinii; i++) {
		matrice[i] = (Agentia*)malloc((*nrColoane) * sizeof(Agentia));
	}
	for (int i = 0; i < (*nrColoane); i++)
	{
		//matrice[0][i] = vector[i];
		matrice[0][i].numarAngajati = vector[i].numarAngajati;
		matrice[0][i].valoareIncasari = vector[i].valoareIncasari;
		matrice[0][i].anInfiintare = vector[i].anInfiintare;
		matrice[0][i].numeAgentie = (char*)malloc(strlen(vector[i].numeAgentie)+1);
		strcpy_s(matrice[0][i].numeAgentie, strlen(vector[i].numeAgentie)+1, vector[i].numeAgentie);
	}
	for (int i = 0; i < (*nrColoane); i++)
	{
		//matrice[1][i] = vector[i+(*nrColoane)];
		matrice[1][i].numarAngajati = vector[i + (*nrColoane)].numarAngajati;
		matrice[1][i].valoareIncasari = vector[i + (*nrColoane)].valoareIncasari;
		matrice[1][i].anInfiintare = vector[i + (*nrColoane)].anInfiintare;
		matrice[1][i].numeAgentie = (char*)malloc(strlen(vector[i + (*nrColoane)].numeAgentie) + 1);
		strcpy_s(matrice[1][i].numeAgentie, strlen(vector[i + (*nrColoane)].numeAgentie) + 1, vector[i + (*nrColoane)].numeAgentie);
	}
	return matrice;
}
void afisareMatrice(Agentia** matrice, int nrLinii, int nrCol)
{
	for (int i = 0; i < nrLinii; i++)
		for (int j = 0; j < nrCol; j++)
			afisareAgentie(matrice[i][j]);
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
	Agentia* agentiiProfitMinim = mutare(&agentii, &lungime, &lungimeProfitMinim, 4050);
	printf("\n\nAgentiile cu profit minim 4050\n\n");
	AfisareVector(agentiiProfitMinim,lungimeProfitMinim);
	printf("\n\nAgentiile cu profit sub 4050\n\n");
	AfisareVector(agentii,lungime);
	printf("\n\n\n\n\nCitire din fisier: \n\n");
	int dimFisier = 0;
	Agentia* agentiiFisier = citireVectorFisier("agentii.txt", &dimFisier);
	for (int i = 0; i < dimFisier; i++)
		afisareAgentie(agentiiFisier[i]);

	printf("\n\n\nAm salvat vectorul in fisierul agentii2.txt\n\n\n");
	salvareVectorInFisier("agentii2.txt",agentiiFisier, dimFisier);
	agentii = sortareCrescatorAngajati(agentii, lungime);
	int linii = 0;
	int coloane = 0;
	Agentia** matr = matrice(agentii, lungime, &linii, &coloane);
	afisareMatrice(matr, linii, coloane);
	return 0;
}