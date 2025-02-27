/*
*****************************************************************************
						  Workshop - #4 (Part-2)

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
What this program does is it takes in the amount of a certain food you choose and upon picking the food it allows you to pick a certain amount of the food
*/

// 2 int 1 char

void prompt() {
	printf("Grocery Shopping\n");
	printf("================\n");
}

void loop() {
	int done = 0;
	while (done != -1) {
		prompt();
		int appleNum, orangeNum, pearNum, tomatoesNum, cabbageNum;
		//apples
		printf("How many APPLES do you need? : ");
		scanf("%d", &appleNum);
		while (appleNum < 0) {
			printf("ERROR: Value must be 0 or more.\n");
			printf("How many APPLES do you need? : ");
			scanf("%d", &appleNum);
		}
		//oranges
		printf("\n");
		printf("How many ORANGES do you need? : ");
		scanf("%d", &orangeNum);
		while (orangeNum < 0) {
			printf("ERROR: Value must be 0 or more.\n");
			printf("How many ORANGES do you need? : ");
			scanf("%d", &orangeNum);
		}
		//pear
		printf("\n");
		printf("How many PEARS do you need? : ");
		scanf("%d", &pearNum);
		while (pearNum < 0) {
			printf("ERROR: Value must be 0 or more.\n");
			printf("How many PEARS do you need? : ");
			scanf("%d", &pearNum);
		}
		//tomatoes
		printf("\n");
		printf("How many TOMATOES do you need? : ");
		scanf("%d", &tomatoesNum);
		while (tomatoesNum < 0) {
			printf("ERROR: Value must be 0 or more.\n");
			printf("How many TOMATOES do you need? : ");
			scanf("%d", &tomatoesNum);
		}
		//cabbages
		printf("\n");
		printf("How many CABBAGES do you need? : ");
		scanf("%d", &cabbageNum);
		while (cabbageNum < 0) {
			printf("ERROR: Value must be 0 or more.\n");
			printf("How many CABBAGES do you need? : ");
			scanf("%d", &cabbageNum);
		}

		int applesPicked;
		int appleNeed = appleNum;
		printf("\n");
		printf("--------------------------\n");
		printf("Time to pick the products!\n");
		printf("--------------------------\n\n");
		/// <summary>
		/// The way this part works is by having a food Need
		/// </summary>
		if (appleNum > 0) {
			printf("Pick some APPLES... how many did you pick? : ");
			scanf("%d", &applesPicked);
			int finished = -1;// value used to end this while loop
			//apple temp = appleNeed
			while (finished != 0) {
				if (appleNeed == 0 || appleNeed == applesPicked) {
					finished = 0;
					// if no apples are needed or if the apples needed are equal to the amount picked
				}
				else if (applesPicked <= 0) {
					// if the apples picked is less than 0
					printf("ERROR: You must pick at least 1!");
					printf("\nPick some APPLES... how many did you pick? : ");
					scanf("%d", &applesPicked);
				}
				else if (applesPicked > appleNeed) {
					// if the apples picked is greater than the apples needed
					printf("You picked too many... only %d more APPLE(S) are needed.", appleNeed);
					printf("\nPick some APPLES... how many did you pick? : ");
					scanf("%d", &applesPicked);

				}
				else if (applesPicked < appleNeed) {
					// if the apples picked is less than the amount needed
					appleNeed = (appleNeed - applesPicked);
					printf("Looks like we still need some APPLES...");
					printf("\nPick some APPLES... how many did you pick? : ");
					scanf("%d", &applesPicked);
				}
			}
			printf("Great, that's the apples done!\n\n");
		}
		int orangeNeed = orangeNum;int orangesPicked;
		if (orangeNum > 0) {
			printf("Pick some ORANGES... how many did you pick? : ");
			scanf("%d", &orangesPicked);
			int finished = -1;
			while (finished != 0) {
				if (orangeNeed == 0 || orangeNeed == orangesPicked) {
					finished = 0;
				}
				else if (orangesPicked <= 0) {
					printf("ERROR: You must pick at least 1!");
					printf("\nPick some ORANGES... how many did you pick? : ");
					scanf("%d", &orangesPicked);
				}
				else if (orangesPicked > orangeNeed) {
					printf("You picked too many... only %d more ORANGE(S) are needed.", orangeNeed);
					printf("\nPick some ORANGES... how many did you pick? : ");
					scanf("%d", &orangesPicked);

				}
				else if (orangesPicked < orangeNeed) {
					orangeNeed = (orangeNeed - orangesPicked);
					printf("Looks like we still need some ORANGES...");
					printf("\nPick some ORANGES... how many did you pick? : ");
					scanf("%d", &orangesPicked);
				}
			}
			printf("Great, that's the oranges done!\n\n");
		}
		if (pearNum > 0) {
			int pearsPicked;int pearNeed = pearNum;
			printf("Pick some PEARS... how many did you pick? : ");
			scanf("%d", &pearsPicked);
			int finished = -1;
			while (finished != 0) {
				if (pearNeed == 0 || pearNeed == pearsPicked) {
					finished = 0;
				}
				else if (pearsPicked <= 0) {
					printf("ERROR: You must pick at least 1!");
					printf("\nPick some PEARS... how many did you pick? : ");
					scanf("%d", &pearsPicked);
				}
				else if (pearsPicked > pearNeed) {
					printf("You picked too many... only %d more PEAR(S) are needed.", pearNeed);
					printf("\nPick some PEARS... how many did you pick? : ");
					scanf("%d", &pearsPicked);

				}
				else if (pearsPicked < pearNeed) {
					pearNeed = (pearNeed - pearsPicked);
					printf("Looks like we still need some PEARS...");
					printf("\nPick some PEARS... how many did you pick? : ");
					scanf("%d", &pearsPicked);
				}
			}
			printf("Great, that's the pears done!\n\n");
		}
		if (tomatoesNum > 0) {
			int tomatoesPicked; int tomatoesNeed = tomatoesNum;
			printf("Pick some TOMATOES... how many did you pick? : ");
			scanf("%d", &tomatoesPicked);
			int finished = -1;
			while (finished != 0) {
				if (tomatoesNeed == 0 || tomatoesNeed == tomatoesPicked) {
					finished = 0;
				}
				else if (tomatoesPicked <= 0) {
					printf("ERROR: You must pick at least 1!");
					printf("\nPick some TOMATOES... how many did you pick? : ");
					scanf("%d", &tomatoesPicked);
				}
				else if (tomatoesPicked > tomatoesNeed) {
					printf("You picked too many... only %d more TOMATO(ES) are needed.", tomatoesNeed);
					printf("\nPick some TOMATOES... how many did you pick? : ");
					scanf("%d", &tomatoesPicked);

				}
				else if (tomatoesPicked < tomatoesNeed) {
					tomatoesNeed = (tomatoesNeed - tomatoesPicked);
					printf("Looks like we still need some TOMATOES...");
					printf("\nPick some TOMATOES... how many did you pick? : ");
					scanf("%d", &tomatoesPicked);
				}
			}
			printf("Great, that's the tomatoes done!\n\n");
		}
		if (cabbageNum > 0) {
			int cabbagePicked; int cabbageNeed = cabbageNum;
			printf("Pick some CABBAGES... how many did you pick? : ");
			scanf("%d", &cabbagePicked);
			int finished = -1;
			while (finished != 0) {
				if (cabbageNeed == 0 || cabbageNeed == cabbagePicked) {
					finished = 0;
				}
				else if (cabbagePicked <= 0) {
					printf("ERROR: You must pick at least 1!");
					printf("\nPick some CABBAGES... how many did you pick? : ");
					scanf("%d", &cabbagePicked);
				}
				else if (cabbagePicked > cabbageNeed) {
					printf("You picked too many... only %d more CABBAGE(S) are needed.", cabbageNeed);
					printf("\nPick some CABBAGES... how many did you pick? : ");
					scanf("%d", &cabbagePicked);

				}
				else if (cabbagePicked < cabbageNeed) {
					cabbageNeed = (cabbageNeed - cabbagePicked);
					printf("Looks like we still need some CABBAGES...");
					printf("\nPick some CABBAGES... how many did you pick? : ");
					scanf("%d", &cabbagePicked);
				}
			}
			printf("Great, that's the cabbages done!\n\n");

		}
		printf("All the items are picked!\n");
		int choice;
		printf("\nDo another shopping? (0=NO): ");
		scanf("%d", &choice);
		if (choice == 0) {
			done = -1;
			printf("\nYour tasks are done for today - enjoy your free time!\n");
		}
		else {
			printf("\n");
		}

	}
}

int main(void) {
	loop();
	return 0;
}

