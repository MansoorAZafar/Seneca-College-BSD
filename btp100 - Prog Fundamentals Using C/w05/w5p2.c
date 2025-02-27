#define _CRT_SECURE_NO_WARNINGS
/*
*****************************************************************************
						  Workshop - #5 (P2)
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
#define MIN_YEAR 2012
#define MAX_YEAR 2022
#define LOG_DAYS 3


void log_(int month, int year, int day) {
	double morning_rating_total = 0; double evening_rating_total = 0; int i;
	switch (month) {
	case 1: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-JAN-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		  printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		  printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		  printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		  printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		  printf("\n----------------------------\n");
		  printf("Average overall rating:  %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		  break;
	case 2: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-FEB-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		  printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		  printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		  printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		  printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		  printf("\n----------------------------\n");
		  printf("Average overall rating:  %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		  break;
	case 3: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-MAR-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		  printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		  printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		  printf("\nAverage monring rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		  printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		  printf("\n----------------------------\n");
		  printf("Average overall rating:   %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		  break;
	case 4: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-APR-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		  printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		  printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		  printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		  printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		  printf("\n----------------------------\n");
		  printf("Average overall rating:   %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		  break;
	case 5: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-MAY-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		  printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		  printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		  printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		  printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		  printf("\n----------------------------\n");
		  printf("Average overall rating:   %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		  break;
	case 6: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-JUN-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		  printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		  printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		  printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		  printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		  printf("\n----------------------------\n");
		  printf("Average overall rating:   %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		  break;
	case 7: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-JUL-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		  printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		  printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		  printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		  printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		  printf("\n----------------------------\n");
		  printf("Average overall rating:   %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		  break;
	case 8: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-AUG-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		  printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		  printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		  printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		  printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		  printf("\n----------------------------\n");
		  printf("Average overall rating:   %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		  break;
	case 9: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-SEP-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		  printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		  printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		  printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		  printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		  printf("\n----------------------------\n");
		  printf("Average overall rating:   %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		  break;
	case 10: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-OCT-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		   printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		   printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		   printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		   printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		   printf("\n----------------------------\n");
		   printf("Average overall rating:   %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		   break;
	case 11: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-NOV-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		   printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		   printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		   printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		   printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		   printf("\n----------------------------\n");
		   printf("Average overall rating:   %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		   break;
	case 12: for (i = 0; i < LOG_DAYS; i++) {
		printf("%d-DEC-", year);
		if (day < 10) {
			printf("0%d", day);
		}
		else {
			printf("%d", day);
		}
		int finished = 0;
		printf("\n   Morning rating (0.0-5.0): ");
		double rating;
		scanf("%lf", &rating);
		while (finished != 1) {
			if (rating < 0 || rating > 5) {
				printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
				printf("\n   Morning rating (0.0-5.0): ");
				scanf("%lf", &rating);
			}
			else {
				morning_rating_total += rating;
				printf("   Evening rating (0.0-5.0): ");
				scanf("%lf", &rating);
				while (finished != 1) {
					if (rating < 0 || rating > 5) {
						printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!");
						printf("\n   Evening rating (0.0-5.0): ");
						scanf("%lf", &rating);
					}
					else {
						evening_rating_total += rating;
						finished = 1;
						day++;
					}
				}

			}
		}
		printf("\n");
	}
		   printf("Summary\n=======\nMorning total rating: %.3lf\nEvening total rating:  %.3lf\n", morning_rating_total, evening_rating_total);
		   printf("----------------------------\nOverall total rating: %.3lf\n", (morning_rating_total + evening_rating_total));
		   printf("\nAverage morning rating:  %.1lf", (morning_rating_total / LOG_DAYS));
		   printf("\nAverage evening rating:  %.1lf", (evening_rating_total / LOG_DAYS) + 0.05);
		   printf("\n----------------------------\n");
		   printf("Average overall rating:   %.1lf", ((morning_rating_total + evening_rating_total) / (LOG_DAYS * 2)) + 0.05);

		   break;
	}
	printf("\n");

}

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
	printf("\n*** Log date set! ***\n\n");
	log_(month, year, day);
}

int main(void) {
	const int JAN = 1; const int DEC = 12;
	date(JAN, DEC);

	return 0;
}

