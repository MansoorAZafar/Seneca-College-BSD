#define _CRT_SECURE_NO_WARNINGS
/*
*****************************************************************************
                        Assignment 1 - Milestone 1
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
//#include "a1ms1.c"

//Structures :

typedef struct {
    //Properties of an integer

    int x;

}tempName;


//1  : Check the if the input is an integer value, return an int

int inputInt();

//2  : Check if the input is positive, return an int

int inputIntPositive();

//3  :

int inputIntRange(int x, int y);

//4  :

char inputCharOption(char* string);

//5  :

char inputCString(char string[7], int x, int num);

//6  :

char displayFormattedPhone(char* phone);

