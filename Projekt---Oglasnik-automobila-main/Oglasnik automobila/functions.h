#pragma once
#include <stdio.h>

typedef struct {
	char make[30];
	char model[30];
	//int kilometraza
	int year;
	char engine[20];
	char gearbox[20];
	float price;
}vehicle;

void loadVehicles();
void saveVehicles();
void createListing();
void showListings();
void searchListing();
void updateListing();
void deleteListing();
void clearInputBuffer();
int confirmExit();
void pause();