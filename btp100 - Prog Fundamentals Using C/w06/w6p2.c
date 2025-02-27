#define _CRT_SECURE_NO_WARNINGS
/*
*****************************************************************************
						  Workshop - #6 (P2)
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

void filter(double finalCost, double items[], int need[], char yesno[], double monthlyNETIncome, int numOfItems) {
	// MEANINGS
	// finalCost : The total cost of all products together 
	// items[] : the cost of the products individually
	// need[] : the priority set to the products
	// yesno[] : the char 'y' or 'n' dependant if it has financing options
	// monthlyNETIncome : the monthly net income that was set at the start
	// numOfItems : the number of items/products
	
	
	int choice;
	int i = 0;
	printf("How do you want to forecast your wish list?\n"
		" 1. All items (no filter)\n"
		" 2. By priority\n 0. Quit/Exit\n"
		"Selection: ");
	scanf("%d", &choice);
	int valid = 0;
	while (valid != 1) {
		if (choice > 2) {
			// if choice is NOT 1, 2 or 0
			printf("\nERROR: Invalid menu selection.\n");
			printf("\nHow do you want to forecast your wish list?\n"
				" 1. All items (no filter)\n"
				" 2. By priority\n 0. Quit/Exit\n"
				"Selection: ");
			scanf("%d", &choice);
		}
		else {
			// if choice IS 1, 2 or 0
			//valid = 1;	// will end the loop
			int year;
			int month;
			int monthlyNetIncomes = (int)monthlyNETIncome;
			switch (choice) {
				// switch for what num they choose
			case 1: 
					//if they choose the first filter option 

					year = (int)((finalCost / 12) / monthlyNETIncome); // sets the yr value
					month = (int)((int)(finalCost / monthlyNetIncomes) % 12 + 0.5); // sets the month value
						
						printf("\n");
						printf("====================================================\n");
						printf("Filter:   All items\n"
							"Amount:   $%1.2lf\n"
							"Forecast: %d years, %d months", finalCost, year, month+1);
						int checker = 0;
						//checks if any of the items entered have a financing option
						for (i = 0; i < numOfItems; i++) {
							if (yesno[i] == 'y') {
								checker++;
							}
						}
						if (checker > 0) {
							//item DOES have financing option
							printf("\nNOTE: Financing options are available on some items.\n"
								"      You can likely reduce the estimated months.\n");
							printf("====================================================\n");
						}
						else {
							printf("\n====================================================\n");
						}

				printf("\nHow do you want to forecast your wish list?\n"
					" 1. All items (no filter)\n"
					" 2. By priority\n 0. Quit/Exit\n"
					"Selection: ");
				scanf("%d", &choice);
				break;
			
			case 2: printf("\nWhat priority do you want to filter by? [1-3]: ");
				scanf("%d", &choice); // get the num 
				while (valid != 1) {
					// check if the num is actually valid or not

					if (choice > 3 || choice <= 0) {
						// if choice is NOT valid
						printf("\nERROR: Invalud menu selection.");
						printf("\nWhat priority do you want to filter by? [1-3]: ");
						scanf("%d", &choice);
					}
					else {
						// if choice IS valid
						// gets the total price for the items that match the priority
						double costForPriority = 0;
						for (i = 0; i < numOfItems; i++) {
							if (need[i] == choice) {
								costForPriority += items[i];
							}
						}
						
						//sets the yr and month values
						year = (int)((costForPriority / 12) / monthlyNETIncome); // sets the yr value
						month = (int)((int)(costForPriority / monthlyNetIncomes) % 12 + 0.5); // sets the month value


						printf("\n");
						printf("====================================================\n");
						printf("Filter:   by priority (%d)\n"
							"Amount:   $%1.2lf\n"
							"Forecast: %d years, %d months", choice, costForPriority, year, month+1);
						int checker = 0;
						//checks if item in x priority has financing options
						for (i = 0; i < numOfItems; i++) {
							if (yesno[i] == 'y' && need[i] == choice) {
								checker++;
							}
						}
						//if the checker is > 0 --> yes financing options
						if (checker > 0) {
							printf("\nNOTE: Financing options are available on some items.\n"
								"      You can likely reduce the estimated months.\n");
							printf("====================================================\n");
						}
						else {
							printf("\n====================================================\n");
						}
						valid = 1; // leave while loop
					}
				}
				valid = 0;
				printf("\nHow do you want to forecast your wish list?\n"
					" 1. All items (no filter)\n"
					" 2. By priority\n 0. Quit/Exit\n"
					"Selection: ");
				scanf("%d", &choice);
				break;

			case 0: printf("\nBest of luck in all your future endeavours!\n");valid = 1; break;
			default: printf("\nInvalid value"); break;
			}
		}
	}
	printf("\n");
}

void printChart(double items[], int need[], char yesno[], int numberOfItems, double monthyNetIncome) {
	printf("Item Priority Financed        Cost\n");
	printf("---- -------- -------- -----------\n");
	int i = 0;
	for (i = 0; i < numberOfItems; i++) {
		printf("%3d  %5d    %5c    %11.2lf\n", i + 1, need[i], yesno[i], items[i]);
	}
	printf("---- -------- -------- -----------\n");
	double finalCost = 0;
	for (i = 0; i < numberOfItems; i++) {
		finalCost += items[i];
	}
	printf("                      $%11.2lf\n\n", finalCost);
	//printf("Best of luck in all your future endeavours!\n");
	filter(finalCost, items, need, yesno, monthyNetIncome, numberOfItems );
}

void itemDetails(double monthlyNETIncome, int numOfItems) {
	double items[MAX_LENGTH-1];
	int priority[MAX_LENGTH-1];
	char financed[MAX_LENGTH-1];
	const double minCost = 100.00;
	int i = 0;
	for (i = 0; i < numOfItems; i++) {
		double itemCost;
		printf("Item-%d Details:\n   Item cost: $", (i + 1));
		scanf("%lf", &itemCost);
		int valid = 0;
		while (valid != 1) {
			if (itemCost < minCost) {
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
	printChart(items, priority, financed, numOfItems, monthlyNETIncome);
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
		else if (monthlyNETIncome > maxIncome) {
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


