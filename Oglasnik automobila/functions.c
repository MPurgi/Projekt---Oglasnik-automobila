#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
int numOfVehicles = 0;
static int numOfShowListingsCalls = 0;


void printMenu() {
	printf("\n===== Oglasnik automobila =====\n");
	printf("1. Postavi oglas\n");
	printf("2. Prikazi oglase\n");
	printf("3. Azuriraj oglas\n");
	printf("4. Izbrisi oglas\n");
	printf("5. Sortiraj po cijeni\n");
	printf("6. Ucitaj oglase\n");
	printf("7. Obrisi datoteku\n");
	printf("8. Preimenuj datoteku\n");
	printf("9. Ispis vozila po marki\n");
	printf("0. !Izlaz!\n");
	printf("Odabir: ");
}

//void createListing(vehicle** array, int* n) {
//	*array = (vehicle*)realloc(*array, (*n + 1) * sizeof(vehicle));
//	if (!*array) {
//		perror("Alokacija neuspjela");
//		exit(EXIT_FAILURE);
//	}
//
//	int newId = (*n == 0) ? 1 : (getMaxId(*array, *n) + 1);
//
//	vehicle* v = &(*array)[*n];
//	v->id = newId;
//
//	printf("ID: %d\n", v->id);
//	printf("Marka: ");
//	scanf("%31s", v->make);
//	printf("Model: ");
//	scanf("%31s", v->model);
//	printf("Cijena (u eurima): ");
//	scanf("%f", &v->price);
//	printf("Kilometraza: ");
//	scanf("%d", &v->mileage);
//	printf("Godina proizvodnje: ");
//	scanf("%d", &v->year);
//	printf("Motor (benzin,dizel...): ");
//	scanf("%15s", v->engine);
//	printf("Mjenjac (rucni, automatski...): ");
//	scanf("%15s", v->gearbox);
//	(*n)++;
//	numOfVehicles = *n;
//	printf("Oglas dodan.\n");
//	saveVehicles(*array, *n, "vehicles.txt");
//}

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
	safeInputString("Marka: ", v->make, MAX_MARKA);
	safeInputString("Model: ", v->model, MAX_MODEL);
	v->price = safeInputFloat("Cijena (u eurima): ");
	v->mileage = safeInputInt("Kilometraza: ");
	v->year = safeInputInt("Godina proizvodnje: ");
	safeInputString("Motor (benzin dizel...): ", v->engine, MAX_MOTOR);
	safeInputString("Mjenjac (rucni, automatski): ", v->gearbox, MAX_MJENJAC);
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

//vehicle* loadVehicles(int *n) {
//	FILE* file = fopen("vehicles.txt", "rb");
//	if (!file) {
//		perror("Ucitavanje vozila iz datoteke vehicles.txt");
//		*n = 0;
//		return NULL;
//	}
//
//	fread(n, sizeof(int), 1, file);
//	vehicle* arrayVehicle = calloc(*n, sizeof(vehicle));
//	if (!arrayVehicle && *n > 0) {
//		perror("Alokacija memorije neuspjela");
//		fclose(file);
//		*n = 0;
//		return NULL;
//	}
//	fread(arrayVehicle, sizeof(vehicle), *n, file);
//	fclose(file);
//	return arrayVehicle;
//}

vehicle* loadVehicles(int* n) {
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
	size_t readCount = fread(arrayVehicle, sizeof(vehicle), *n, file);
	if (readCount != (size_t)(*n)) {
		printf("Upozorenje: Ucitano je samo %zu od %d vozila.\n", readCount, *n);
	}
	if (feof(file)) {
		printf("Dohvacen je kraj datoteke.\n");
	}
	if (ferror(file)) {
		printf("Dogodila se greska pri ucitavanju datoteke!\n");
	}
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
	clearInputBuffer();
	for (int i = 0; i < n; i++) {
		if (array[i].id == id) {
			printf("Azuriranje podataka za ID: %d\n", id);
			safeInputString("Marka: ", array[i].make, MAX_MARKA);
			safeInputString("Model: ", array[i].model, MAX_MODEL);
			array[i].price = safeInputFloat("Cijena (u eurima): ");
			array[i].mileage = safeInputInt("Kilometraza: ");
			array[i].year = safeInputInt("Godina proizvodnje: ");
			safeInputString("Motor (benzin dizel...): ", array[i].engine, MAX_MOTOR);
			safeInputString("Mjenjac (rucni, automatski): ", array[i].gearbox, MAX_MJENJAC);
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

//static inline void clearInputBuffer(void) {
//	int c;
//	while ((c = getchar()) != '\n' && c != EOF);
//}

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
	numOfShowListingsCalls++;
	printf("Oglasi prikazani %d puta.\n", numOfShowListingsCalls);
	printf("Ukupno oglasa: %d\n", n);
	for (int i = 0; i < n; i++) {
		printf("ID: %d | %s %s | %d | %.2f EUR | %d km | %s | %s\n", array[i].id, array[i].make, array[i].model, array[i].year, array[i].price, array[i].mileage, array[i].engine, array[i].gearbox);		
	}
}

vehicle* deleteListing(vehicle* array, int* n) {
	int id, found = 0,i;
	printf("Unesi ID za brisanje: ");
	scanf("%d", &id);
	clearInputBuffer();
	for (i = 0; i < *n; i++) {
		if (array[i].id == id) {
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("Nema oglasa s tim ID-jem.\n");
	}

	for (int j = i; j < *n - 1; j++) {
		array[j] = array[j + 1];
	}
	(*n)--;

	vehicle* tmp = realloc(array, (*n) * sizeof(vehicle));
	if (tmp == NULL && *n > 0) {
		printf("Greska pri realokaciji memorije!\n");
		return array;
	}
	printf("Oglas uspjesno obrisan.\n");
	return tmp;
}

//int deleteListing(vehicle* array, int* n) {
//	int id, found = 0;
//	printf("Unesi ID za brisanje: ");
//	scanf("%d", &id);
//	clearInputBuffer();
//	for (int i = 0; i < *n; i++) {
//		if (array[i].id == id) {
//			for (int j = i; j < *n - 1; j++) {
//				array[j] = array[j + 1];
//			}
//			(*n)--;
//			numOfVehicles = *n;
//			array=(vehicle*)realloc(array, (*n)*sizeof(vehicle));
//			found = 1;
//			printf("Oglas obrisan.\n");
//			break;
//		}
//	}
//	if (!found) {
//		printf("Nema oglasa s tim ID-om.\n");
//	}
//	return found;
//}

void freeVehicles(vehicle** array) {
	free(*array);
	*array = NULL;
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

//void pause() {
//	printf("Pritisnite Enter za nastavak.\n");
//	clearInputBuffer();
//}

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

//void sortVehiclesByPrice(vehicle* array, int n) {
//	quickSortVehicles(array, 0, n - 1);
//	printf("Oglasi sortirani po cijeni(najmanje do najvise):\n");
//	for (int i = 0; i < n; i++) {
//		printf("ID: %d | %s %s | %d | %.2f EUR | %d km | %s | %s\n", array[i].id, array[i].make, array[i].model, array[i].year, array[i].price, array[i].mileage, array[i].engine, array[i].gearbox);
//	}
//}

void sortVehiclesByPrice(vehicle* array, int n) {
	qsort(array, n, sizeof(vehicle), compareByPrice);
	printf("Oglasi sortirani po cijeni(najmanje do najvise):\n");
	for (int i = 0; i < n; i++) {
		printf("ID: %d | %s %s | %d | %.2f EUR | %d km | %s | %s\n", array[i].id, array[i].make, array[i].model, array[i].year, array[i].price, array[i].mileage, array[i].engine, array[i].gearbox);
	}
}

void printFileSize(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (!file) {
		printf("Neuspjesno otvaranje datoteke %s\n", filename);
		return;
	}
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	printf("Velicina datoteke '%s' iznosi %ld bajtova.\n", filename, size);
	fclose(file);
}

void deleteFile(void) {
	char filename[100];
	printf("Unesi ime datoteke za brisanje: ");
	safeInputString("", filename, 100);
	if (remove(filename) == 0) {
		printf("Datoteka '%s' uspjesno obrisana.\n", filename);
	}
	else {
		perror("Greska pri brisanju datoteke");
	}
}

void renameFile(void) {
	char oldname[100], newname[100];
	printf("Unesi trenutno ime datoteke: ");
	safeInputString("", oldname, 100);
	printf("Unesi novo ime datoteke: ");
	safeInputString("", newname, 100);
	if (rename(oldname, newname) == 0) {
		printf("Datoteka je preimenovana u '%s'.\n", newname);
	}
	else {
		perror("Greska pri preimenovanju datoteke");
	}
}

void searchByMake(vehicle* array, int n) {
	char marka[MAX_MARKA];
	int found = 0;
	safeInputString("Unesi marku vozila za pretragu: ", marka, MAX_MARKA);

	for (int i = 0; i < n; i++) {
		if (strcmp(array[i].make, marka) == 0) {
			printf("ID: %d | %s %s | %d | %.2f EUR | %d km | %s | %s\n", array[i].id, array[i].make, array[i].model, array[i].year, array[i].price, array[i].mileage, array[i].engine, array[i].gearbox);
			found = 1;
		}
	}
	if (!found) {
		printf("Nema vozila s markom '%s'.\n", marka);
	}
}