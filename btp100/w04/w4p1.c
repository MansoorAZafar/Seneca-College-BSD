/*
*****************************************************************************
						  Workshop - #4 (Part-1)

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
What this program does is, it promots the user with the choice of picking either 'D', 'W', 'F' each repersenting a loop and repeating
*/

// 2 int 1 char

void loop() {
	int done = 0;
	while (done != -1) {
		done = 0;
		printf("D = do/while | W = while | F = for | Q = quit\n");
		printf("Enter loop type and the number of times to iterate (Quit=Q0): ");
		int x;
		char ch;
		scanf(" %c%d", &ch, &x);
		if (ch == 'Q' && x == 0) {
			//if quit do this
			done = -1;
			printf("\n");
			printf("+--------------------+\n");
			printf("Loop application ENDED\n");
			printf("+--------------------+\n");
		}
		else if (ch == 'Q' && x != 0) {
			//if they want to quit but mess up with the int
			printf("ERROR: To quit, the number of iterations should be 0!\n\n");
		}
		else if (ch == 'D' || ch == 'W' || ch == 'F' || ch == 'Q') {
			// if char is one of the correct options do this
			if (x >= 3 && x <= 20) {
				switch (ch) {
				case 'D': printf("DO-WHILE: ");
					do {
						printf("%c", ch);
						done++; // prints out the char using a do-while loop
					} while (done < x);
					break; // if the user entered D

				case 'W': printf("WHILE   : ");
					while (done < x) {
						printf("%c", ch);
						done++; // prints out the char using a while loop
					}
					break; // if user entered W

				case 'F': printf("FOR     : ");
					for (done = 0; done < x; done++) {
						printf("%c", ch); // prints out the respective char x amount of times
					}
					break; // if user entered F
				}
				printf("\n\n");
			}
			else {
				printf("ERROR: The number of iterations must be between 3-20 inclusive!\n\n");
			}
		}
		else {
			// if invalid char do this
			printf("ERROR: Invalid entered value(s)!\n\n");
		}
	}
}

void prompt() {
	printf("+----------------------+\n");
	printf("Loop application STARTED\n");
	printf("+----------------------+\n\n");
	loop();


}

int main(void) {
	prompt();
	return 0;
}

