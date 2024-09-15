/*
*****************************************************************************
						  Workshop - #5 (P1)
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
#include <stdio.h>
#include <stdlib.h>
#define MIN_YEAR 2012
#define MAX_YEAR 2022


void date(const int jan, const int dec) {
	printf("General Well-being Log\n");
	printf("======================\n");

	printf("Set the year and month for the well-being log (YYYY MM): ");
	int year, month;
	scanf("%d %d", &year, &month);
	//printf("Year is %d\nMonth is %d", year, month); scanf works
	int finished = 0;
	while (finished != 1) {

		if ((year < MIN_YEAR || year > MAX_YEAR) && (month < jan || month > dec)) {
			printf("   ERROR: The year must be between 2012 and 2022 inclusive\n");
			printf("   ERROR: Jan.(1) - Dec.(12)\n");
			printf("Set the year and month for the well-being log (YYYY MM): ");
			scanf("%d %d", &year, &month);

		}
		else if (year < MIN_YEAR || year > MAX_YEAR) {
			printf("   ERROR: The year must be between 2012 and 2022 inclusive\n");
			printf("Set the year and month for the well-being log (YYYY MM): ");
			scanf("%d %d", &year, &month);
		}
		else if (month < jan || month > dec) {
			printf("   ERROR: Jan.(1) - Dec.(12)\n");
			printf("Set the year and month for the well-being log (YYYY MM): ");
			scanf("%d %d", &year, &month);
		}
		else {
			finished = 1;
		}
	}
	int day = 01;
	printf("\n*** Log date set! ***\n\nLog starting date: %d", year);
	switch (month) {
	case 1: printf("-JAN-0%d", day); break;
	case 2: printf("-FEB-0%d", day); break;
	case 3: printf("-MAR-0%d", day); break;
	case 4: printf("-APR-0%d", day); break;
	case 5: printf("-MAY-0%d", day); break;
	case 6: printf("-JUN-0%d", day); break;
	case 7: printf("-JUL-0%d", day); break;
	case 8: printf("-AUG-0%d", day); break;
	case 9: printf("-SEP-0%d", day); break;
	case 10: printf("-OCT-0%d", day); break;
	case 11: printf("-NOV-0%d", day); break;
	case 12: printf("-DEC-0%d", day); break;
	}
	printf("\n");
}

int main(void) {

	const int JAN = 1; const int DEC = 12;
	date(JAN, DEC);

	return 0;
}


