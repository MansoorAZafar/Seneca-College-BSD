/*
*****************************************************************************
						  Workshop - #3 (Part-1)

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

/*
What this program does is it creates constant variables and determines set information about their properties.
*/

void displayProductInfo() {
	const int pID1 = 111; const int pID2 = 222; const int pID3 = 111; // declaration of product ID's
	const double price1 = 111.49; const double price2 = 222.99; const double price3 = 334.49; // declaration of price for each Product
	const char p1Tax = 'Y';	const char p2Tax = 'N'; const char p3Tax = 'N'; // declaration for product # taxable 
	const double testValue = 330.99; // declaration for the test value
	printf("Product Information\n");
	printf("===================\n");
	printf("Product-1 (ID:%d)\n", pID1); // prints out the ID for the 1st product
	printf("  Taxed: %c\n", p1Tax); // prints out if product 1 is taxable
	printf("  Price: $%.4lf\n\n", price1); // prints out the price for product 1
	printf("Product-2 (ID:%d)\n", pID2); // prints out the ID for the 2nd product
	printf("  Taxed: %c\n", p2Tax); // prints out if product 2 is taxable
	printf("  Price: $%.4lf\n\n", price2); // prints out the price for product 2
	printf("Product-3 (ID:%d)\n", pID3); // prints out the ID for the 3rd product
	printf("  Taxed: %c\n", p3Tax); // prints out if product 1 is taxable
	printf("  Price: $%.4lf\n\n", price3); // prints out the price for product 3

	double avgPrice; // creates a var for the average price
	avgPrice = (price1 + price2 + price3) / 3; // sets the value of the avg price by adding all 3 prices then / by 3
	printf("The average of all prices is: $%.4lf\n\n", avgPrice); // prints out the avg price

	printf("About Relational and Logical Expressions!\n");
	printf("========================================\n");
	printf("1. These expressions evaluate to TRUE or FALSE\n2. FALSE: is always represented by integer value 0\n3. TRUE : is represented by any integer value other than 0\n\n");
	printf("Some Data Analysis...\n");
	printf("=====================\n");
	printf("1. Is product 1 taxable? -> %d\n\n",
		p1Tax == 'Y' || p1Tax == 'N'); // checks if product # 1 taxable is Y or N
	printf("2. Are products 2 and 3 both NOT taxable (N)? -> %d\n\n",
		p2Tax == 'N' && p3Tax == 'N'); // checks if product # 2 && product # 3 taxable is N
	printf("3. Is product 3 less than testValue ($%.2lf)? -> %d\n\n", testValue,
		price3 < testValue); // checks if product 3 is less than the testvalue
	printf("4. Is the price of product 3 more than both product 1 and 2 combined? -> %d\n\n",
		price3 > (price1 + price2)); // checks if the price of product # 3 is more than product # 1 added onto product # 2
	printf("5. Is the price of product 1 equal to or more than the price difference\n");
        printf("   of product 3 LESS product 2? ->  %d",
		price1 >= (price3 - price2)); printf(" (price difference: $%.2lf)\n\n", (price3 - price2)); // checks if price of product # 1 is greater than the price difference between # 3 & # 2
	printf("6. Is the price of product 2 equal to or more than the average price? -> %d\n\n",
		price2 >= avgPrice); // checks if the 2nd product price is greater or equal to than the average price
	printf("7. Based on product ID, product 1 is unique -> %d\n\n",
		!(pID1 == pID2) && !(pID1 == pID3)); // prints out if the first product's ID is unique
	printf("8. Based on product ID, product 2 is unique -> %d\n\n",
		!(pID2 == pID1) && !(pID2 == pID3)); // prints out if the 2nd product's ID is unique
	printf("9. Based on product ID, product 3 is unique -> %d\n",
		!(pID3 == pID2) && !(pID3 == pID1)); // prints out if the 3rd product's ID is unique
}

int main(void) {
	displayProductInfo();
	return 0;
}

