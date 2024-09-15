#define _CRT_SECURE_NO_WARNINGS
/*
*****************************************************************************
						  Workshop - #6 (P1)
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
#define MAX_LENGTH 10
#include <stdio.h>

void printChart(double items[], int need[], char yesno[], int numberOfItems) {
	printf("Item Priority Financed        Cost\n");
	printf("---- -------- -------- -----------\n");
	int i = 0;
	for (i = 0; i < numberOfItems; i++) {
		printf("%3d  %5d    %5c    %11.2lf\n", i+1, need[i], yesno[i], items[i]);
	}
	printf("---- -------- -------- -----------\n");
	double finalCost = 0;
	for (i = 0; i < numberOfItems; i++) {
		finalCost += items[i];
	}
	printf("                      $%11.2lf\n\n", finalCost);
	printf("Best of luck in all your future endeavours!\n");
}

void itemDetails(double monthlyNETIncome, int numOfItems) {
	double items[MAX_LENGTH];
	int priority[MAX_LENGTH];
	char financed[MAX_LENGTH];
	const double minCost = 100.00;
	int i = 0;
	for (i = 0; i < numOfItems; i++) {
		double itemCost;
		printf("Item-%d Details:\n   Item cost: $", (i+1));
		scanf("%lf", &itemCost);
		int valid = 0;
		while (valid != 1) {
			if (itemCost < minCost ) {
				printf("      ERROR: Cost must be at least $%.2lf", minCost);
				printf("\n   Item cost: $");
				scanf("%lf", &itemCost);
			}
			else {
				items[i] = itemCost;
				//valid = 1;
				// it means the value of items cost is valid
				int need;
				printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
				scanf("%d", &need);
				while (valid != 1) {
					if (need < 1 || need > 3) {
						printf("      ERROR: Value must be between 1 and 3\n");
						printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
						scanf("%d", &need);
					}
					else {
						priority[i] = need;
						char answer;
						printf("   Does this item have financing options? [y/n]: ");
						scanf(" %c", &answer);
						while (valid != 1) {
							if (answer == 'y' || answer == 'n') {
								financed[i] = answer;
								valid = 1;
							}
							else {
								printf("      ERROR: Must be a lowercase 'y' or 'n'\n");
								printf("   Does this item have financing options? [y/n]: ");
								scanf(" %c", &answer);
							}
						}
					}
				}
			}
		}
		valid = 0;
		printf("\n");
	}
	printChart(items, priority, financed, numOfItems);
}

void wishList(double monthlyNETIncome) {
	const int minItems = 1; const int maxItems = 10;
	printf("\nHow many wish list items do you want to forecast?: ");
	int numOfItems;
	scanf("%d", &numOfItems);
	int valid = 0;
	while (valid != 1) {
		if (numOfItems < minItems || numOfItems > maxItems) {
			printf("ERROR: List is restricted to between 1 and 10 items.");
			printf("\n\nHow many wish list items do you want to forecast?: ");
			scanf("%d", &numOfItems);
		}
		else {
			valid = 1;
		}
	}
	printf("\n");
	itemDetails(monthlyNETIncome, numOfItems);
}

void netIncome() {
	printf("+--------------------------+\n");
	printf("+   Wish List Forecaster   |\n");
	printf("+--------------------------+\n\n");
	printf("Enter your monthly NET income: $");
	const double minIncome = 500.00; const double maxIncome = 400000.00;
	double monthlyNETIncome;
	scanf("%lf", &monthlyNETIncome);
	char valid = 'F';
	while (valid == 'F') {
		if (monthlyNETIncome < minIncome) {
			printf("ERROR: You must have a consistent monthly income of at least $%.2lf", minIncome);
			printf("\n\nEnter your monthly NET income: $");
			scanf("%lf", &monthlyNETIncome);
		}
		else if(monthlyNETIncome > maxIncome) {
			printf("ERROR: Liar! I'll believe you if you enter a value no more than $%.2lf", maxIncome);
			printf("\n\nEnter your monthly NET income: $");
			scanf("%lf", &monthlyNETIncome);
		}
		else {
			valid = 'T';
		}
	}
	wishList(monthlyNETIncome);
}

int main(void) {
	netIncome();
	return 0;
}
