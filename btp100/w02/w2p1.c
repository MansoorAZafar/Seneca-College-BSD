/*
*****************************************************************************
						  Workshop - #2 (Part-1)

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
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
//calculates the subtotal, taxes + total
//prints out the final statement
void shoppingCart(int boughtShirts, int priceSmallShirt, double TAX) {
	// takes in the amount of shirts sold and the price of the small shirt
	int subTotal = priceSmallShirt * boughtShirts; // calculates the sub-total by multiplying the amount of shirts sold by the price of the small shirts
	int taxes = (int)((subTotal * TAX - subTotal) + 0.5); // calculates the taxes by taking the subtotal times the tax and subtracting the subtotal 
	int total = subTotal + taxes; // calculates the total price through addition of the subtotal and the taxes
	printf("\nPatty's shopping cart...\nContains : %d shirts\nSub-total: $%8.4lf\nTaxes    : $%8.4lf\nTotal    : $%8.4lf", boughtShirts, (float)subTotal / 100, (float)taxes / 100, (float)total / 100);
	printf("\n");
}
//lists the shirt prices
void shirtStorePrices(int smallShirt, int mediumShirt, int largeShirt) {
	// takes in the small, medium and large shirt prices
	printf("\nShirt Store Price List\n");
	printf("======================");
	printf("\nSMALL  : $%.2lf", (float)smallShirt / 100); // prints out the small shirt price with 2 decimals
	printf("\nMEDIUM : $%.2lf", (float)mediumShirt / 100); // prints out the medium shirt price with 2 decimals
	printf("\nLARGE  : $%.2lf", (float)largeShirt / 100); // prints out the large shirt price with 2 decimals

}
//sets the prices of the shirts
void setShirtPrices() {
	double smallShirtPriceTemp, mediumShirtPriceTemp, largeShirtPriceTemp;
	int smallShirtPrice, mediumShirtPrice, largeShirtPrice, shirtsSoldPat; // int's to hold the value of prices of the small, medium, large shirts and the amount of shirts sold
	printf("Enter the price for a SMALL shirt: $");
	scanf("%lf", &smallShirtPriceTemp); // takes in the price of the small shirt
	smallShirtPrice = (int)(smallShirtPriceTemp * 100 + 0.5); // converts the double to int
	printf("Enter the price for a MEDIUM shirt: $");
	scanf("%lf", &mediumShirtPriceTemp); // takes in the price of the medium shirt
	printf("Enter the price for a LARGE shirt: $");
	mediumShirtPrice = (int)(mediumShirtPriceTemp * 100 + 0.5); // converts the double to int
	scanf("%lf", &largeShirtPriceTemp); // takes in the price of the large shirt
	largeShirtPrice = (int)(largeShirtPriceTemp * 100 + 0.5); // converts double to int
	shirtStorePrices(smallShirtPrice, mediumShirtPrice, largeShirtPrice); // runs the shirt store prices functions
	const char patSize = 'S'; // pat's size

	printf("\n\nPatty's shirt size is '%c'\nNumber of shirts Patty is buying: ", patSize); // prints out a statement
	scanf("%d", &shirtsSoldPat); // takes in how many shirts were sold
	const double TAX = 1.13; // tax cost
	shoppingCart(shirtsSoldPat, smallShirtPrice, TAX); // runs the shopping cart function with the shirts sold and small shirt price as parentheses
	//printf("The price for a small shirt is : %.2lf", (float)smallShirtPrice/100);
}

void shirtStore() {
	printf("Set Shirt Prices\n"); // prints out a word statement
	printf("================\n"); // prints out "=" 
	setShirtPrices(); // sets the shirts prices
}

int main(void) {
	shirtStore(); // runs the shirtStore function
	return 0; // returns 0 due to int function
}





//Quick note, if they want to show all 4 decimals change .2lf to 8.4lf


