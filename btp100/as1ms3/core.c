/*
*****************************************************************************
                        Assignment 1 - Milestone 3
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

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

int getNum() {
    int num;
    scanf("%d", &num);
    return num;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

int inputIntPositive() {
    int num = getNum();
    if (num > 0) {
        return num;
    }
    return inputIntPositive();
}

int inputIntRange(int lRange, int hRange) {
    int num = getNum();
    if (num >= lRange && num <= hRange) {
        return num;
    }
    printf("ERROR! Value must be between %d and %d inclusive: ", lRange, hRange);
    return inputIntRange(lRange, hRange);

}

char inputCharOption(char* str) {
    char ch; int count = 0;
    char temp = '\0';
    while ((ch = getchar()) != '\n') {
        count++;
        if (count == 1) {
            temp = ch;
        }
    }
    int i = 0;
    for (i = 0; i < sizeof(str); i++) {
        if (temp == str[i] && count == 1) {
            return temp;
        }
    }
    if (count > 0) { printf("ERROR: Character must be one of [yn]: "); }
    return inputCharOption(str);
}

void inputCString(char string[], int x, int num) {
    int l = 0;
    for (l = 0; l < 15; l++) { string[l] = '\0'; }
    char ch; int count = 0; char* pointer = string; int i = 0;
    char temp[16];
    while ((ch = getchar()) != '\n') {
        count++;
        if (count <= 16) {
            temp[count - 1] = ch;
        }
    }
    if (count <= 16 && count > 0) {
        for (i = 0; i < count; i++) { pointer[i] = temp[i]; }
        return;
    }
    else {
        if (count > 0) { printf("ERROR: String length must be no more than 15 chars: "); }

        inputCString(string, x, num);
    }
}

void displayFormattedPhone(const char phone[]) {

    if (phone != NULL) {
        int valid = 0;
        int len = 0;
        for (len = 0; phone[len] != '\0'; len++);
        //printf("len is %d", len); // PASS LENGTH WORKS
        if (len == 10) {
            int count = 0;
            int i = 0;
            for (i = 0; i < len; i++) { if (phone[i] >= 48 && phone[i] <= 57) { count++; } }
            if (count == 10) {
                valid++;
            }
        }
        else {
            valid = 0;
        }
        if (valid) {
            int i = 0;
            printf("(");
            for (i = 0; i < len; i++) { printf("%c", phone[i]); if (i == 2) { printf(")"); } if (i == 5) { printf("-"); } }
            return;
        }
        else {

            printf("(___)___-____");
            return;
        }
    }
    printf("(___)___-____");
    return;

}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////