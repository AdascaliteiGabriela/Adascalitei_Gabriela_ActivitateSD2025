
#include<stdio.h>
#include<stdlib.h>

//articol != structura 

struct Masina {
	int id;
	int nrLocuri;
	char* marca;
	float capacitateC;
	char normaPoluare;
};

struct Masina initializare(int id, int nrLocuri,const char* marca, float capacitateC, char norma) {
	struct Masina m;
	m.id = 1;
	m.capacitateC = capacitateC;
	m.nrLocuri = nrLocuri;
	m.marca = (char*)malloc((strlen(marca)+1)*sizeof(char));//se aloca numarul de octeti
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

int main() {
	struct Masina masina1;
	masina1 = initializare(1, 4, "Logan", 2000, '1');
	afisare(masina1);
	modificaNrLocuri(&masina1, 1);
	afisare(masina1);
	dezalocare(&masina1);
	afisare(masina1);
	printf("\nDimensiunea unui pointer: %d", sizeof(int*));
	printf("\nDimensiunea unui pointer de tip Masina: %d", sizeof(struct Masina*));
	printf("\nDimensiunea unei structuri de tip Masina: %d", sizeof(struct Masina));
	return 0;
}
