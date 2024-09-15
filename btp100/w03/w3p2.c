/*
*****************************************************************************
						  Workshop - #3 (Part-2)

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

//15 var

void makeCoffee() {
	char c_1_type, c_1_grind, c_1_cream, c_2_type, c_2_grind, c_2_cream, c_3_type, c_3_grind, c_3_cream;
	int c_1_weight, c_2_weight, c_3_weight;
	double c_1_temp, c_2_temp, c_3_temp;
	const double GRAMS_IN_LBS = 453.5924;

	printf("Take a Break - Coffee Shop\n");
	printf("==========================\n\n");
	printf("Enter the coffee product information being sold today...\n\n");
	printf("COFFEE-1...\n");
	printf("Type ([L]ight,[B]lend): ");
	scanf("%c", &c_1_type); 
	printf("Grind size ([C]ourse,[F]ine): ");
	scanf(" %c", &c_1_grind);
	printf("Bag weight (g): ");
	scanf("%d", &c_1_weight);
	printf("Best served with cream ([Y]es,[N]o): ");
	scanf(" %c", &c_1_cream);
	printf("Ideal serving temperature (Celsius): ");
	scanf("%lf", &c_1_temp);
	
	printf("\nCOFFEE-2...\n");
	printf("Type ([L]ight,[B]lend): ");
	scanf(" %c", &c_2_type);
	printf("Grind size ([C]ourse,[F]ine): ");
	scanf(" %c", &c_2_grind);
	printf("Bag weight (g): ");
	scanf("%d", &c_2_weight);
	printf("Best served with cream ([Y]es,[N]o): ");
	scanf(" %c", &c_2_cream);
	printf("Ideal serving temperature (Celsius): ");
	scanf("%lf", &c_2_temp);

	printf("\nCOFFEE-3...\n");
	printf("Type ([L]ight,[B]lend): ");
	scanf(" %c", &c_3_type);
	printf("Grind size ([C]ourse,[F]ine): ");
	scanf(" %c", &c_3_grind);
	printf("Bag weight (g): ");
	scanf("%d", &c_3_weight);
	printf("Best served with cream ([Y]es,[N]o): ");
	scanf(" %c", &c_3_cream);
	printf("Ideal serving temperature (Celsius): ");
	scanf("%lf", &c_3_temp);
	
	printf("\n");
	
	printf("---+---------------+---------------+---------------+-------+--------------\n");
	printf("   |    Coffee     |    Coffee     |   Packaged    | Best  |   Serving\n");
	printf("   |     Type      |  Grind Size   |  Bag Weight   | Served| Temperature\n");
	printf("   +---------------+---------------+---------------+ With  +--------------\n");
	printf("ID | Light | Blend | Course | Fine |  (G) | Lbs    | Cream |   (C) |   (F)\n");
	printf("---+---------------+---------------+---------------+-------+--------------\n");
	
	printf(" 1 |   %d   |   %d   |    %d   |   %d  | %4d | %6.3lf |   %d   | %5.1lf | %5.1lf\n",
		c_1_type == 'L' || c_1_type == 'l', c_1_type == 'B' || c_1_type == 'b', 
		c_1_grind == 'C' || c_1_grind == 'c', c_1_grind == 'F' || c_1_grind == 'f',
		c_1_weight, ((float)c_1_weight/ GRAMS_IN_LBS), c_1_cream == 'Y' || c_1_cream == 'y',
		c_1_temp, (c_1_temp * 1.8) + 32.0);

	printf(" 2 |   %d   |   %d   |    %d   |   %d  | %4d | %6.3lf |   %d   | %5.1lf | %5.1lf\n",
		c_2_type == 'L' || c_2_type == 'l', c_2_type == 'B' || c_2_type == 'b',
		c_2_grind == 'C' || c_2_grind == 'c', c_2_grind == 'F' || c_2_grind == 'f',
		c_2_weight, ((float)c_2_weight / GRAMS_IN_LBS), c_2_cream == 'Y' || c_2_cream == 'y',
		c_2_temp, (c_2_temp * 1.8) + 32.0);
	
	printf(" 3 |   %d   |   %d   |    %d   |   %d  | %4d | %6.3lf |   %d   | %5.1lf | %5.1lf\n",
		c_3_type == 'L' || c_3_type == 'l', c_3_type == 'B' || c_3_type == 'b',
		c_3_grind == 'C' || c_3_grind == 'c', c_3_grind == 'F' || c_3_grind == 'f',
		c_3_weight, ((float)c_3_weight / GRAMS_IN_LBS), c_3_cream == 'Y' || c_3_cream == 'y',
		c_3_temp, (c_3_temp*1.8) + 32.0);

	char c_strength, c_maker, c_cream;
	int serving;
	printf("\nEnter how you like your coffee and the coffee maker equipment you use...\n\n");
	printf("Coffee strength ([M]ild,[R]ich): ");
	scanf(" %c", &c_strength);
	printf("Do you like your coffee with cream ([Y]es,[N]o): ");
	scanf(" %c", &c_cream);
	printf("Typical number of daily servings: ");
	scanf(" %d", &serving);
	printf("Maker ([R]esidential,[C]ommercial): ");
	scanf(" %c", &c_maker);
	printf("\nThe below table shows how your preferences align to the available products:\n\n");

	printf("--------------------+--------------------+-------------+-------+--------------\n");
	printf("  |     Coffee      |       Coffee       |  Packaged   | With  |   Serving\n");
	printf("ID|      Type       |     Grind Size     | Bag Weight  | Cream | Temperature\n");
	printf("--+-----------------+--------------------+-------------+-------+--------------\n");
	printf(" 1|       %d         |         %d          |      %d      |   %d   |      %d\n",
		((c_strength == 'M' || c_strength == 'm') && (c_1_type == 'L' || c_1_type == 'l')) || ((c_strength == 'r' || c_strength == 'R') && (c_1_type == 'b' || c_1_type == 'B')),
		((c_maker == 'R' || c_maker == 'r') && (c_1_grind == 'c' || c_1_grind == 'C')) || ((c_maker == 'C' || c_maker == 'c') && (c_1_grind == 'f' || c_1_grind == 'F')),
		(serving <= 4 && c_1_weight <= 250) || ((serving <= 9 && serving >= 5) && c_1_weight == 500) || (serving >= 10 && c_1_weight == 1000),
		((c_cream == 'Y' || c_cream == 'y') && (c_1_cream == 'Y' || c_1_cream == 'y')) || ((c_cream == 'n' || c_cream == 'N') && (c_1_cream == 'n' || c_1_cream == 'N')),
		((c_maker == 'r' || c_maker == 'R') && (c_1_temp >= 60.0 && c_1_temp <= 69.9)) || ((c_maker == 'c' || c_maker == 'C') && c_1_temp >= 70.0));

	printf(" 2|       %d         |         %d          |      %d      |   %d   |      %d\n",
		((c_strength == 'M' || c_strength == 'm') && (c_2_type == 'L' || c_2_type == 'l')) || ((c_strength == 'r' || c_strength == 'R') && (c_2_type == 'b' || c_2_type == 'B')),
		((c_maker == 'R' || c_maker == 'r') && (c_2_grind == 'c' || c_2_grind == 'C')) || ((c_maker == 'C' || c_maker == 'c') && (c_2_grind == 'f' || c_2_grind == 'F')),
		(serving <= 4 && c_2_weight <= 250) || ((serving <= 9 && serving >= 5) && c_2_weight == 500) || (serving >= 10 && c_2_weight == 1000),
		((c_cream == 'Y' || c_cream == 'y') && (c_2_cream == 'Y' || c_2_cream == 'y')) || ((c_cream == 'n' || c_cream == 'N') && (c_2_cream == 'n' || c_2_cream == 'N')),
		((c_maker == 'r' || c_maker == 'R') && (c_2_temp >= 60.0 && c_2_temp <= 69.9)) || ((c_maker == 'c' || c_maker == 'C') && c_2_temp >= 70.0));

	printf(" 3|       %d         |         %d          |      %d      |   %d   |      %d\n",
		((c_strength == 'M' || c_strength == 'm') && (c_3_type == 'L' || c_3_type == 'l')) || ((c_strength == 'r' || c_strength == 'R') && (c_3_type == 'b' || c_3_type == 'B')),
		((c_maker == 'R' || c_maker == 'r') && (c_3_grind == 'c' || c_3_grind == 'C')) || ((c_maker == 'C' || c_maker == 'c') && (c_3_grind == 'f' || c_3_grind == 'F')),
		(serving <= 4 && c_3_weight <= 250) || ((serving <= 9 && serving >= 5) && c_3_weight == 500) || (serving >= 10 && c_3_weight == 1000),
		((c_cream == 'Y' || c_cream == 'y') && (c_3_cream == 'Y' || c_3_cream == 'y')) || ((c_cream == 'n' || c_cream == 'N') && (c_3_cream == 'n' || c_3_cream == 'N')),
		((c_maker == 'r' || c_maker == 'R') && (c_3_temp >= 60.0 && c_3_temp <= 69.9)) || ((c_maker == 'c' || c_maker == 'C') && c_3_temp >= 70.0));

	printf("\n");

	printf("Enter how you like your coffee and the coffee maker equipment you use...\n\n");
	printf("Coffee strength ([M]ild,[R]ich): ");
	scanf(" %c", &c_strength);
	printf("Do you like your coffee with cream ([Y]es,[N]o): ");
	scanf(" %c", &c_cream);
	printf("Typical number of daily servings: ");
	scanf("%d", &serving);
	printf("Maker ([R]esidential,[C]ommercial): ");
	scanf(" %c", &c_maker);
	printf("\nThe below table shows how your preferences align to the available products:\n\n");

	printf("--------------------+--------------------+-------------+-------+--------------\n");
	printf("  |     Coffee      |       Coffee       |  Packaged   | With  |   Serving\n");
	printf("ID|      Type       |     Grind Size     | Bag Weight  | Cream | Temperature\n");
	printf("--+-----------------+--------------------+-------------+-------+--------------\n");
	printf(" 1|       %d         |         %d          |      %d      |   %d   |      %d\n",
		((c_strength == 'M' || c_strength == 'm') && (c_1_type == 'L' || c_1_type == 'l')) || ((c_strength == 'r' || c_strength == 'R') && (c_1_type == 'b' || c_1_type == 'B')),
		((c_maker == 'R' || c_maker == 'r') && (c_1_grind == 'c' || c_1_grind == 'C')) || ((c_maker == 'C' || c_maker == 'c') && (c_1_grind == 'f' || c_1_grind == 'F')),
		(serving <= 4 && c_1_weight <= 250) || ((serving <= 9 && serving >= 5) && c_1_weight == 500) || (serving >= 10 && c_1_weight == 1000),
		((c_cream == 'Y' || c_cream == 'y') && (c_1_cream == 'Y' || c_1_cream == 'y')) || ((c_cream == 'n' || c_cream == 'N') && (c_1_cream == 'n' || c_1_cream == 'N')),
		((c_maker == 'r' || c_maker == 'R') && (c_1_temp >= 60.0 && c_1_temp <= 69.9)) || ((c_maker == 'c' || c_maker == 'C') && c_1_temp >= 70.0));

	printf(" 2|       %d         |         %d          |      %d      |   %d   |      %d\n",
		((c_strength == 'M' || c_strength == 'm') && (c_2_type == 'L' || c_2_type == 'l')) || ((c_strength == 'r' || c_strength == 'R') && (c_2_type == 'b' || c_2_type == 'B')),
		((c_maker == 'R' || c_maker == 'r') && (c_2_grind == 'c' || c_2_grind == 'C')) || ((c_maker == 'C' || c_maker == 'c') && (c_2_grind == 'f' || c_2_grind == 'F')),
		(serving <= 4 && c_2_weight <= 250) || ((serving <= 9 && serving >= 5) && c_2_weight == 500) || (serving >= 10 && c_2_weight == 1000),
		((c_cream == 'Y' || c_cream == 'y') && (c_2_cream == 'Y' || c_2_cream == 'y')) || ((c_cream == 'n' || c_cream == 'N') && (c_2_cream == 'n' || c_2_cream == 'N')),
		((c_maker == 'r' || c_maker == 'R') && (c_2_temp >= 60.0 && c_2_temp <= 69.9)) || ((c_maker == 'c' || c_maker == 'C') && c_2_temp >= 70.0));

	printf(" 3|       %d         |         %d          |      %d      |   %d   |      %d\n",
		((c_strength == 'M' || c_strength == 'm') && (c_3_type == 'L' || c_3_type == 'l')) || ((c_strength == 'r' || c_strength == 'R') && (c_3_type == 'b' || c_3_type == 'B')),
		((c_maker == 'R' || c_maker == 'r') && (c_3_grind == 'c' || c_3_grind == 'C')) || ((c_maker == 'C' || c_maker == 'c') && (c_3_grind == 'f' || c_3_grind == 'F')),
		(serving <= 4 && c_3_weight <= 250) || ((serving <= 9 && serving >= 5) && c_3_weight == 500) || (serving >= 10 && c_3_weight == 1000),
		((c_cream == 'Y' || c_cream == 'y') && (c_3_cream == 'Y' || c_3_cream == 'y')) || ((c_cream == 'n' || c_cream == 'N') && (c_3_cream == 'n' || c_3_cream == 'N')),
		((c_maker == 'r' || c_maker == 'R') && (c_3_temp >= 60.0 && c_3_temp <= 69.9)) || ((c_maker == 'c' || c_maker == 'C') && c_3_temp >= 70.0));
	
	printf("\nHope you found a product that suits your likes!\n");

	
	

}

int main(void) {
	makeCoffee();
	return 0;
}