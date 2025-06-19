#pragma once
#include <stdio.h>
#include "enums.h"

#define MAX_MARKA 32
#define MAX_MODEL 32
#define MAX_MOTOR 16
#define MAX_MJENJAC 16
#define PAUSE() do{printf("Pritisnite Enter za nastavak.\n");clearInputBuffer(); CLEAR_SCREEN();}while(0)
#define CLEAR_SCREEN() printf("\033[2J\033[1;1H")

typedef struct {
	int id;
	char make[MAX_MARKA];
	char model[MAX_MODEL];
	int year;
	EngineType engineType;
	GearboxType gearboxType;
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
int confirmExit(void);
int getMaxId(vehicle* array, int n);
void printFileSize(const char* filename);
void deleteFile(void);
void renameFile(void);
void searchByMake(vehicle* array, int n);
void inputEngine(EngineType* engineType);
void inputGearbox(GearboxType* gearboxType);
const char* engineTypeToString(EngineType type);
const char* gearboxTypeToString(GearboxType type);
void printVehicle(const vehicle* v);
void printAllVehicles(const vehicle* array, int n);
void inputUpdateString(char* dest, int size);
void inputUpdateInt(int* dest);
void inputUpdateFloat(float* dest);
void inputUpdateYear(int* dest);
int compareById(const void* a, const void* b);
void toLowerString(char* str);