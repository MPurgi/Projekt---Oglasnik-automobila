#pragma once
#include <stdio.h>

#define MAX_MARKA 32
#define MAX_MODEL 32
#define MAX_MOTOR 16
#define MAX_MJENJAC 16
#define PAUSE() do{printf("Pritisnite Enter za nastavak.\n");clearInputBuffer(); }while(0)


typedef struct {
	int id;
	char make[MAX_MARKA];
	char model[MAX_MODEL];
	int year;
	char engine[MAX_MOTOR];
	char gearbox[MAX_MJENJAC];
	int mileage;
	float price;
}vehicle;

extern int numOfVehicles;

void printMenu(void);
void createListing(vehicle** array, int* n);
vehicle* loadVehicles(int *n);
void showListings(vehicle* array, int n);
void updateListing(vehicle* array, int n);
vehicle* deleteListing(vehicle* array, int* n);
void saveVehicles(vehicle* array, int n, const char* filename);
void freeVehicles(vehicle** array);
void sortVehiclesByPrice(vehicle* array, int n);
static inline void clearInputBuffer(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
int confirmExit(void);
void pause(void);
int getMaxId(vehicle* array, int n);
void printFileSize(const char* filename);
void deleteFile(void);
void renameFile(void);
void searchByMake(vehicle* array, int n);

static inline int safeInputInt(const char* prompt) {
	int value;
	char end;
	while (1) {
		printf("%s", prompt);
		if (scanf("%d%c", &value, &end) == 2 && end == '\n') {
			return value;
		}
		else {
			printf("Neispravan unos!");
			clearInputBuffer();
		}
	}
}

static inline float safeInputFloat(const char* prompt) {
	float value;
	char end;
	while (1) {
		printf("%s", prompt);
		if (scanf("%f%c", &value, &end) == 2 && end == '\n') {
			return value;
		}
		else {
			printf("Neispravan unos!");
			clearInputBuffer();
		}
	}
}

static inline void safeInputString(const char* prompt, char* buffer, int size) {
	printf("%s", prompt);
	if (fgets(buffer, size, stdin) != NULL) {
		buffer[strcspn(buffer, "\n")] = 0;
	}
}