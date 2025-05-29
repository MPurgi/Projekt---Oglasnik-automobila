#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
static int numOfVehicles = 0;

void printMenu() {
	printf("\n===== Oglasnik automobila =====\n");
	printf("1. Postavi oglas\n");
	printf("2. Prikazi oglase\n");
	printf("3. Azuriraj oglas\n");
	printf("4. Izbrisi oglas\n");
	printf("5. Sortiraj po cijeni\n");
	printf("6. Ucitaj oglase\n");
	printf("0. !Izlaz!\n");
	printf("Odabir: ");
}

void createListing(vehicle** array, int* n) {
	*array = (vehicle*)realloc(*array, (*n + 1) * sizeof(vehicle));
	if (!*array) {
		perror("Alokacija neuspjela");
		exit(EXIT_FAILURE);
	}
	vehicle* v = &(*array)[*n];
	printf("ID: ");
	scanf("%d", &v->id);
	printf("Marka: ");
	scanf("%31s", v->make);
	printf("Model: ");
	scanf("%31s", v->model);
	printf("Cijena: ");
	scanf("%f", &v->price);
	printf("Kilometraza: ");
	scanf("%d", &v->mileage);
	printf("Godina proizvodnje: ");
	scanf("%d", &v->year);
	printf("Motor: ");
	scanf("%15s", v->engine);
	printf("Mjenjac: ");
	scanf("%15s", v->gearbox);
	(*n)++;
	numOfVehicles = *n;
	printf("Oglas dodan.\n");
}

void loadVehicles(int *n) {
	FILE* file = fopen("vehicles.txt", "rb");
	if (!file) {
		perror("Ucitavanje vozila iz datoteke vehicles.txt");
		*n = 0;
		return NULL;
	}
	fread(n, sizeof(int), 1, file);
	vehicle* arrayVehicle = calloc(*n, sizeof(vehicle));
	if (!arrayVehicle && *n > 0) {
		perror("Alokacija memorije neuspjela");
		fclose(file);
		*n = 0;
		return NULL;
	}
	fread(arrayVehicle, sizeof(vehicle), *n, file);
	fclose(file);
	numOfVehicles = *n;
	return arrayVehicle;
}

//void loadVehicles() {
//	FILE* file = fopen("vehicles.txt", "rb");
//	if (file == NULL) {
//		perror("Ucitavanje vozila iz datoteke vehicles.txt");
//		exit(EXIT_FAILURE);
//	}
//	fread(&numOfVehicles, sizeof(int), 1, file);
//	printf("Broj postavljenih oglasa: %d\n", numOfVehicles);
//	vehicle* arrayVehicle = (vehicle*)calloc(numOfVehicles, sizeof(vehicle));
//	if (arrayVehicle == NULL) {
//		perror("Zauzimanje memorije za oglase");
//		exit(EXIT_FAILURE);
//	}
//	fread(arrayVehicle, sizeof(vehicle), numOfVehicles, file);
//	fclose(file);
//	return arrayVehicle;
//}

void saveVehicles(vehicle* array, int n, const char* filename) {
	FILE* fp = fopen(filename, "wb");
	if (!fp) {
		perror("Greska pri otvaranju datoteke");
		return;
	}
	fwrite(&n, sizeof(int), 1, fp);
	fwrite(array, sizeof(vehicle), n, fp);
	fclose(fp);
	printf("Oglasni spremljeni u datoteku.\n");
}

void updateListing(vehicle* array, int n) {
	int id, found = 0;
	printf("Unesi ID za izmjenu: ");
	scanf("%d", &id);
	for (int i = 0; i < n; i++) {
		if (array[i].id == id) {
			printf("Nova marka: ");
			scanf("%31s", array[i].make);
			printf("Novi model: ");
			scanf("%31s", array[i].model);
			printf("Nova cijena: ");
			scanf("%f", &array[i].price);
			printf("Nova kilometraza: ");
			scanf("%d", &array[i].mileage);
			printf("Nova godina proizvodnje: ");
			scanf("%d", &array[i].year);
			printf("Novi motor: ");
			scanf("%15s", array[i].engine);
			printf("Novi mjenjac: ");
			scanf("%15s", array[i].gearbox);
			found = 1;
			printf("Oglas azuriran.\n");
			break;
		}
	}
	if (!found) {
		printf("Oglas nije pronaden.\n");
	}
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



//void createListing() {
//	vehicle temp;
//
//	printf("Broj vozila: %d\n", numOfVehicles);
//	getchar();
//
//	printf("Unesite marku vozila.\n");
//	scanf("%19[^\n]", temp.make);
//	clearInputBuffer();
//	
//	printf("Unesite model vozila.\n");
//	scanf("%19[^\n]", temp.model);
//	clearInputBuffer();
//
//	printf("Unesite godinu proizvodnje vozila.\n");
//	scanf("%d", &temp.year);
//	clearInputBuffer();
//
//	printf("Unesite motor vozila(gorivo).\n");
//	scanf("%19[^\n]", temp.engine);
//	clearInputBuffer();
//
//	printf("Unesite mjenjac u vozilu.\n");
//	scanf("%19[^\n]", temp.gearbox);
//	clearInputBuffer();
//
//	printf("Unesite cijenu vozila.\n");
//	scanf("%d", &temp.price);
//	clearInputBuffer();
//
//	FILE* file = fopen("vehicles.txt", "w");
//	vehicle* vehicles = NULL;
//
//	if (file == NULL) {
//		fread(&numOfVehicles, sizeof(int), 1, file);
//		vehicles = (vehicle*)malloc(numOfVehicles * sizeof(vehicle));
//		if (vehicles = NULL) {
//			perror("Greska kod alokacije memorije za vozila");
//			exit(EXIT_FAILURE);
//		}
//		fread(vehicles, sizeof(vehicle), numOfVehicles, file);
//		fclose(file);
//	}
//	else {
//		numOfVehicles = 0;
//	}
//
//	vehicles = (vehicle*)realloc(vehicles, (numOfVehicles + 1) * sizeof(vehicle));
//	if(vehicles==NULL){
//		perror("Greska kod prosirivanja memorije.");
//		exit(EXIT_FAILURE);
//	}
//	vehicles[numOfVehicles] = temp;
//	numOfVehicles++;
//
//	file = fopen("vehicles.txt", "w");
//	if (file == NULL) {
//		perror("Greska kod pisanja u datoteku vehicles.txt");
//		exit(EXIT_FAILURE);
//	}
//	fwrite(&numOfVehicles, sizeof(int), 1, file);
//	fwrite(vehicles, sizeof(vehicle), numOfVehicles, file);
//	fclose(file);
//	
//	printf("Oglas uspjesno dodan.\n");
//
//	free(vehicles);
//
//}

void showListings(vehicle* array, int n) {
	printf("Ukupno oglasa: %d\n", n);
	for (int i = 0; i < n; i++) {
		printf("ID: %d | %s %s | %d | %.2f EUR | %d km | %s | %s\n", array[i].id, array[i].make, array[i].model, array[i].year, array[i].price, array[i].mileage, array[i].engine, array[i].gearbox);		
	}
}

void deleteListing(vehicle** array, int* n) {
	int id, found = 0;
	printf("Unesi ID za brisanje: ");
	scanf("%d", &id);
	for (int i = 0; i < *n; i++) {
		if ((*array=[i].id == id) {
			for (int j = i; j < *n - 1; j++) {
				(*array)[j] = (*array)[j + 1];
			}
			*n=*n-1;
			numOfVehicles = *n;
			*array=(vehicle*)realloc(*array, (*n)*sizeof(vehicle));
			found = 1;
			printf("Oglas obrisan.\n");
			break;
		}
	}
	if (!found) {
		printf("Nema oglasa s tim ID-om.\n");
	}
}

void freeVehicles(vehicle* array) {
	free(array);
	numOfVehicles = 0;
}

int compareByPrice(const void* a, const void* b) {
	float c1 = ((vehicle*)a)->price;
	float c2 = ((vehicle*)b)->price;
	if (c1 < c2) {
		return -1;
	}
	if (c1 > c2) {
		return 1;
	}
	return 0;
}

void sortVehiclesByPrice(vehicle* array, int n) {
	qsort(array, n, sizeof(vehicle), compareByPrice);
	printf("Oglasni sortirani po cijeni:\n");
	for (int i = 0; i < n; i++) {
		printf("ID: %d | %s %s | %d | %.2f EUR | %d km | %s | %s\n", array[i].id, array[i].make, array[i].model, array[i].year, array[i].price, array[i].mileage, array[i].engine, array[i].gearbox);
	}
}

//void removeDataFile(const char* filename) {
//	if (remove(filename) == 0) {
//		printf("Datoteka obrisana.\n");
//	}
//	else {
//		perror("Greska pri brisanju datoteke.");
//	}
//}

//void pause() {
//	printf("Pritisnite Enter za nastavak.\n");
//	getchar();
//}

void pause() {
	printf("Pritisnite Enter za nastavak.\n");
	clearInputBuffer();
}