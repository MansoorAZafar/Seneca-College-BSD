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

//Note for my program: I take the prices of the shirts as a double and convert them to integer
// in print statements I convert the integer to a float
//EX. Enter the price of the small Shirt: 12.55
//My program will change 12.55 to 1255 and use that number for calculations.


void line() {
	printf("\n"); // makes a new line (thats it)
}
//TOTAL IS TAKEN AS A FULL INT EX. 12.55 IS TAKEN AS 1255
void cashRegTax(int total, int totalShirtsBought) {
	//declaration of variables
	int coins, numOfToon, balanceToon, numOfLoon, balanceLoon, numOfQuar, balanceQuar, numOfDime, balanceDime, numOfNick, balanceNick, numOfPenn, balancePen;
	coins = total; // initalization of coin variable
	numOfToon = coins / 200; // calculates how many toonies are needed by subtracting # of coins by the value of 200
	coins = coins - (numOfToon * 200); // reduces the total coins by how many toonies were inide
	balanceToon = (int)((total % 200) + 0.5);// caluclates the "balance" for the toonies 
	numOfLoon = coins / 100; // repeats the same process for toonies but for loonies
	coins = coins - (numOfLoon * 100);
	balanceLoon = (int)((total % 100) + 0.5);
	numOfQuar = coins / 25; // repeats same process as toonies but for quarters
	coins = coins - (numOfQuar * 25);
	balanceQuar = (int)((total % 25) + 0.5);
	numOfDime = coins / 10; // repeats same process as toonies but for dimes
	coins = coins - (numOfDime * 10);
	balanceDime = (int)((total % 10) + 0.5);
	numOfNick = coins / 5; // repeats same process for toonies but for nickles
	coins = coins - (numOfNick * 5);
	balanceNick = (int)((total % 5) + 0.5);
	numOfPenn = coins / 1; // repeats same process for toonies but for pennies
	coins = coins - (numOfPenn * 1);
	balancePen = (int)((total % 1) + 0.5);
	line(); line(); // makes 2 lines
	printf("Sales INCLUDING tax\n");
	printf("Coin     Qty   Balance\n");
	printf("-------- --- ---------\n");
	printf("              %8.4lf\n", (float)total / 100); // prints out the total by converting it from int to float
	printf("Toonies  %3d %9.4lf\n", numOfToon, (float)balanceToon / 100); // converts the balance to float + prints out toony info
	printf("Loonies  %3d %9.4lf\n", numOfLoon, (float)balanceLoon / 100); // convets the balance to float + prints out loonie info
	printf("Quarters %3d %9.4lf\n", numOfQuar, (float)balanceQuar / 100); // converts the balance to float + prints out quarter info
	printf("Dimes    %3d %9.4lf\n", numOfDime, (float)balanceDime / 100); // converts the balance to float + prints out dime info
	printf("Nickels  %3d %9.4lf\n", numOfNick, (float)balanceNick / 100); // converts the balance to float + prints out nickle info
	printf("Pennies  %3d %9.4lf\n", numOfPenn, (float)balancePen / 100); // converts the balance to float + prints out pennies info

	line(); // prints out an empty line
	printf("Average cost/shirt: $%.4lf", ((float)total / 100 / totalShirtsBought)); // prints out the avg shirt price
	// avg shirt formula is total cost / total # of shirts bought 
}

//DOES THE SAME THING AS cashRegTax BUT WITH subTotal INSTEAD OF TOTAL 
//COMMENTS ARE THERE
//subTotal IS TAKEN AS INT EX. 12.55 --> 1255
void cashRegNoTax(int subTotal, int totalShirtsBought) {
	//declaraction of variables
	int coins, numOfToon, balanceToon, numOfLoon, balanceLoon, numOfQuar, balanceQuar, numOfDime, balanceDime, numOfNick, balanceNick, numOfPenn, balancePen;
	coins = subTotal; // makes coins equal to the subtotal
	numOfToon = coins / 200; // does the same as in cashRegTax but with subTotal instead of total
	coins = coins - (numOfToon * 200);
	balanceToon = (int)((subTotal % 200) + 0.5);// / 1000;
	numOfLoon = coins / 100;
	coins = coins - (numOfLoon * 100);
	balanceLoon = (int)((subTotal % 100) + 0.5);
	numOfQuar = coins / 25;
	coins = coins - (numOfQuar * 25);
	balanceQuar = (int)((subTotal % 25) + 0.5);
	numOfDime = coins / 10;
	coins = coins - (numOfDime * 10);
	balanceDime = (int)((subTotal % 10) + 0.5);
	numOfNick = coins / 5;
	coins = coins - (numOfNick * 5);
	balanceNick = (int)((subTotal % 5) + 0.5);
	numOfPenn = coins / 1;
	coins = coins - (numOfPenn * 1);
	balancePen = (int)((subTotal % 1) + 0.5);
	line(); line();
	printf("Daily retail sales represented by coins\n");
	printf("=======================================\n\n");
	printf("Sales EXCLUDING tax\n");
	printf("Coin     Qty   Balance\n");
	printf("-------- --- ---------\n");
	printf("              %8.4lf\n", (float)subTotal / 100);
	printf("Toonies  %3d %9.4lf\n", numOfToon, (float)balanceToon / 100);
	printf("Loonies  %3d %9.4lf\n", numOfLoon, (float)balanceLoon / 100);
	printf("Quarters %3d %9.4lf\n", numOfQuar, (float)balanceQuar / 100);
	printf("Dimes    %3d %9.4lf\n", numOfDime, (float)balanceDime / 100);
	printf("Nickels  %3d %9.4lf\n", numOfNick, (float)balanceNick / 100);
	printf("Pennies  %3d %9.4lf\n", numOfPenn, (float)balancePen / 100);

	line();
	printf("Average cost/shirt: $%.4lf", ((float)subTotal / 100 / totalShirtsBought));
}

//calculates the subtotal, taxes + total
//prints out the final statement
void shoppingCart(double tax, int patShirtNum, int tomShirtNum, int salShirtNum, int smlShirt, int medShirt, int larShirt) {
	// takes in the amount of shirts sold and the price of the small shirt
	int subTotalPat = smlShirt * patShirtNum; // calculates the sub-total by multiplying the amount of shirts sold by the price of the small shirts
	int taxesPat = (int)((subTotalPat * tax - subTotalPat) + 0.5); // calculates the taxes by taking the subtotal times the tax and subtracting the subtotal 
	int totalPat = subTotalPat + taxesPat; // calculates the total price through addition of the subtotal and the taxes

	int subTotalTom = larShirt * tomShirtNum; // calculates the sub-total by multiplying the amount of shirts sold by the price of the small shirts
	int taxesTom = (int)((subTotalTom * tax - subTotalTom) + 0.5); // calculates the taxes by taking the subtotal times the tax and subtracting the subtotal 
	int totalTom = subTotalTom + taxesTom; // calculates the total price through addition of the subtotal and the taxes

	int subTotalSal = medShirt * salShirtNum; // calculates the sub-total by multiplying the amount of shirts sold by the price of the small shirts
	int taxesSal = (int)((subTotalSal * tax - subTotalSal) + 0.5); // calculates the taxes by taking the subtotal times the tax and subtracting the subtotal 
	int totalSal = subTotalSal + taxesSal; // calculates the total price through addition of the subtotal and the taxes

	int subTotal = subTotalPat + subTotalSal + subTotalTom; // adds up all the totals
	int taxes = (int)(taxesPat + taxesSal + taxesTom + 0.5); // adds up all the taxes into an int
	int total = (int)totalPat + totalSal + totalTom; // adds up all totals into an int

	int totalShirtsBought = patShirtNum + salShirtNum + tomShirtNum; // addes up the total # of shirts bought

	printf("Customer Size Price Qty Sub-Total       Tax     Total\n");
	printf("-------- ---- ----- --- --------- --------- ---------\n");
	printf("Patty    S    %.2lf   %d  %8.4lf  %8.4lf  %8.4lf", (float)smlShirt / 100, patShirtNum, (float)subTotalPat / 100, (float)taxesPat / 100, (float)totalPat / 100);
	printf("\nSally    M    %.2lf   %d  %8.4lf  %8.4lf  %8.4lf", (float)medShirt / 100, salShirtNum, (float)subTotalSal / 100, (float)taxesSal / 100, (float)totalSal / 100);
	printf("\nTommy    L    %.2lf   %d  %8.4lf  %8.4lf  %8.4lf", (float)larShirt / 100, tomShirtNum, (float)subTotalTom / 100, (float)taxesTom / 100, (float)totalTom / 100);
	printf("\n-------- ---- ----- --- --------- --------- ---------\n");
	printf("%33.4lf %9.4lf %9.4lf", (float)subTotal / 100, (float)taxes / 100, (float)total / 100); // converts the subTotal, taxes + total into int's
	cashRegNoTax(subTotal, totalShirtsBought); // sends the subTotal and total # of shirts bought to the no tax cash reg
	cashRegTax(total, totalShirtsBought); // sends the total amount + total # of shirts bought to the cash reg with tax
}

//collects all info needed for the shopping cart then passing it to the cart
void infoCollector(double tax, int patShirtNum, int tomShirtNum, int salShirtNum, int smlShirt, int medShirt, int larShirt) {
	shoppingCart(tax, patShirtNum, tomShirtNum, salShirtNum, smlShirt, medShirt, larShirt);
	//TAX, shirtsSoldPat, shirtsSoldTom, shirtsSoldSal, smallShirtPrice, mediumShirtPrice, largeShirtPrice
}

//sets the prices of the shirts

void setShirtPrices() {
	//Declaration of variables
	double smallShirtPriceTemp, mediumShirtPriceTemp, largeShirtPriceTemp;
	int smallShirtPrice, mediumShirtPrice, largeShirtPrice, shirtsSoldPat, shirtsSoldSal, shirtsSoldTom; // int's to hold the value of prices of the small, medium, large shirts and the amount of shirts sold
	printf("Enter the price for a SMALL shirt: $");
	scanf("%lf", &smallShirtPriceTemp); // takes in the price of the small shirt
	smallShirtPrice = (int)(smallShirtPriceTemp * 100 + 0.5); // converts the double to int
	printf("Enter the price for a MEDIUM shirt: $");
	scanf("%lf", &mediumShirtPriceTemp); // takes in the price of the medium shirt
	printf("Enter the price for a LARGE shirt: $");
	mediumShirtPrice = (int)(mediumShirtPriceTemp * 100 + 0.5); // converts the double to int
	scanf("%lf", &largeShirtPriceTemp); // takes in the price of the large shirt
	largeShirtPrice = (int)(largeShirtPriceTemp * 100 + 0.5); // converts double to int

	//shirtStorePrices(smallShirtPrice, mediumShirtPrice, largeShirtPrice); // runs the shirt store prices functions
	printf("\nShirt Store Price List");
	printf("\n======================");
	printf("\nSMALL  : $%.2lf", (float)smallShirtPrice / 100); // prints out the small shirt price with 2 decimals
	printf("\nMEDIUM : $%.2lf", (float)mediumShirtPrice / 100); // prints out the medium shirt price with 2 decimals
	printf("\nLARGE  : $%.2lf", (float)largeShirtPrice / 100); // prints out the large shirt price with 2 decimals

	const char patSize = 'S'; // pat's size
	const char salSize = 'M';
	const char tomSize = 'L';

	printf("\n\nPatty's shirt size is '%c'\nNumber of shirts Patty is buying: ", patSize); // prints out a statement
	scanf("%d", &shirtsSoldPat); // takes in how many shirts were sold

	printf("\nTommy's shirt size is '%c'\nNumber of shirts Tommy is buying: ", tomSize); // prints out a statement
	scanf("%d", &shirtsSoldTom); // takes in how many shirts were sold

	printf("\nSally's shirt size is '%c'\nNumber of shirts Sally is buying: ", salSize); // prints out a statement
	scanf("%d", &shirtsSoldSal); // takes in how many shirts were sold

	const double TAX = 1.13; // tax cost

	printf("\n");
	infoCollector(TAX, shirtsSoldPat, shirtsSoldTom, shirtsSoldSal, smallShirtPrice, mediumShirtPrice, largeShirtPrice);
	printf("\n");

	//shoppingCart(shirtsSoldPat, smallShirtPrice, TAX); // runs the shopping cart function with the shirts sold and small shirt price as parentheses
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


