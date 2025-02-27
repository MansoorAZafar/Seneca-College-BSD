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
#include "w8p2.h"

// System Libraries

#include <stdio.h>

// User Libraries


// ----------------------------------------------------------------------------
// PART-1


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

// 4. Get user input for the details of cat food product + {ADDED: also sets the basic values for reportdata array}

CatFoodInfo getCatFoodInfo(CatFoodInfo cfi[maxNumOfProd], ReportData rp[maxNumOfProd]) {

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
		rp[i].sku = cfi[i].sku;

		printf("PRICE         : $");
		//Take input		  
		scanf("%lf", &cfi[i].price);
		//Validation		  
		while (cfi[i].price <= 0) {
			printf("ERROR: Enter a positive value: ");
			scanf("%lf", &cfi[i].price);
		}
		rp[i].price = cfi[i].price;

		printf("WEIGHT (LBS)  : ");
		//Take input		  
		scanf("%lf", &cfi[i].lbs);
		//Validation		  
		while (cfi[i].lbs <= 0) {
			printf("ERROR: Enter a positive value: ");
			scanf("%lf", &cfi[i].lbs);
		}
		rp[i].lbs = cfi[i].lbs;

		printf("CALORIES/SERV.: ");
		//Take input		  
		scanf("%d", &cfi[i].calories);
		//Validation		  
		while (cfi[i].calories <= 0) {
			printf("ERROR: Enter a positive value: ");
			scanf("%d", &cfi[i].calories);
		}
		rp[i].calories = cfi[i].calories;

		printf("\n");
	}

	displayCatFoodHeader();
	displayCatFoodData(cfi);
	calculateReportData(rp);
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

// ----------------------------------------------------------------------------
// PART-2

// 8. convert lbs: kg (divide by 2.20462)
	
double convertLbsKg(double* x, double* y) {
	double num;
	num = *x / lbsToKG;
	if (y != NULL) {
		*y = num;
	}
	return num;
}

// 9. convert lbs: g (call convertKG, then * 1000)

int convertLbsG(double* x, int* y) {
	int num = 0;
	num = (int)(*x / lbsToKG * 1000);
	if (y != NULL) {
		*y = num;
	}
	return num;
}

// 10. convert lbs: kg and g

void convertLbs(double* x, double* y, int* z) {
	int num = 0;
	double num2 = 0;
	num = (int)(*x / lbsToKG * 1000);
	if (z != NULL) {
		*z = num;
		num2 = (*x / lbsToKG);
		*y = num2;
	}
}

// 11. calculate: servings based on gPerServ

double calculateServings(int grams) {
	double totalServing = ((double)grams/numOfGrams);
	return totalServing;
}

// 12. calculate: cost per serving

double calculateCostPerServing(double price, double serving) {
	double costPerServing = price / serving;
	return costPerServing;
}

// 13. calculate: cost per calorie

double calculateCostPerCal(double pricePerServing, int calories) {
	double costPerCal = pricePerServing / calories;
	return costPerCal;
}

// 14. Derive a reporting detail record based on the cat food product data

ReportData calculateReportData(ReportData rp[maxNumOfProd]) {
	int i = 0;
	for (i = 0; i < maxNumOfProd; i++) {
		rp[i].grams = (int)(rp[i].lbs / lbsToKG * 1000); // sets grams
		rp[i].totalServing = calculateServings(rp[i].grams); // sets the serving amount total
		rp[i].kg = rp[i].lbs / lbsToKG; // sets the kg
		rp[i].pricePerServing = calculateCostPerServing(rp[i].price, rp[i].totalServing); // sets the price per serving
		rp[i].pricePerCalories = calculateCostPerCal(rp[i].pricePerServing, rp[i].calories); // sets the price per calories
	}
	printf("\n");
	displayReportHeader();
	displayReportData(rp);

	return rp[0];
}

// 15. Display the formatted table header for the analysis results
void displayReportHeader(void)
{
	printf("Analysis Report (Note: Serving = %dg)\n", numOfGrams);
	printf("---------------\n");
	printf("SKU         $Price    Bag-lbs     Bag-kg     Bag-g Cal/Serv Servings  $/Serv   $/Cal\n");
	printf("------- ---------- ---------- ---------- --------- -------- -------- ------- -------\n");
}

// 16. Display the formatted data row in the analysis table

void displayReportData(ReportData rp[maxNumOfProd]) {
	int i = 0;
	int lowestPricePosition = 0;
	double price = rp[0].pricePerCalories;
	for (i = 0;i < maxNumOfProd;i++) {
		if (price > rp[i].pricePerCalories) {
			price = rp[i].pricePerCalories;	
			lowestPricePosition = i;

		}
		else {
		}
	}
	i = 0;
	while (i != 3) {
		printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf", rp[i].sku, rp[i].price, rp[i].lbs, rp[i].kg,
			rp[i].grams, rp[i].calories, rp[i].totalServing, rp[i].pricePerServing, rp[i].pricePerCalories);
		if (i == lowestPricePosition) {
			printf(" ***");
		}
		printf("\n");
		i++;
	}
	displayFinalAnalysis(rp, lowestPricePosition);
}

// 17. Display the findings (cheapest)

void displayFinalAnalysis(ReportData rp[maxNumOfProd], int pos) {
	printf("\nFinal Analysis");
	printf("\n--------------\n"
	"Based on the comparison data, the PURRR-fect economical option is:\n"
	"SKU:00%d Price: $%.2lf\n\n", rp[pos].sku, rp[pos].price);
	printf("Happy shopping!\n");
}


// ----------------------------------------------------------------------------


// 7. Logic entry point
void start() {
	CatFoodInfo cfi[maxNumOfProd];
	ReportData rp[maxNumOfProd];
	openingMessage();
	getCatFoodInfo(cfi, rp);
	//PART 2
}

