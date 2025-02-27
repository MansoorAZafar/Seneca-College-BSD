/*
*****************************************************************************
                        Assignment 1 - Milestone 2
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

//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

void clearInputBuffer(void) {
    while (getchar() != '\n') {
        ;
    }
}

void suspend(void) {
    printf("<ENTER> to continue...\n");
    clearInputBuffer();
    putchar('\n');
}

int getNum() {
    int num;
    scanf("%d", &num);
    return num;
}

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
    return inputIntRange(lRange, hRange);
}

char inputCharOption(char* str) {
    char ch;
    ch = getchar();
    int i = 0;
    for (i = 0; i < sizeof(str); i++) {
        if (ch == str[i]) {
            return ch;
        }
    }
    return inputCharOption(str);
}

void inputCString(char string[], int x, int num) {
    char ch[20];
    int l = 0;
    for (l = 0; l < sizeof(string); l++) { string[l] = '\0'; }
    int count = 0;
    char* pointer = string;
    int i = 0;
    for (i = 0; i < 20; i++) { scanf("%c", &ch[i]); if (ch[i] == '\n') { i = 20; } else { count++; } }
    //printf("%d the size is ", sizeof(string));
    //scanf("%s", ch);
    for (i = 0; i < count; i++) { pointer[i] = ch[i]; }
    i = 0;
    if ((pointer[0])) {
        return;
    }
    else {
        inputCString(string, x, num);
    }
    //return;
    //scanf("%[^\n]%*s", ch);
    /*
    if (x == num) {
        //printf("\nX is equal to num X and NUM COUNT\n", x, num, count);
        if (count == x && count == num) {
            //printf("\ncount is equal to x and count is equal to num count,x,num %d%d%d\n", count, x, num);
            //If you cant use "sizeof" do this instead
            
            * for(count=0;string[count] != '0'; count++); The count will be 8 so do i<count-1 instead of i < sizeof(string)-1
            
            for (i = 0; i < count; i++) { pointer[i] = ch[i]; }

            return;
        }
        else {
            //if (count > 0) { printf("ERROR: String length must be exactly %d chars: ", x); }

            inputCString(string, x, num);
        }
    }
    else if (count > num) {
        //printf("\nX is greater than num X and NUM COUNT\n", x, num, count);
        if (count <= x && count >= num) {
            //printf("\ncount is less or equal to x and count is greater or equal to num count,x,num %d%d%d\n", count, x, num);
            for (i = 0; i < count; i++) { pointer[i] = ch[i]; }

            return;
        }
        else {

            //printf("ERROR: String length must be no more than %d chars: ", num);
            inputCString(string, x, num);
        }
    }
    else {
        //printf("\nX is LESS than num X and NUM COUNT\n", x, num, count);
        if (count >= x && count <= num) {
            //printf("\ncount is greater or equal to x and count is less or equal to num count,x,num %d%d%d\n", count, x, num);
            for (i = 0; i < count; i++) { pointer[i] = ch[i]; }

            return;
        }
        else {
            //printf("ERROR: String length must be between %d and %d chars: ", x, num);

            inputCString(string, x, num);
        }
    }
    */
}

void displayFormattedPhone(const char* phone) {

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