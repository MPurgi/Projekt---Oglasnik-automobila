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

	int newId = (*n == 0) ? 1 : (getMaxId(*array, *n) + 1);

	vehicle* v = &(*array)[*n];
	v->id = newId;

	printf("ID: %d\n", v->id);
	printf("Marka: ");
	scanf("%31s", v->make);
	printf("Model: ");
	scanf("%31s", v->model);
	printf("Cijena (u eurima): ");
	scanf("%f", &v->price);
	printf("Kilometraza: ");
	scanf("%d", &v->mileage);
	printf("Godina proizvodnje: ");
	scanf("%d", &v->year);
	printf("Motor (benzin,dizel...): ");
	scanf("%15s", v->engine);
	printf("Mjenjac (rucni, automatski...): ");
	scanf("%15s", v->gearbox);
	(*n)++;
	numOfVehicles = *n;
	printf("Oglas dodan.\n");
	saveVehicles(*array, *n, "vehicles.txt");
}

//void createListing(vehicle** array, int* n) {
//	*array = (vehicle*)realloc(*array, (*n + 1) * sizeof(vehicle));
//	if (!*array) {
//		perror("Alokacija neuspjela");
//		exit(EXIT_FAILURE);
//	}
//
//	int newId = (*n == 0) ? 1 : (getMaxId(*array, *n) + 1);
//	int engineChoice;
//
//	vehicle* v = &(*array)[*n];
//	v->id = newId;
//
//	printf("ID: %d\n", v->id);
//	printf("Marka: ");
//	scanf("% 31[^\n]", v->make);
//	printf("Model: ");
//	scanf("% 31[^\n]", v->model);
//	printf("Cijena (u eurima): ");
//	scanf("%f", &v->price);
//	printf("Kilometraza: ");
//	scanf("%d", &v->mileage);
//	printf("Godina proizvodnje: ");
//	scanf("%d", &v->year);
//	printf("Odaberi vrstu motora:\n");
//	printf("1. Benzin\n");
//	printf("2. Dizel\n");
//	printf("3. Hibrid\n");
//	printf("4. Elektricni\n");
//	printf("Unos: ");
//	scanf("%d", &engineChoice);
//
//	switch (engineChoice) {
//		case 1: strcpy(v->engine, "Benzin"); break;
//		case 2: strcpy(v->engine, "Dizel"); break;
//		case 3: strcpy(v->engine, "Hibrid"); break;
//		case 4: strcpy(v->engine, "Elektricni"); break;
//		default: strcpy(v->engine, "Nepoznato"); break;
//	}
//	scanf("%15s", v->engine);
//	printf("Mjenjac (rucni, automatski...): ");
//	scanf("%15s", v->gearbox);
//	(*n)++;
//	numOfVehicles = *n;
//	printf("Oglas dodan.\n");
//	saveVehicles(*array, *n, "vehicles.txt");
//}

vehicle* loadVehicles(int *n) {
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
	return arrayVehicle;
}

void saveVehicles(vehicle* array, int n, const char* filename) {
	FILE* fp = fopen(filename, "wb");
	if (!fp) {
		perror("Greska pri otvaranju datoteke");
		return;
	}
	fwrite(&n, sizeof(int), 1, fp);
	fwrite(array, sizeof(vehicle), n, fp);
	fclose(fp);
	
	printf("Spremanje u datoteku uspjesno.\n");
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
			//saveVehicles(arrayVehicle, n, "vehicles.txt");
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

void showListings(vehicle* array, int n) {
	printf("Ukupno oglasa: %d\n", n);
	for (int i = 0; i < n; i++) {
		printf("ID: %d | %s %s | %d | %.2f EUR | %d km | %s | %s\n", array[i].id, array[i].make, array[i].model, array[i].year, array[i].price, array[i].mileage, array[i].engine, array[i].gearbox);		
	}
}

int deleteListing(vehicle* array, int* n) {
	int id, found = 0;
	printf("Unesi ID za brisanje: ");
	scanf("%d", &id);
	for (int i = 0; i < *n; i++) {
		if (array[i].id == id) {
			for (int j = i; j < *n - 1; j++) {
				array[j] = array[j + 1];
			}
			(*n)--;
			numOfVehicles = *n;
			array=(vehicle*)realloc(array, (*n)*sizeof(vehicle));
			found = 1;
			printf("Oglas obrisan.\n");
			break;
		}
	}
	if (!found) {
		printf("Nema oglasa s tim ID-om.\n");
	}
	return found;
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

//void sortVehiclesByPrice(vehicle* array, int n) {
//	qsort(array, n, sizeof(vehicle), compareByPrice);
//	printf("Oglasni sortirani po cijeni:\n");
//	for (int i = 0; i < n; i++) {
//		printf("ID: %d | %s %s | %d | %.2f EUR | %d km | %s | %s\n", array[i].id, array[i].make, array[i].model, array[i].year, array[i].price, array[i].mileage, array[i].engine, array[i].gearbox);
//	}
//}

void pause() {
	printf("Pritisnite Enter za nastavak.\n");
	clearInputBuffer();
}

int getMaxId(vehicle* array, int n) {
	int maxId = 0;
	for (int i = 0; i < n; i++) {
		if (array[i].id > maxId) {
			maxId = array[i].id;
		}
	}
	return maxId;
}

void swapVehicles(vehicle* a, vehicle* b) {
	vehicle temp = *a;
	*a = *b;
	*b = temp;
}

int partition(vehicle* array, int low, int high) {
	float pivot = array[high].price;
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (array[j].price <= pivot) {
			i++;
			swapVehicles(&array[i], &array[j]);
		}
	}
	swapVehicles(&array[i + 1], &array[high]);
	return i + 1;
}

void quickSortVehicles(vehicle* array, int low, int high) {
	if (low < high) {
		int pi = partition(array, low, high);
		quickSortVehicles(array, low, pi - 1);
		quickSortVehicles(array, pi + 1, high);
	}
}

void sortVehiclesByPrice(vehicle* array, int n) {
	quickSortVehicles(array, 0, n - 1);
	printf("Oglasi sortirani po cijeni(najmanje do najvise):\n");
	for (int i = 0; i < n; i++) {
		printf("ID: %d | %s %s | %d | %.2f EUR | %d km | %s | %s\n", array[i].id, array[i].make, array[i].model, array[i].year, array[i].price, array[i].mileage, array[i].engine, array[i].gearbox);
	}
}