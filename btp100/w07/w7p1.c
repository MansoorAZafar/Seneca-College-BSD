#define _CRT_SECURE_NO_WARNINGS
/*
*****************************************************************************
                          Workshop - #7 (P1)
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

typedef struct {
    //commands
    int lives; // num of lives
    char symbol; // player symbol
    int tCounter; // treasure counter
    int pathHistory[13]; // path of 14 multiplies of 5 so 70
} PlayerInfo;

typedef struct {
    int max_moves;
    int pathLen;
    int bombs[70];
    int treasures[70];
} GameInfo;


int main(void) {
    //struct declarations
    PlayerInfo player;
    GameInfo game;

    //printing title and sentences
    printf("================================\n");
    printf("         Treasure Hunt!\n");
    printf("================================\n\nPLAYER Configuration");
    printf("\n--------------------\n");

    //making player info
    printf("Enter a single character to represent the player: ");
    scanf(" %c", &player.symbol);
    printf("Set the number of lives: ");
    scanf("%d", &player.lives);
    while (player.lives > 10 || player.lives < 1) {
        printf("     Must be between 1 and 10!\n");
        printf("Set the number of lives: ");
        scanf("%d", &player.lives);
    }
    printf("Player configuration set-up is complete\n\n");

    //Game set-up
    printf("GAME Configuration\n");
    printf("------------------\n");
    printf("Set the path length (a multiple of 5 between 10-70): ");
    scanf("%d", &game.pathLen);
    while (game.pathLen > 70 || game.pathLen < 10 || game.pathLen % 5 != 0) {
        printf("     Must be a multiple of 5 and between 10-70!!!\n");
        printf("Set the path length (a multiple of 5 between 10-70): ");
        scanf("%d", &game.pathLen);
    }

    printf("Set the limit for number of moves allowed: ");
    scanf("%d", &game.max_moves);
    while (game.max_moves < player.lives || game.max_moves >(game.pathLen * .75)) {
        printf("    Value must be between %d and %d\n", player.lives, (int)(game.pathLen * .75));
        printf("Set the limit for number of moves allowed: ");
        scanf("%d", &game.max_moves);
    }

    //Setting up the bombs
    //give bombs array the length of the path length
    
    //INSTRUCTIONS TO BOMB PLACEMENt
    printf("\nBOMB Placement\n");
    printf("--------------\n"
        "Enter the bomb positions in sets of 5 where a value\n"
        "of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n"
        "(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", game.pathLen);
    //int counter = 0;
    
    //PLACING BOMBS

    int i = 0; // value for the for loop
    int pos = 1; // position values
    int bombPos = 0;
    for (i = 0; i < (game.pathLen / 5); i++) {
        //Print out the statement first:
        if (pos < 10) {
            if ((pos + 4) < 10) {
                printf("   Positions [ %d- %d]: ", pos, pos + 4);
            }
            else {
                printf("   Positions [ %d-%d]: ", pos, pos + 4);
            }
        }
        else {
            printf("   Positions [%d-%d]: ", pos, pos + 4);
        }

        //take input and set bomb position
        pos += 5; // for the txt 
        scanf("%d %d %d %d %d", &game.bombs[bombPos], &game.bombs[bombPos +1], &game.bombs[bombPos +2], &game.bombs[bombPos +3], &game.bombs[bombPos +4]);
        bombPos += 5; // add onto the bomb pos to properly set their positions
    }

   
    printf("BOMB placement set\n\n");

    //INSTRUCTIONS FOR TREASURE 
    //instructions
    printf("TREASURE Placement\n");
    printf("------------------\n"
    "Enter the treasure placements in sets of 5 where a value\n"
    "of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n"
    "(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", game.pathLen);

    //PLACING TREASURE
    pos = 1; bombPos = 0; // same as setting the bombs
    for (i = 0; i < (game.pathLen / 5); i++) {
        //Print out the statement first:
        if (pos < 10) {
            if ((pos + 4) < 10) {
                printf("   Positions [ %d- %d]: ", pos, pos + 4);
            }
            else {
                printf("   Positions [ %d-%d]: ", pos, pos + 4);
            }
        }
        else {
            printf("   Positions [%d-%d]: ", pos, pos + 4);
        }

        //take input and set treasure position
        pos += 5; // for the txt 
        scanf("%d %d %d %d %d", &game.treasures[bombPos], &game.treasures[bombPos + 1], &game.treasures[bombPos + 2], &game.treasures[bombPos + 3], &game.treasures[bombPos + 4]);
        bombPos += 5; // add onto the treasure pos to properly set their positions
    }
    printf("TREASURE placement set\n\n");


    //GAME
    printf("GAME configuration set-up is complete...\n\n");
    printf("------------------------------------\n");
    printf("TREASURE HUNT Configuration Settings\n");
    printf("------------------------------------\n");
                           
    //PRINTING PLAYER AND GAME INFO
    printf("Player:\n");   
    printf("   Symbol     : %c\n", player.symbol);
    printf("   Lives      : %d\n", player.lives);
    printf("   Treasure   : [ready for gameplay]\n");
    printf("   History    : [ready for gameplay]\n\n");

    printf("Game:\n");
    printf("   Path Length: %d\n", game.pathLen);
    printf("   Bombs      : ");
    for (i = 0; i < game.pathLen; i++) {
        printf("%d", game.bombs[i]);
    }			  
    printf("\n");	  
    printf("   Treasure   : ");
    for (i = 0; i < game.pathLen; i++) {
        printf("%d", game.treasures[i]);
    }
    printf("\n\n");
    printf("====================================\n");
    printf("~ Get ready to play TREASURE HUNT! ~\n");
    printf("====================================\n");
    return 0;
}
