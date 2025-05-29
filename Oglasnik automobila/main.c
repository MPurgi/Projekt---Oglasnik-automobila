#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"
typedef enum {
	IZLAZ,
	DODAJ_OGLAS,
	POPIS_OGLASA,
	PRETRAZI_OGLAS,
	UREDI_OGLAS,
	OBRISI_OGLAS,
	SORT_CIJENA,
	UCITAJ_OGLASE
}MENU;

int main() {
	int choice;
	int n = 0;
	static vehicle* arrayVehicle = NULL;

	arrayVehicle = loadVehicles(&n);
	do {
		printMenu();
		scanf("%d", &choice);
		clearInputBuffer();
		switch (choice) {
		case 1: createListing(&arrayVehicle, &n);
				break;
		case 2: showListings(arrayVehicle, n);
			break;
		case 3: updateListing(arrayVehicle, n);
			break;
		case 4: deleteListing(arrayVehicle, &n);
			break;
		case 5: sortVehiclesByPrice(arrayVehicle, n);
			break;
		case 6: 
			freeVehicles(arrayVehicle);
			arrayVehicle = loadVehicles(&n);
			break;
		case 0:
			if (confirmExit()) {
				saveVehicles(arrayVehicle, n, "vehicles.txt");
				freeVehicles(arrayVehicle);
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