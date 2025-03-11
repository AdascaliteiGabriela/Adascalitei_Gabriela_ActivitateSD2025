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

int main()
{
	struct Salariat s1;
	s1=initializare(3, 2100, "Gigel", 's');
	struct Salariat s2;
	s2.id = 2;
	s2.salariu = 3210.5;
	s2.specializare = 'B';
	s2.nume = (char*)malloc(strlen("Maria") + 1);
	strcpy_s(s2.nume,strlen("Maria")+1, "Maria");
	afisare(s1);
	afisare(s2);
	return 0;
}