#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "utils.h"
int numOfVehicles = 0;
static int numOfShowListingsCalls = 0;

void printMenu() {
	printf("\n===== Oglasnik automobila =====\n");
	printf("1. Postavi oglas\n");
	printf("2. Prikazi oglase\n");
	printf("3. Azuriraj oglas\n");
	printf("4. Izbrisi oglas\n");
	printf("5. Sortiraj po cijeni\n");
	printf("6. Ucitaj oglase, velicinu datoteke\n");
	printf("7. Obrisi datoteku\n");
	printf("8. Preimenuj datoteku\n");
	printf("9. Ispis vozila po marki\n");
	printf("0. !Izlaz!\n");
	printf("Odabir: ");
}

//Funkcija za sigurno dodavanje novog uglasa u dinamicko polje
void createListing(vehicle** array, int* n) {

	vehicle* tmp = realloc(*array, (*n + 1) * sizeof(vehicle));
	if (!tmp) {
		perror("Alokacija neuspjela");
		exit(EXIT_FAILURE);
	}
	*array = tmp;

	int newId = (*n == 0) ? 1 : (getMaxId(*array, *n) + 1);

	vehicle* v = &(*array)[*n];
	v->id = newId;

	printf("ID: %d\n", v->id);
	safeInputString("Marka: ", v->make, MAX_MARKA);
	toLowerString(v->make);
	safeInputString("Model: ", v->model, MAX_MODEL);
	v->price = safeInputFloat("Cijena (u eurima): ");
	v->mileage = safeInputInt("Kilometraza: ");
	v->year = safeInputYear("Godina proizvodnje: ");
	inputEngine(&v->engineType);
	inputGearbox(&v->gearboxType);
	(*n)++;
	numOfVehicles = *n;
	printf("Oglas dodan.\n");
	saveVehicles(*array, *n, "vehicles.txt");
}


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

	for (int i = 0; i < *n; i++) {
		toLowerString(arrayVehicle[i].make);
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

//Funkcija za azuriranje i izmjenu postojeceg oglasa prema ID-u
void updateListing(vehicle* array, int n) {
	int id, found = 0; //trazeni ID, oznaka za pronalazak oglasa

	printf("Unesi ID za izmjenu: ");
	//Siguran unos ID-a sa provjerom ispravnosti
	if (scanf("%d", &id) != 1) {
		printf("Neispravan unos!\n");
		clearInputBuffer();
		return;
	}
	clearInputBuffer();
	//pretrazivanje polja vozila po ID-u
	for (int i = 0; i < n; i++) {
		if (array[i].id == id) {
			//ako je pronaden oglas s trazenim ID-em
			printf("Ako ne zelite promjenu, pritisnite ENTER.\n");
			printf("Azuriranje podataka za ID: %d\n", id);

			printf("Marka [%s]: ", array[i].make);
			inputUpdateString(array[i].make, MAX_MARKA);
			toLowerString(array[i].make);

			printf("Model [%s]: ", array[i].model);
			inputUpdateString(array[i].model, MAX_MODEL);

			printf("Cijena (u eurima) [%.2f]: ", array[i].price);
			inputUpdateFloat(&array[i].price);

			printf("Kilometraza [%d]: ", array[i].mileage);
			inputUpdateInt(&array[i].mileage);

			printf("Godina proizvodnje [%d]: ", array[i].year);
			inputUpdateYear(&array[i].year);

			printf("Zelite li azurirati motor?\nPritisnite:\nENTER za preskociti\nBilo koji znak za promjenu: ");
			
			char buffer[8];
			fgets(buffer, sizeof(buffer), stdin);
			if (buffer[0] != '\n') {
				inputEngine(&array[i].engineType);
			}

			printf("Zelite li azurirati mjenjac?\nPritisnite:\nEnter za preskociti\nBilo koji znak za promjenu: ");
			fgets(buffer, sizeof(buffer), stdin);
			if (buffer[0] != '\n') {
				inputGearbox(&array[i].gearboxType);
			}

			found = 1;
			printf("Oglas azuriran.\n");
			break;
		}
	}
	if (!found) {
		printf("Oglas nije pronaden.\n");
	}
}

int confirmExit() {
	char choice;
	int c, isValid;
	while (1) {
		printf("Jeste li sigurni da zelite izaci iz programa? (y/n): ");
		isValid = 1;
		choice = getchar();
		while ((c = getchar()) != '\n' && c != EOF) {
			isValid = 0;
		}
		if (!isValid) {
			printf("Krivi unos. Molimo unesite 'y' ili 'n'.\n");
			continue;
		}
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
}

void showListings(vehicle* array, int n) {
	if (!array || n <= 0) {
		printf("Nema oglasa za prikaz.\n");
		return;
	}
	numOfShowListingsCalls++;
	qsort(array, n, sizeof(vehicle), compareById);
	printAllVehicles(array, n);
	printf("Oglasi prikazani %d puta.\n", numOfShowListingsCalls);
	printf("Ukupno oglasa: %d\n", n);
}


//Brisanje iz polja prema ID-u, vraca novi pokazivac na polje, moze biti NULL ako je polje prazno nakon brisanja
vehicle* deleteListing(vehicle* array, int* n) {
	int id, found = 0,i;
	printf("Unesi ID za brisanje: ");
	if (scanf("%d", &id) != 1) {
		printf("Neispravan unos!\n");
		clearInputBuffer();
		return array;
	}
	clearInputBuffer();
	for (i = 0; i < *n; i++) {
		if (array[i].id == id) {
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("Nema oglasa s tim ID-jem.\n");
		return array;
	}
	//brise oglas i sve elemente pomice ulijevo
	for (int j = i; j < *n - 1; j++) {
		array[j] = array[j + 1];
	}
	(*n)--;
	//ako nema vise oglasa oslobada memoriju i vraca NULL
	if (*n == 0) {
		free(array);
		printf("Oglas uspjesno obrisan.\n");
		return NULL;
	}
	//realocira memoriju na novu velicinu, za element manje
	vehicle* tmp = realloc(array, (*n) * sizeof(vehicle));
	if (tmp == NULL) {
		printf("Greska pri realokaciji memorije!\n");
		return array; //ako realloc ne uspije vraca se novi pokazivac
	}
	printf("Oglas uspjesno obrisan.\n");
	return tmp; //vraca novi ili isti pokazivac na polje
}

void freeVehicles(vehicle** array) {
	free(*array);
	*array = NULL;
	numOfVehicles = 0;
}

//int compareByPrice(const void* a, const void* b) {
//	float c1 = ((vehicle*)a)->price;
//	float c2 = ((vehicle*)b)->price;
//	if (c1 < c2) {
//		return -1;
//	}
//	if (c1 > c2) {
//		return 1;
//	}
//	return 0;
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
//funkcija za podjelu u quicksortu
//dijeli polje tako da su svi elementi manji od pivota lijevo, a veci desno
//low je pocetni index podniza, high je zadnji index podniza
int partition(vehicle* array, int low, int high) {
	float pivot = array[high].price; //odabire se zadnji element u podnizu po cijeni kao pivot
	int i = low - 1; //indeks manjeg elementa, sve lijevo od i je <= pivot
	for (int j = low; j < high; j++) { //prolazi kroz sve elemente od low do high-1
		if (array[j].price <= pivot) {
			i++; 
			swapVehicles(&array[i], &array[j]); //zamijeni ako je element manji ili jednak pivotu
		}
	}
	swapVehicles(&array[i + 1], &array[high]); // stavlja pivot na pravo mjesto, dakle iza svih manjih
	return i + 1; //vraca indeks pivota koji se sada nalazi na pravom mjestu
}
//rekurzivna quicksort funkcija za sortiranje po cijeni
void quickSortVehicles(vehicle* array, int low, int high) {
	if (low < high) {
		int pi = partition(array, low, high); //pi je pivot index, index nakon pivota particije
		// Rekurzivno sortia lijevi i desni dio oko pivota
		quickSortVehicles(array, low, pi - 1); // Sortira liejvi dio, odnosno manji od pivota
		quickSortVehicles(array, pi + 1, high);
	}
}

void sortVehiclesByPrice(vehicle* array, int n) {
	//qsort(array, n, sizeof(vehicle), compareByPrice);
	quickSortVehicles(array, 0, n - 1);
	printf("Oglasi sortirani po cijeni (najmanje do najvise):\n");
	printAllVehicles(array, n);
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
	toLowerString(marka);
	for (int i = 0; i < n; i++) {
		if (strcmp(array[i].make, marka) == 0) {
			printVehicle(&array[i]);
			found = 1;
		}
	}
	if (!found) {
		printf("Nema vozila s markom '%s'.\n", marka);
	}
}

void inputEngine(EngineType* engineType) {
	int choice;

	do {
		printf("Odaberite tip motora:\n");
		printf("0. Nepoznato\n1. Benzin\n2. Dizel\n3. Hibrid\n4. Elektricni\n");
		choice = safeInputInt("Vas odabir: ");
		switch (choice) {
		case NEPOZNATO_MOTOR:
		case BENZIN:
		case DIZEL:
		case HIBRID:
		case ELEKTRICNI:
			*engineType = (EngineType)choice;
			break;
		default:
			printf("Neispravan unos.\n");
			choice = -1;
		}
	} while (choice == -1);
}
void inputGearbox(GearboxType* gearboxType) {
	int choice;
	do {
		printf("Odaberite tip mjenjaca:\n");
		printf("0. Nepoznato\n1. Automatski\n2. Rucni\n3. Poluautomatski\n");
		choice = safeInputInt("Vas odabir: ");
		switch (choice) {
		case NEPOZNATO_MJENJAC:
		case AUTOMATSKI:
		case RUCNI:
		case POLUAUTOMATSKI:
			*gearboxType = (GearboxType)choice;
			break;
		default:
			printf("Neispravan unos.\n");
			choice = -1;
		}
	} while (choice == -1);

}

const char* engineTypeToString(EngineType type) {
	switch (type) {
	case NEPOZNATO_MOTOR: return "Nepoznato";
	case BENZIN: return "Benzin";
	case DIZEL: return "Dizel";
	case HIBRID: return "Hibrid";
	case ELEKTRICNI: return "Elektricni";
	default: return "Nepoznato";
	}
}

const char* gearboxTypeToString(GearboxType type) {
	switch (type) {
	case NEPOZNATO_MJENJAC: return "Nepoznato";
	case AUTOMATSKI: return "Automatski";
	case RUCNI: return "Rucni";
	case POLUAUTOMATSKI: return "Poluautomatski";
	default: return "Nepoznato";
	}
}

void printVehicle(const vehicle* v) {
	printf("ID: %-4d | %-15s | %-18s | %6d | %12.2f EUR | %10d km | %-12s | %-14s\n",
		v->id,
		v->make,
		v->model,
		v->year,
		v->price,
		v->mileage,
		engineTypeToString(v->engineType),
		gearboxTypeToString(v->gearboxType)
	);
}

void printAllVehicles(const vehicle* array, int n) {
	printf("%-8s | %-15s | %-18s | %-6s | %-16s | %-13s | %-12s | %-14s\n", "", "Marka", "Model", "God.", "Cijena", "Kilometraza", "Motor", "Mjenjac");
	printf("---------------------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < n; i++) {
		printVehicle(&array[i]);
	}
}

void inputUpdateString(char* dest, int size) {
	if (dest == NULL || size <= 0) {
		return;
	}
	char buffer[128];
	if (fgets(buffer, sizeof(buffer), stdin)) {
		int len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n') {
			buffer[len - 1] = '\0';
		}
		if (strlen(buffer) > 0) {
			strncpy(dest, buffer, size);
		}
	}
}

void inputUpdateInt(int* dest) {
	if (dest == NULL) {
		return;
	}
	char buffer[64];
	int value;
	char extra;

	while(1){
		if (fgets(buffer, sizeof(buffer), stdin)) {
			int len = strlen(buffer);
			if (len > 0 && buffer[len - 1] == '\n') {
				buffer[len - 1] = '\0';
			}
			if (strlen(buffer) == 0) {
				return;
			}
			if (sscanf(buffer, "%d %c", &value, &extra) == 1) {
				if (value < 0) {
					printf("Unos ne moze biti negativan broj! Pokusajte ponovno: ");
					continue;
				}
				*dest = value;
				return;
			}
			else {
				printf("Neispravan Unos! Unesite cijeli broj ili Enter da bi preskocili: ");
			}
		}
	}
}

void inputUpdateFloat(float* dest) {
	if (dest == NULL) {
		return;
	}
	char buffer[64];
	float value;
	char extra;

	while (1) {
		if (fgets(buffer, sizeof(buffer), stdin)) {
			int len = strlen(buffer);
			if (len > 0 && buffer[len - 1] == '\n') {
				buffer[len - 1] = '\0';
			}
			if (strlen(buffer) == 0) {
				return;
			}
			if (sscanf(buffer, "%f %c", &value, &extra) == 1) {
				if (value < 0) {
					printf("Unos ne moze biti negativan broj! Pokusajte ponovno: ");
					continue;
				}
				*dest = value;
				return;
			}
			else {
				printf("Neispravan unos! Unesite decimalni broj ili Enter da bi preskocili: ");
			}
		}
	}
}

void inputUpdateYear(int* dest) {
	if (dest == NULL) {
		return;
	}
	char buffer[64];
	int value;
	char extra;
	while (1) {
		if (fgets(buffer, sizeof(buffer), stdin)) {
			int len = strlen(buffer);
			if (len > 0 && buffer[len - 1] == '\n') {
				buffer[len - 1] = '\0';
			}
				if (strlen(buffer) == 0) {
					return;
				}
				if (sscanf(buffer, "%d %c", &value, &extra) == 1) {
					if (value < 1884 || value > 2025) {
						printf("Neispravan unos!\n");
						continue;
					}
					*dest = value;
					return;
				}
				else {
					printf("Neispravan unos! Unesite vazecu godinu ili Enter da bi preskocili: ");
			}
		}
	}
}

int compareById(const void* a, const void* b) {
	int id1 = ((vehicle*)a)->id;
	int id2 = ((vehicle*)b)->id;
	return id1 - id2;
}

void toLowerString(char* str) {
	while (*str) {
		*str = tolower((unsigned char)*str);
		str++;
	}
}