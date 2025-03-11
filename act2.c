#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

struct Salariat {
	int id;
	float salariu;
	char* nume;
	char specializare;

};

struct Salariat initializare(int id, float salariul, const char* nume, char specializare)
{
	struct Salariat s;
	s.id = id;
	s.salariu = salariul;
	s.specializare = specializare;
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
		printf("ID salariat: %d, Salariul: %5.2f, Nume: %s, Specializare: %c.\n",s.id,s.salariu,s.nume,s.specializare );
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



int main()
{
	struct Salariat s1;
	s1=initializare(3, 2100, "Gigel", 'S');
	struct Salariat s2;
	s2.id = 2;
	s2.salariu = 3210.5;
	s2.specializare = 'B';
	s2.nume = (char*)malloc(strlen("Maria") + 1);
	strcpy_s(s2.nume,strlen("Maria")+1, "Maria");
	afisare(s1);
	afisare(s2);
	printf("\n");
	struct Salariat s3;
	s3 = initializare(1, 3456.2, "Patricia", 'L');
	struct Salariat* vector;
	vector = (struct Salariat*)malloc(3 * sizeof(struct Salariat));
	int numarElemente = 3;
	//vector[0] = s3;
	//vector[1] = s2;     - shallow copy
	//vector[2] = s1;
	//afisareVector(vector, numarElemente);
	///*dezalocare(&s1);
	//afisareVector(vector, numarElemente);*/
	vector[2] = initializare(s1.id, s1.salariu, s1.nume, s1.specializare);
	vector[1] = initializare(s2.id, s2.salariu, s2.nume, s2.specializare);
	vector[0] = initializare(s3.id, s3.salariu, s3.nume, s3.specializare);
	afisareVector(vector, numarElemente);
	dezalocare(&s1);
	afisareVector(vector, numarElemente);
	return 0;
}