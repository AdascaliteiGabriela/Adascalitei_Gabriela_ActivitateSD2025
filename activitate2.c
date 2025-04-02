#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

struct Salariat {
	int id;
	float salariu;
	char* nume;
	char specializare;
	int varsta;

};

struct Salariat initializare(int id, float salariul, const char* nume, char specializare, int varsta)
{
	struct Salariat s;
	s.id = id;
	s.salariu = salariul;
	s.specializare = specializare;
	s.varsta = varsta;
	if (nume == NULL)
		s.nume = NULL;
	else
	{
		s.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
		strcpy_s(s.nume,strlen(nume)+1, nume);
	}
	return s;
}
void afisare(struct Salariat s)
{
		printf("ID salariat: %d, Salariul: %5.2f, Nume: %s, Specializare: %c,Varsta: %i.\n",s.id,s.salariu,s.nume,s.specializare,s.varsta );
}
	
void modificaSalariul(float salariuNou, struct Salariat*s)
{
		if (salariuNou > 0)
			s->salariu = salariuNou;
}
	
void dezalocare(struct Salariat* s)
{
	if (s->nume != NULL)
	{
			free(s->nume);
			s->nume = NULL;
	}
}
void afisareVector(struct Salariat* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
		afisare(vector[i]);
	printf("\n");
}
void dezalocareV(struct Salariat** vector, int* nrElemente)
{
	for (int i = 0; i < *nrElemente; i++) 
		free((*vector)[i].nume);
			
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;  
}
void copiazaSalVarstaPesteMin(struct Salariat* s, int nrElem, int varstaMin, struct Salariat** vectNou, int* numarElemente)
{
	*numarElemente = 0;
	for (int i = 0; i < nrElem; i++)
		if (s[i].varsta > varstaMin)
		{
			(*numarElemente)++;
		}
	(*vectNou) = (struct Salariat*)malloc((*numarElemente) * sizeof(struct Salariat));
	int j = 0;
	for(int i=0;i<nrElem;i++)
		if (s[i].varsta > varstaMin)
		{
			struct Salariat temp = initializare(s[i].id, s[i].salariu, s[i].nume, s[i].specializare, s[i].varsta);
			(*vectNou)[j] = temp;
			j++;
		}
}

struct Salariat getPrimulSalDupaNume(struct Salariat* vector, int nrEl, const char* nume) {
	
	for (int i = 0; i < nrEl; i++)
	{
		if (strcmp(vector[i].nume, nume) == 0)
			return vector[i];
	}
	return initializare(1, 0, NULL, 0, '0');

}

int main()
{
	struct Salariat s1;
	s1=initializare(3, 2100, "Gigel", 'S',23);
	struct Salariat s2;
	s2.id = 2;
	s2.salariu = 3210.5;
	s2.specializare = 'B';
	s2.varsta = 56;
	s2.nume = (char*)malloc(strlen("Maria") + 1);
	strcpy_s(s2.nume,strlen("Maria")+1, "Maria");
	afisare(s1);
	afisare(s2);
	printf("\n");
	struct Salariat s3;
	s3 = initializare(1, 3456.2, "Patricia", 'L',18);
	struct Salariat* vector;
	vector = (struct Salariat*)malloc(3 * sizeof(struct Salariat));
	int numarElemente = 3;
	//vector[0] = s3;
	//vector[1] = s2;     - shallow copy
	//vector[2] = s1;
	//afisareVector(vector, numarElemente);
	///*dezalocare(&s1);
	//afisareVector(vector, numarElemente);*/
	vector[2] = initializare(s1.id, s1.salariu, s1.nume, s1.specializare,s1.varsta);
	vector[1] = initializare(s2.id, s2.salariu, s2.nume, s2.specializare,s2.varsta);
	vector[0] = initializare(s3.id, s3.salariu, s3.nume, s3.specializare,s3.varsta);
	afisareVector(vector, numarElemente);
	dezalocare(&s1);
	afisareVector(vector, numarElemente);
	
	struct Salariat* vectNou;
	int dim = 0;
	int varstaMin = 22;
	copiazaSalVarstaPesteMin(vector, numarElemente, varstaMin, &vectNou, &dim);
	afisareVector(vectNou, dim);

	dezalocareV(&vector, &numarElemente);
	//afisareVector(vector, numarElemente);

	printf("\nSalariatul cu numele 'Maria' este: \n");
	afisare(getPrimulSalDupaNume(vectNou, dim, "Maria"));

	return 0;
}
