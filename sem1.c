
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

void modifica_Atribut(struct Masina m) {
	//modificarea unui atribut
}

void dezalocare(struct Masina* m) {
	//dezalocare campuri alocate dinamic
}

int main() {
	struct Masina masina1;
	masina1 = initializare(1, 4, "Logan", 2000, '1');
	afisare(masina1);
	return 0;
}
