/*
*****************************************************************************
						  Workshop - #8 (P2)
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

//Macros
#define maxNumOfProd 3
#define numOfGrams 64
#define lbsToKG 2.20462
//#define openingMessage(maxNumOfProd, numOfGrams)
#include <stdio.h>

//#include "Header.c"

// ----------------------------------------------------------------------------
// structures

typedef struct {

	int sku;
	double price;
	int calories;
	double lbs;

} CatFoodInfo;

typedef struct{
	int sku;
	double price;
	int calories;
	double lbs;
	double kg;
	int grams;
	double totalServing;
	double pricePerServing;
	double pricePerCalories;
} ReportData;


// ----------------------------------------------------------------------------
// function prototypes

// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

int getIntPositive(int* num);

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)

double getDoublePositive(double* num);

// 3. Opening Message (include the number of products that need entering)

void openingMessage();

// 4. Get user input for the details of cat food product

CatFoodInfo getCatFoodInfo(CatFoodInfo cfi[maxNumOfProd], ReportData rp[maxNumOfProd]);

// 5. Display the formatted table header

void displayCatFoodHeader(void);

// 6. Display a formatted record of cat food data

void displayCatFoodData(CatFoodInfo cfiArr[]);

// ----------------------------------------------------------------------------
// PART-2

// 8. convert lbs: kg

double convertLbsKg(double* x, double* y);

// 9. convert lbs: g

int convertLbsG(double* x, int* y);

// 10. convert lbs: kg / g

void convertLbs(double* x, double* y, int* z);

// 11. calculate: servings based on gPerServ

double calculateServings(int grams);

// 12. calculate: cost per serving

double calculateCostPerServing(double price, double serving);

// 13. calculate: cost per calorie

double calculateCostPerCal(double pricePerServing, int calories);

// 14. Derive a reporting detail record based on the cat food product data

ReportData calculateReportData(ReportData rp[maxNumOfProd]);

// 15. Display the formatted table header for the analysis results

void displayReportHeader(void);

// 16. Display the formatted data row in the analysis table

void displayReportData(ReportData rp[maxNumOfProd]);

// 17. Display the findings (cheapest)

void displayFinalAnalysis(ReportData rp[maxNumOfProd], int pos);

// ----------------------------------------------------------------------------


// 7. Logic entry point
void start();

