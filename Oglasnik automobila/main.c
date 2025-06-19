#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"
#include "utils.h"
typedef enum {
	IZLAZ,
	DODAJ_OGLAS,
	POPIS_OGLASA,
	PRETRAZI_OGLAS,
	UREDI_OGLAS,
	OBRISI_OGLAS,
	SORT_CIJENA,
	UCITAJ_OGLASE,
	OBRISI_DATOTEKU,
	PREIMENUJ_DATOTEKU
}MENU;



int main() {
	int choice;
	int n = 0;
	static vehicle* arrayVehicle = NULL;

	arrayVehicle = loadVehicles(&n);
	do {
		printMenu();
		if (scanf("%d", &choice) != 1) {
			printf("Neispravan unos! Pokusajte ponovno.\n");
			clearInputBuffer();
			continue;
		}
		clearInputBuffer();
		switch (choice) {
		case 1: createListing(&arrayVehicle, &n);
				break;
		case 2: 
			CLEAR_SCREEN();
			showListings(arrayVehicle, n);
			break;
		case 3: updateListing(arrayVehicle, n);
			saveVehicles(arrayVehicle, n, "vehicles.txt");
			break;
		case 4: arrayVehicle = deleteListing(arrayVehicle, &n);
			saveVehicles(arrayVehicle, n, "vehicles.txt");
			break;
		case 5: sortVehiclesByPrice(arrayVehicle, n);
			break;
		case 6: 
			freeVehicles(&arrayVehicle);
			arrayVehicle = NULL;
			arrayVehicle = loadVehicles(&n);
			printFileSize("vehicles.txt");
			break;
		case 7:
			deleteFile();
			break;
		case 8:
			renameFile();
			break;
		case 9:
			searchByMake(arrayVehicle, n);
			break;
		case 0:
			if (confirmExit()) {
				saveVehicles(arrayVehicle, n, "vehicles.txt");
				freeVehicles(&arrayVehicle);
				arrayVehicle = NULL;
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
			PAUSE();
		
	} while (1);
	return 0;
}