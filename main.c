/*
Filename: Oreopolis game version 6.c
Description: This program is for a mining game.
Author: David Aaron
Date: 30th April,2024
Input/output: Based on the code developed and the user's input's
Version: 6
 Log:
 1. This codes here has everything but a win and lose condition and unlike the last versions all the functions we needed for the player to mine, sell and check inventory are included but there are still some problems with the error handling and inputs
 2. Since before whenever we went to the mine the code stopped, i created a loop to make sure that when we move the code restarts and shows the new position and for quitting the game.
 3. In the next version i added a win and lose condition based on how much money they have based on how many minerals they sold in the store.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "Mine.h"
//#include "Inventory.h"

#define GridSize 12// Grid Size of the  game
#define Max_Cells 3// Max number of impassable cells

// Function to set the player's position
void setPlayerPosition(HPM *player, int x, int y){
    player->pos.x = x;
    player->pos.y = y;
}

int main() {
    srand(time(NULL));// Seed the random number generator

    Cell grid[GridSize][GridSize];// Call out the Cell grid here to make sure the code runs without errors
    HPM player;// Call the HPM Function
    Position pos = {0, 0};// Set the initial position of the player
    Minerals mineral;// Call out the Mineral function
    int n;// For use in selecting of a difficulty
    int x;// Delared to enable users to choose where they would like to go to
    char ch;
    char file;// For printing out the words that are saved in a text file

    player.goldmined = 0;// Declare and initialize the gold mined to 0 since we can not do it like other structs
    player.silvermined = 0;// Declare and initialize the silver mined to 0
    player.diamondmined = 0;// Declare and initialize the diamond mined to 0

    // Code used in printing out text from a text file
//     FILE *ptr;
//
//     ptr = fopen("oreopolis.txt", "r");
//     if (NULL == ptr) {
//         printf("File can't be opened \n");
//         return 1;
//     }
//     printf(" \n");
//
//     while (!feof(ptr)) {
//         file = fgetc(ptr);
//         printf("%c", file);
//     }
//     fclose(ptr);

     //Prompt the user to select a difficulty and store it
    printf("Please select a Difficulty:\n[1]Easy\n[2]Medium\n[3]Hard\n");
    scanf("%d", &n);

    //When the user chooses between 1 and 3 there are some code below that will run
    if (n >= 1 && n <= 3) {
        if (n == 1) {
            player.Hp = 10.0;// Player's Hp initialized at the start of the game to be 10 since it is on Easy mode
            player.Money = 100;// Player's Money initialized at the start of the game to be 100
            //Print out the player's money and hp
            printf("HP: %.1f\n", player.Hp);
            printf("Player's Money: %d\n", player.Money);
        } else if (n == 2) {
            player.Hp = 5.0;// Player's Hp initialized at the start of the game to be 5 since it is on Medium mode
            player.Money = 75;// Player.s money initially initialized to 75
            //Print out the player's money and hp
            printf("HP: %.1f\n", player.Hp);
            printf("Player's Money: %d\n", player.Money);
        } else {
            player.Hp = 3.0;// Player's Hp initialized at the start of the game to be 3 since it is on Hard mode
            player.Money = 50;// player's money initialized to 50
            //Print out the player's money and hp
            printf("HP: %.1f\n", player.Hp);
            printf("Player's Money: %d\n", player.Money);
        }
    } else {
        printf("Invalid Input\n");// If none of the numbers from 1 to 3 were not picked out print invalid input
        return 0;
    }
    getchar();

    //Prompt the user on where they would like to go
    printf("Where would you like to go:\n[1]Mine\n[2]Check Inventory\n");
    scanf("%d", &x);

    // Place a while loop inside another while loop because when the player quits that is the end so this part of the code asks again until you tell it to quit
    while (1) {
        printf("Where would you like to go:\n[1]Mine\n[2]Check Inventory\n[0]Quit\n");//Prompt the user on where they would like to go
        scanf(" %c", &ch);

        //Based on what the user inputs use a switch function to make it so that whatever the user picks they will be an underlying code on what to do
        switch (ch) {
            case '1':
                setPlayerPosition(&player, 0, 0);// Call the function of setplayerposition to set the player's position
                Mine(grid, player);//Call the Mine function
                //Call out the following functions

                while (1) {
                    char direction;// Initialize a character
                    printf("Enter direction(0 to quit and 2 for the store):\n");// Prompt the user for an input
                    scanf(" %c", &direction);

                    // Based on the number or value to user inputs the underlying code will stop the function and quit the game
                    if (direction == '0') {
                        break;
                    }
                        if(player.Hp == 0){
                            printf("Hp has finished. Sell Minerals mined to see if you have won or lost the game\n");
                            inventory(&player);
                       break;
                        }

                        if(direction == '2') {
                            inventory(&player);
                            break;
                        }
                        //Calling out the functions
                    moveplayer(grid, &player, direction);
                    printgrid(grid, player);
                    Minecell(grid, &player);
                }
                break;
            case '2':
                showinventory(&player);// Calling the show inventory function
                break;
            case '0':
                printf("Goodbye!\n");// When they finally pick 0 end the game finally
                return 0;
            default:
                printf("Invalid Input\n");
                return 0;
                break;
        }
    }
}