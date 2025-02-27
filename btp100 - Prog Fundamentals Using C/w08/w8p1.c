/*
*****************************************************************************
						  Workshop - #8 (P1)
Full Name  : Mansoor Ahmad Zafar
Student ID#: 100503226
Email      : mzafar15@myseneca.ca
Section    : NBB
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS
//#include "yeah.c"
#include "w8p1.h"

// System Libraries

#include <stdio.h>

// User Libraries


// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

int getIntPositive(int* a) {
	int num = 0;
	int* x = a;
	scanf("%d", &num);
	//printf("\n\nUM IS %d\n\n", num);
	do {
		if (num <= 0) {
			printf("ERROR: Enter a positive value: ");
			scanf("%d", &num);
		}
		//printf("\n\nUM IS %d\n\n", num);
	} while (num <= 0);
	if (a != NULL) {
		*x = num;
	}
	return num;
}

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

double getDoublePositive(double* a) {
	double num = 0;
	double* x = a;
	scanf("%lf", &num);
	//printf("\n\nUM IS %d\n\n", num);
	do {
		if (num <= 0) {
			printf("ERROR: Enter a positive value: ");
			scanf("%lf", &num);
		}
		//printf("\n\nUM IS %d\n\n", num);
	} while (num <= 0);
	if (a != NULL) {
		*x = num;
	}
	return num;
}

// 3. Opening Message (include the number of products that need entering)

void openingMessage() {

	printf("Cat Food Cost Analysis\n");
	printf("======================\n\n"
		"Enter the details for %d dry food bags of product data for analysis.\n"
		"NOTE: A 'serving' is %dg\n\n", maxNumOfProd, numOfGrams);
}

// 4. Get user input for the details of cat food product


CatFoodInfo getCatFoodInfo(CatFoodInfo cfi[maxNumOfProd]) {

	int i;
	for (i = 0; i < maxNumOfProd; i++) {

		printf("Cat Food Product #%d\n", i + 1);
		printf("--------------------\n");
		printf("SKU           : ");
		//Take input		  
		scanf("%d", &cfi[i].sku);
		//Validation		  
		while (cfi[i].sku <= 0) {
			printf("ERROR: Enter a positive value: ");
			scanf("%d", &cfi[i].sku);
		}

		printf("PRICE         : $");
		//Take input		  
		scanf("%lf", &cfi[i].price);
		//Validation		  
		while (cfi[i].price <= 0) {
			printf("ERROR: Enter a positive value: ");
			scanf("%lf", &cfi[i].price);
		}

		printf("WEIGHT (LBS)  : ");
		//Take input		  
		scanf("%lf", &cfi[i].lbs);
		//Validation		  
		while (cfi[i].lbs <= 0) {
			printf("ERROR: Enter a positive value: ");
			scanf("%lf", &cfi[i].lbs);
		}

		printf("CALORIES/SERV.: ");
		//Take input		  
		scanf("%d", &cfi[i].calories);
		//Validation		  
		while (cfi[i].calories <= 0) {
			printf("ERROR: Enter a positive value: ");
			scanf("%d", &cfi[i].calories);
		}
		printf("\n");
	}

	displayCatFoodHeader();
	displayCatFoodData(cfi);

	return cfi[0];

}

// 5. Display the formatted table header
void displayCatFoodHeader(void)
{
	printf("SKU         $Price    Bag-lbs Cal/Serv\n");
	printf("------- ---------- ---------- --------\n");
}

// 6. Display a formatted record of cat food data

void displayCatFoodData(CatFoodInfo cfiArr[]) {
	//SENDING IN AN ARRAY OF STRUCTURES 
	int i = 0;
	for (i = 0; i < maxNumOfProd; i++) {
		printf("%07d %10.2lf %10.1lf %8d\n", cfiArr[i].sku, cfiArr[i].price, cfiArr[i].lbs, cfiArr[i].calories);
	}
}

// 7. Logic entry point
void start() {
	CatFoodInfo cfi[maxNumOfProd];
	openingMessage();
	getCatFoodInfo(cfi);
}

