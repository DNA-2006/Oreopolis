//
// Created by DNA on 4/29/2024.
//
#ifndef OREOPOLIS_GAME_INVENTORY_H
#define OREOPOLIS_GAME_INVENTORY_H

#endif //OREOPOLIS_GAME_INVENTORY_H

// Structure defintion to help in us using the minerals throughout our code
typedef enum {
    Gold,
    Silver,
    Diamond,
    Obstacle,
    Empty
} Minerals;

// Structure defintion to help in the postion and movement of our player
typedef struct {
    int x;
    int y;
} Position;

//Structure defintion to help in initialzing the grid correctly without errors
typedef struct {
    Minerals mineral;
    int value;
} Cell;

//Structure defintion to help in initialzing the grid correctly without errors
typedef struct {
    float Hp;
    int Money;
    Position pos;
    Minerals mineral;
    int goldmined;
    int silvermined;
    int diamondmined;
} HPM;

// Define a function with an argument player to help the buying and selling of Minerals at the shop
void inventory(HPM *player) {
    int v;// Initialize the following to store the user's input
    printf("Welcome to the Store\n");// Welcome the user
    printf("You must have a money amount of over 200 to win the game \n");// Prompt the user for an input
//    scanf("%d",&v);

     //When the initialzed integer is equal to any of the three the following code prints and use a switch statement and lastly the mined minerals must be greater than 0 if not a message will print out
//    if (v >= 1 && v <= 3) {
//        switch (v){
                if (player->goldmined > 0) {
                    printf("You have sold Gold\n");
                    player->Money += player->goldmined * 30;// Reduce the amount of the mineral mined by one, one of the reasons we initialized the minerals mined to 0
                    player->goldmined = 0;
//                    player->Money+=30;// Increment the player's money by 30
                }else{
                    printf("You do not have any Gold to sell\n");// Print out for when the user has no gold to sell
                }

                if (player->silvermined > 0) {
                    printf("You have sold Silver\n");
                    player->Money += player->silvermined* 20;// Sell the silver minerals with a
                    player->silvermined = 0;
//                    player->Money+=20;
                }else{
                    printf("You do not have any Silver to sell\n");// Print out for when the user has no Silver to sell
                }

                if (player->diamondmined > 0) {
                    printf("You have sold Diamond\n");
                   player->Money += player->diamondmined * 50;// Reduce the amount of the mineral mined by one
                   player->diamondmined = 0;
//                    player->Money+=50;// Increment the player's money by 20
                }else{
                    printf("You do not have any Diamond to sell\n");// Print out for when the user has no Silver to sell
                }
//        }
//    } else if(v == 0){
//        return;// The following else if is used
//    } else {
//        printf("Invalid Input\n");
//    }
    printf("Current Money: %d\n", player->Money);
    if(player->Money < 200){
        printf("You lose\n");
        exit(0);
    }else{
        printf("Congratulations You Win\n");
        exit(0);
    }
}

//Function decalartion to help in checking the player's inventory
void showinventory(HPM *player){
    printf("You currently have %d Gold\n", player->goldmined);
    printf("You currently have %d Silver\n", player->silvermined);
    printf("You currently have %d Diamond\n", player->diamondmined);
}
