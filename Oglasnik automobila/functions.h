#pragma once
#include <stdio.h>

typedef struct {
	char marka[30];
	char model[30];
	//int kilometraza
	int godinaProizvodnje;
	char motor[20];
	char mjenjac[20];
	float cijena;
}vehicle;

void loadVehicles();
void clearInputBuffer();
int confirmExit();