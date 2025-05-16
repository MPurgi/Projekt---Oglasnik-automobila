#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"
typedef enum {
	IZLAZ,
	POPIS_OGLASA,
	UREDI_OGLAS,
	OBRISI_OGLAS,
	DODAJ_OGLAS
}MENU;

void printMenu() {
	printf("\n===== Oglasnik automobila =====\n");
	printf("1. Postavi oglas\n");
	printf("2. Prikazi oglase\n");
	printf("3. Pretrazi oglase\n");
	printf("4. Azuriraj oglas\n");
	printf("5. Izbrisi oglas\n");
	printf("0. !Izlaz!\n");
}

int main() {
	int choice;
	static vehicle* arrayVehicle = NULL;
	loadVehicles();
	do {
		printMenu();
		scanf("%d", &choice);
		clearInputBuffer();
		switch (choice) {
		case 1: createListing();
				break;
		case 2: showListings();
			break;
		case 3: searchListing();
			break;
		case 4: updateListing();
			break;
		case 5: deleteListing();
			break;
		case 0:
			if (confirmExit()) {
				saveVehicles();
				printf("Izlaz iz oglasnika!\n");
				return 0;
			}
			else {
				printf("Povratak u meni.\n");
				break;
			}
		default:
			printf("Nevazeci odabir.\n");
			break;
		}
			pause();
		
	} while (1);
	return 0;
}