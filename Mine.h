//
// Created by DNA on 4/29/2024.
//

#ifndef OREOPOLIS_GAME_MINE_H
#define OREOPOLIS_GAME_MINE_H

#endif //OREOPOLIS_GAME_MINE_H
#include "Inventory.h"
#define GridSize 12// Grid Size of the game
#define Max_Cells 3// Maximum number of impassable cells

//Function to initialize the grid
void initializegrid(Cell grid[GridSize][GridSize]) {
    for (int i = 0; i < GridSize; ++i) {
        for (int j = 0; j < GridSize; ++j) {
            grid[i][j].mineral = Empty;
            grid[i][j].value = 0;
        }
    }
}

//Function to place obstacles randomly in the grid
void placeobstacles(Cell grid[GridSize][GridSize]) {
    for (int i = 0; i < Max_Cells; ++i) {
        int x = rand() % GridSize;
        int y = rand() % GridSize;
        grid[y][x].mineral = Obstacle;// TO place an obstacle at a randomly generated place
    }
}

// FUnction to place minerals without it interfering with other minerals and obstacles
void placeminerals(Cell grid[GridSize][GridSize]) {
    for (int i = 0; i < Max_Cells; ++i) {
        int x = rand() % GridSize;
        int y = rand() % GridSize;
        if (grid[y][x].mineral == Empty)
            grid[y][x].mineral = Gold;
    }

    for (int i = 0; i < Max_Cells; ++i) {
        int x = rand() % GridSize;
        int y = rand() % GridSize;
        if (grid[y][x].mineral == Empty)
            grid[y][x].mineral = Silver;
    }

    for (int i = 0; i < Max_Cells; ++i) {
        int x = rand() % GridSize;
        int y = rand() % GridSize;
        if (grid[y][x].mineral == Empty)
            grid[y][x].mineral = Diamond;
    }
}

// Function to print the grid and player out
void printgrid(Cell grid[GridSize][GridSize], HPM player) {
    for (int i = 0; i < GridSize; ++i) {
        for (int j = 0; j < GridSize; ++j) {
            if (i == player.pos.y && j == player.pos.x)
                printf("P");
            else if (grid[i][j].mineral == Empty)
                printf(".");
            else if (grid[i][j].mineral == Gold)
                printf("G");
            else if (grid[i][j].mineral == Silver)
                printf("S");
            else if (grid[i][j].mineral == Diamond)
                printf("D");
            else if (grid[i][j].mineral == Obstacle)
                printf("O");
        }
        printf("\n");
    }
}

// This function helps in moving the player, reducing Hp based on you moving and error handling in case of the player trying to move out of bounds
void moveplayer(Cell grid[GridSize][GridSize], HPM *player, char direction){
    int dirX = player->pos.x;// Defining and initializing the player's position to a variable because of the error handling
    int dirY = player->pos.y;// Defining and initializing the player's position to a variable because of the error handling

    // Switch statemnt to check what the user inputted and using that to move the player in a given direction
    switch(direction){
        case '8':
            player->pos.y--;//Up
            break;
        case '2':
            player->pos.y++;// Down
            break;
        case '6':
            player->pos.x++;// Right
            break;
        case '4':
            player->pos.x--;// Left
            break;
        default:
            printf("Invalid Direction\n");// Invalid direction if you input any number apart from the above
            return;
    }

    player->Hp -= 0.5;// Reduce player's Hp by 0.5 for every move played

    // Error handling for if you encounter an obstacle or move out of boundaries
    if(player->pos.x >= 0 && player->pos.x < GridSize && player->pos.y >= 0 && player->pos.y < GridSize){

        // If you either an obstacle or you try to move out of bounds the player will not move.
        if(grid[player->pos.y][player->pos.x].mineral == Obstacle) {
            printf("Cannot move: There is an Obstacle\n");
            player->pos.x = dirX;
            player->pos.y = dirY;
        }
    }else{
        printf("Cannot move out of bounds\n");
        player->pos.x = dirX;
        player->pos.y = dirY;
    }
    printf("HP: %.1f\n", player->Hp);// Print out the decremented Hp
}

//Function used in mining minerals and making sure the player cannot move past obstacles
void Minecell(Cell grid[GridSize][GridSize], HPM *player){
    // Checking for if the minerals are either gold, silver and diamond
    if(grid[player->pos.y][player->pos.x].mineral == Gold || grid[player->pos.y][player->pos.x].mineral == Silver || grid[player->pos.y][player->pos.x].mineral == Diamond){
        switch(grid[player->pos.y][player->pos.x].mineral){
            case Gold:
                printf("Mined Gold\n");// Prompt the user that gold has been mined once you mine it
                player->goldmined++;// Increase your gold mineral by one
                break;
            case Silver:
                printf("Mined Silver\n");// Prompt the user that silver has been mined once it is type of mineral mined
                player->silvermined++;// Increase silver by one
                break;
            case Diamond:
                printf("Mined Diamond\n");// Prompt the user that diamond has been mined
                player->diamondmined++;// Increment diamond
                break;
            default:
                break;
        }
        grid[player->pos.y][player->pos.x].mineral = Empty;// Once the mineral has mined set the place were it was mined to empty
        // Checking if the mineral mined is an obstacle, if it is you cannot mine
    }else if(grid[player->pos.y][player->pos.x].mineral == Obstacle){
        printf("Cannot mine\n");
    }else{
        printf("No minerals\n");
    }
    printf("Gold: %d\n",player->goldmined);
    printf("Silver: %d\n",player->silvermined);
    printf("Diamond: %d\n", player->diamondmined);
}

// Calling out the functions in a function called mine
void Mine(Cell grid[GridSize][GridSize], HPM player) {
    // Statement added to tell the user that when the Hp reaches zero the hp has finished
    if(player.Hp <= 0){
        printf("Hp has finished\n");
        return;
    }
    initializegrid(grid);
    placeobstacles(grid);
    placeminerals(grid);
    printgrid(grid, player);
}
