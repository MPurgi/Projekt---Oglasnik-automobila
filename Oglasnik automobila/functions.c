#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
static int numOfVehicles = 0;

void loadVehicles() {
	FILE* file = fopen("vehicles.txt", "r");
	if (file == NULL) {
		perror("Ucitavanje vozila iz datoteke vehicles.txt");
		exit(EXIT_FAILURE);
	}
	fread(&numOfVehicles, sizeof(int), 1, file);
	printf("Broj postavljenih oglasa: %d\n", numOfVehicles);
	vehicle* arrayVehicle = (vehicle*)calloc(numOfVehicles, sizeof(vehicle));
	if (arrayVehicle == NULL) {
		perror("Zauzimanje memorije za oglase");
		exit(EXIT_FAILURE);
	}
	fread(arrayVehicle, sizeof(vehicle), numOfVehicles, file);
	return arrayVehicle;
}

void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int confirmExit() {
	char choice;
	printf("Jeste li sigurni da zelite izaci iz programa? (y/n): ");
	scanf(" %c", &choice);
	clearInputBuffer();
	if (choice == 'y' || choice == 'Y') {
		return 1;
	}
	else if (choice == 'n' || choice == 'N') {
		return 0;
	}
	else {
		printf("Krivi unos. Molimo unesite 'y' ako zelite izaci iz programa ili 'n' ako ne zelite.\n");
	}
}

void createListing() {
	FILE* file = fopen("vehicles.txt", "w");
	if (file == NULL) {
		perror("Dodavanje oglasa u datoteku vehicles.txt");
		exit(EXIT_FAILURE);
	}
	fread(&numOfVehicles, sizeof(int), 1, file);
	printf("Broj vozila: %d\n", numOfVehicles);
	vehicle
}