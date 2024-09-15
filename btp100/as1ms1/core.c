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

//Library 
#include <stdio.h>
#include <ctype.h>
#include "core.h"


//1
int inputInt() {
    // LETS GOO RECURSION LLLLL
    int num = 0;
    if (scanf("%d", &num)) {
        return num;
    }
    else {
        printf("Error! Input a whole number: ");
        char ch[7];
        scanf("%s", ch);

    }
    return inputInt();
}

//2
int inputIntPositive() {
    int num = 0;
    scanf("%d", &num);
    if (num >= 0) {
        return num;
    }
    else {
        printf("ERROR! Value must be > 0: ");
        return inputIntPositive();
    }
}

//3
int inputIntRange(int x, int y) {
    int num = 0;
    if (scanf("%d", &num)) {
        if ((num >= y && num <= x) || (num <= y && num >= x)) {
            return num;
        }
        //If y is greater than x
        else {
            printf("ERROR! Value must be between %d and %d inclusive: ", x, y);
            return inputIntRange(x, y);
        }
    }
    else {
        printf("Error! Input a whole number: ");
        char ch[7];
        scanf("%s", ch);
    }
    return inputIntRange(x, y);
    //If x is greater than y
}

//5
char inputCharOption(char* string) {
    char ch;
    int i = 0;
    scanf("%c", &ch);
    scanf("%c", &ch); // I still dont know why I have to do two of the scanf?? but whatever ig
    /*
    * If I cannot use "sizeof"
    * Do this
    * -->
    * int count;
    * for(count=0; string[count] != '\0'; count++ );
    * -->
    * count will now equal the size of the string
    */
    int count = 0;
    for(count=0; string[count] != '\0'; count++ );
    for (i = 0; i < count; i++) {
        if (ch == string[i]) {
            return ch;
        }
    }
    printf("ERROR: Character must be one of [%s]: ", string);
    return inputCharOption(string);
}

//6

char inputCString(char string[7], int x, int num) {
    char ch[20];
    int count = 0;
    char* pointer = string;
    int i = 0;
    for (i = 0; i < 20; i++) { scanf("%c", &ch[i]); if (ch[i] == '\n') { i = 20; } else { count++; } }
    //printf("%d the size is ", sizeof(string));
    //scanf("%s", ch);

    //scanf("%[^\n]%*s", ch);
    if (x == num) {
        //printf("\nX is equal to num X and NUM COUNT\n", x, num, count);
        if (count == x && count == num) {
            //printf("\ncount is equal to x and count is equal to num count,x,num %d%d%d\n", count, x, num);
            //If you cant use "sizeof" do this instead
            /*
            * for(count=0;string[count] != '0'; count++); The count will be 8 so do i<count-1 instead of i < sizeof(string)-1
            */
            for (i = 0;i < count;i++) { pointer[i] = ch[i];  }
            
            return pointer[0];
        }
        else {
            if(count > 0){printf("ERROR: String length must be exactly %d chars: ", x);}
	    
            return inputCString(string, x, num);
        }
    }
    else if (count > num) {
        //printf("\nX is greater than num X and NUM COUNT\n", x, num, count);
        if (count <= x && count >= num) {
            //printf("\ncount is less or equal to x and count is greater or equal to num count,x,num %d%d%d\n", count, x, num);
            for (i = 0;i < count;i++) { pointer[i] = ch[i]; }
           
            return pointer[0];
        }
        else {
            
	    printf("ERROR: String length must be no more than %d chars: ", num);
            return inputCString(string, x, num);
        }
    }
    else {
        //printf("\nX is LESS than num X and NUM COUNT\n", x, num, count);
        if (count >= x && count <= num) {
            //printf("\ncount is greater or equal to x and count is less or equal to num count,x,num %d%d%d\n", count, x, num);
            for (i = 0;i < count;i++) { pointer[i] = ch[i]; }
            
            return pointer[0];
        }
        else {
            printf("ERROR: String length must be between %d and %d chars: ", x, num);
	    
            return inputCString(string, x, num);
        }
    }
}

char displayFormattedPhone(char* phone) {
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
            return '\0';
        }
        else {
            printf("(___)___-____");
            return '\0';
        }
    }
    printf("(___)___-____");
    return '\0';
}
