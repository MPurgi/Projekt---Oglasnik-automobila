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
	vehicle temp;

	printf("Broj vozila: %d\n", numOfVehicles);
	getchar();

	printf("Unesite marku vozila.\n");
	scanf("%19[^\n]", temp.make);
	clearInputBuffer();
	
	printf("Unesite model vozila.\n");
	scanf("%19[^\n]", temp.model);
	clearInputBuffer();

	printf("Unesite godinu proizvodnje vozila.\n");
	scanf("%d", &temp.year);
	clearInputBuffer();

	printf("Unesite motor vozila(gorivo).\n");
	scanf("%19[^\n]", temp.engine);
	clearInputBuffer();

	printf("Unesite mjenjac u vozilu.\n");
	scanf("%19[^\n]", temp.gearbox);
	clearInputBuffer();

	printf("Unesite cijenu vozila.\n");
	scanf("%d", &temp.price);
	clearInputBuffer();

	FILE* file = fopen("vehicles.txt", "w");
	vehicle* vehicles = NULL;

	if (file == NULL) {
		fread(&numOfVehicles, sizeof(int), 1, file);
		vehicles = (vehicle*)malloc(numOfVehicles * sizeof(vehicle));
		if (vehicles = NULL) {
			perror("Greska kod alokacije memorije za vozila");
			exit(EXIT_FAILURE);
		}
		fread(vehicles, sizeof(vehicle), numOfVehicles, file);
		fclose(file);
	}
	else {
		numOfVehicles = 0;
	}

	vehicles = (vehicle*)realloc(vehicles, (numOfVehicles + 1) * sizeof(vehicle));
	if(vehicles==NULL){
		perror("Greska kod prosirivanja memorije.");
		exit(EXIT_FAILURE);
	}
	vehicles[numOfVehicles] = temp;
	numOfVehicles++;

	file = fopen("vehicles.txt", "w");
	if (file == NULL) {
		perror("Greska kod pisanja u datoteku vehicles.txt");
		exit(EXIT_FAILURE);
	}
	fwrite(&numOfVehicles, sizeof(int), 1, file);
	fwrite(vehicles, sizeof(vehicle), numOfVehicles, file);
	fclose(file);
	
	printf("Oglas uspjesno dodan.\n");

	free(vehicles);

}

void pause() {
	printf("Pritisnite Enter za nastavak.\n");
	getchar();
}