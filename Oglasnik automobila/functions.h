#pragma once
#include <stdio.h>

#define MAX_MARKA 32
#define MAX_MODEL 32
#define MAX_MOTOR 16
#define MAX_MJENJAC 16

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
void deleteListing(vehicle** array, int* n);
void saveVehicles(vehicle* array, int n, const char* filename);
void freeVehicles(vehicle* array);
void sortVehiclesByPrice(vehicle* array, int n);
//void removeDataFile();
void clearInputBuffer(void);
int confirmExit(void);
void pause(void);