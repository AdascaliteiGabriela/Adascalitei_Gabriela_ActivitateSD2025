#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

struct Masina {
	int id;
	int nrLocuri;
	char* marca;
	float capacitateC;
	char normaPoluare;
};

struct Masina initializare(int id, int nrLocuri, const char* marca, float capacitateC, char norma) {
	struct Masina m;
	m.id = 1;
	m.capacitateC = capacitateC;
	m.nrLocuri = nrLocuri;
	m.marca = (char*)malloc((strlen(marca) + 1) * sizeof(char));//se aloca numarul de octeti
	strcpy_s(m.marca, strlen(marca) + 1, marca);
	m.normaPoluare = norma;
	return m;
}
	void afisare(struct Masina m) {
		printf("ID masina: %d \nNR Locuri: %d\nCapacitate:  %4.2f\nMarca: %s\nEuro%c",m.id,m.nrLocuri,m.capacitateC,m.marca,m.normaPoluare);
	}
	
	void modificaNrLocuri(struct Masina* m, int numarNou) {
		if(numarNou>0)
			m->nrLocuri += numarNou;
	}
	
	void dezalocare(struct Masina* m) {
	
		free(m->marca);
		m->marca = NULL;
		//(*m).marca=NULL;
		/* NU STERGEM NOI masina1! m este in stiva lui main, deci este gestionat automat. free(m);m = NULL;*/
	}




void afisareVector(struct Masina* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
		afisare(vector[i]);
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Masina *vectorNou=NULL;
	vectorNou = (struct Masina*)malloc(nrElementeCopiate * sizeof(struct Masina));
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = initializare(vector[i].id,vector[i].marca,vector[i].nrLocuri,vector[i].capacitateC,vector[i].normaPoluare);
	}
	return vectorNou;
}



void copiazaAnumiteElemente(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
}

struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Masina s;
	s.id = 1;

	return s;
}
	


int main() {
	struct Masina* vector;
	int nrElemente=3;
	vector = (struct Masina*)malloc(nrElemente * sizeof(struct Masina));
	vector[0] = initializare(1, 3, "Dacia", 40, '5');
	vector[1] = initializare(2, 5, "Honda", 30, '6');
	vector[2] = initializare(3, 4, "Dacia", 50, '3');
	afisare(vector[0]);
	afisareVector(vector,nrElemente);
	return 0;
}