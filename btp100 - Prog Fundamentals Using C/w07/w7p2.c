#define _CRT_SECURE_NO_WARNINGS
/*
*****************************************************************************
                          Workshop - #7 (P2)
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

//PLAYER STRUCTURE
typedef struct {
    //commands
    int lives; // num of lives
    char symbol; // player symbol
    int tCounter; // treasure counter
    int pathHistory[13]; // path of 14 multiplies of 5 so 70
} PlayerInfo;

//GAME STRUCTURE
typedef struct {
    int max_moves; // max amount of moves they can make
    int pathLen; // the length of the path for the game
    int bombs[70]; // the array of bombs
    int treasures[70]; // array of treasures
    char positions[70]; // array of the current positions
} GameInfo;

void nl(int x) {
    int i;
    for (i = 0; i < x; i++) {
        printf("\n");
    }
}

void pw(char* word) {
    //PRINT WORD
    printf("%s", word);
}

void gameOver() {
    nl(1);
    pw("##################\n");
    pw("#   Game over!   #\n");
    pw("##################\n");
    nl(1);
    pw("You should play again and try to beat your score!\n");

}

void checker() {
    printf("\n----\nCHECKER 1 2 3\n----\n");
}

void baseCase(GameInfo game) {
    int i = 0;
    int num = 0;
    switch (i) {
    case 0:
        //Prints out FIRST LINE
        printf("  ");
        for (i = 0; i < game.pathLen; i++) {
            game.positions[i] =  '-';
            printf("%c", game.positions[i]);
        }

    case 1:
        //Prints out SECOND LINE
        num = 1;
        nl(1);
        printf("  ");
        for (i = 0; i < game.pathLen; i++) {
            if ((i + 1) % 10 == 0) {
                printf("%d", num);
                num++;
            }
            else {
                printf("|");
            }
        }

    case 2:
        ////Prints out THIRD LINE

        nl(1);
        printf("  ");
        num = 1;
        for (i = 0; i < game.pathLen; i++) {
            if (num == 10) {
                num = 0;
            }
            printf("%d", num);
            num++;
        }
    }
}

void playerInformation(GameInfo game, PlayerInfo player, int movesLeft) {
    nl(1);
    int remaingMoves = movesLeft;
    printf("+---------------------------------------------------+\n"
    "  Lives:  %d  | Treasures:  %d  |  Moves Remaining: %2d\n"
    "+---------------------------------------------------+\n", player.lives, player.tCounter, remaingMoves);

}

void playGame(GameInfo game, PlayerInfo player) {
    //SETTING UP BASE VALUES AND INITALIZING VARIABLES
    //P1
    nl(1);
    int i = 0;
    int repition = 0;
    player.tCounter = 0;
    //int num;
    baseCase(game);
    playerInformation(game, player, game.max_moves);
    //BASE POSITION SET
    int remainingMoves = game.max_moves;
    for (i = 0; i < game.pathLen; i++) {
        game.positions[i] = '-';
    }
    //
    //P1 DONE

    //LOOPING GAME P2
    while (player.lives > 0) {
        if (remainingMoves == 0) {
            player.lives = 0;
            nl(1);
            printf("no more MOVES remaining\n");
        }
        else{
        //SETTING UP BASE VARIABLES FOR INSIDE GAME
        int num = 0;
        int alreadyExplored[70];
        // continue until player runs out of lives
        //nl(1);
        //checker();
        int move = 0;
        
        //SETTING PLAYER MOVES
        
        printf("Next Move [1-%d]: ", game.pathLen);
        scanf("%d", &move);
        while (move > game.pathLen || move < 1) {
            printf("  Out of Range!!!");
            nl(1);
            printf("Next Move [1-%d]: ", game.pathLen);
            scanf("%d", &move);
        }


        // PRINT IF PLAYER LANDS ON ???

        //IF PLAYER LANDED ON NOTHING
        if (game.bombs[move-1] == 0 && game.treasures[move-1] == 0) {
            //LANDED ON NOTHING
            for (i = 0; i < game.pathLen; i++) {
                //Lets say you enter 4
                //Checks IF that num has already been explored
                //if NO then do it until I've checked every section in alreadyExplored
                //if STILL NO then its your first time aka nothing found
                //If I enter 8
                if (alreadyExplored[i] == move) {
                    nl(1);
                    pw("===============> Dope! You've been here before!\n");
                    if (repition > 0) {
                        repition++;
                    }
                    i = game.pathLen;
                }
                else if (i == game.pathLen - 1) {
                    nl(1);
                    pw("===============> [.] ...Nothing found here... [.]\n");
                    i = game.pathLen;
		    remainingMoves--;
                }
            }
        }

        //IF PLAYER LANDED ON BOMBS AND TREASURE
        else if (game.bombs[move - 1] == 1 && game.treasures[move - 1] == 1) {
            //PLAYER LANDS ON BOTH BOMB AND TREASURE 

            for (i = 0; i < game.pathLen; i++) {
                //Lets say you enter 4
                //Checks IF that num has already been explored
                //if NO then do it until I've checked every section in alreadyExplored
                //if STILL NO then its your first time aka nothing found
                if (alreadyExplored[i] == move) {
                    nl(1);
                    printf("===============> Dope! You've been here before!\n");
                    if (repition > 0) {
                        repition++;
                    }
                    i = game.pathLen;
                }
                else if (i == game.pathLen - 1) {
                    nl(1);
                    printf("===============> [&] !!! BOOOOOM !!! [&]\n");
                    printf("===============> [&] $$$ Life Insurance Payout!!! [&]\n");
                    i = game.pathLen;
                    player.lives--;
	            player.tCounter++;
		    remainingMoves--;
                }
            }
        }

        //IF PLAYER LANDS ON TREASURE ONLY
        else if (game.bombs[move-1] == 0 && game.treasures[move-1] == 1) {
            //LANDED ON TREASURE
            for (i = 0; i < game.pathLen; i++) {
                if (alreadyExplored[i] == move) {
                    nl(1);
                    printf("===============> Dope! You've been here before!\n");
                    if (repition > 0) {
                        repition++;
                    }
                    i = game.pathLen;
                }
                else if (i == game.pathLen-1) {
                    nl(1);
                    printf("===============> [$] $$$ Found Treasure! $$$ [$]\n");
                    player.tCounter++;
                    i = game.pathLen;
		    remainingMoves--;
                }
            }
        }

        //IF PLAYER LANDS ON BOMB ONLY
        else if (game.bombs[move-1] == 1 && game.treasures[move-1] == 0) {
            //LANDED ON BOMB
            for (i = 0; i < game.pathLen; i++) {
                if (alreadyExplored[i] == move) {
                    nl(1);
                    printf("===============> Dope! You've been here before!\n");
                    if (repition > 0) {
                        repition++;
                    }
                    i = game.pathLen;
                }
                else if (i == game.pathLen - 1) {
                    nl(1);
                    printf("===============> [!] !!! BOOOOOM !!! [!]\n");
                    i = game.pathLen;
                    player.lives--;
                    //printf("player lives remaining: %d", player.lives); ::works::
		    remainingMoves--;
                }
            }
        }
	alreadyExplored[repition] = move;
        if(repition == 0){
		repition++;
	}
	//PLAYER MOVING FINISHED


        //PRINTING CURRENT INFO 
	
	if (player.lives == 0) {
                printf("\nNo more LIVES remaining!\n");
            }

	
        i = 0; // for the switch statement to work
            switch (i) {

            case 0:
                //checker(); // goes  to all of these 
                //PRINT PLAYER POS
                nl(1);
                printf("  ");
                for (i = 0; i < game.pathLen; i++) {
                    if ((i+1) == move) {
                        printf("%c\n", player.symbol);
			i = game.pathLen;
                    }
                    else {
                        printf(" ");
                    }
                }

            case 1:
                //checker(); // goes to this too
                //nl(1);
                printf("  ");
                for (i = 0; i < game.pathLen; i++) {
                    
		    if(game.bombs[move-1] == 1 && game.treasures[move-1] == 1){
			game.positions[move-1] = '&';
		    }		    
		    else if (game.bombs[move-1] == 1) {
                        game.positions[move-1] = '!';
                    }
                    else if (game.treasures[move-1] == 1) {
                        game.positions[move-1] = '$';
                    }
                    else {
                        game.positions[move-1] = '.';
                    }
                    printf("%c", game.positions[i]);
                }
                
            case 2:
                num = 1;
                nl(1);
                printf("  ");
                for (i = 0; i < game.pathLen; i++) {
                    if ((i + 1) % 10 == 0) {
                        printf("%d", num);
                        num++;
                    }
                    else {
                        printf("|");
                    }
                }

            case 3:
                nl(1);
                printf("  ");
                num = 1;
                for (i = 0; i < game.pathLen; i++) {
                    if (num == 10) {
                        num = 0;
                    }
                    printf("%d", num);
                    num++;
                }
            }

            //Subtract a move
            
            playerInformation(game, player, remainingMoves);
            //player.lives = 0; //TO END LOOP   
            
        }
    }
    gameOver();
}

int main(void) {
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

    playGame(game, player);

    return 0;
}
