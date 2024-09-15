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

//Macros
#define maxNumOfProd 3
#define numOfGrams 64
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

CatFoodInfo getCatFoodInfo(CatFoodInfo cfi[maxNumOfProd]);

// 5. Display the formatted table header

void displayCatFoodHeader(void);

// 6. Display a formatted record of cat food data

void displayCatFoodData(CatFoodInfo cfiArr[]);

// 7. Logic entry point
void start();
