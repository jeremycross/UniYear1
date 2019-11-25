/************************crossJeremyA3.c**************************
Student Name: Jeremy Cross                    Email Id: jcross04
Date: November 28th, 2018                     Course Name: CIS 1500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
1) I have read and understood the University policy on academic
integrity;
2) I have completed the Computing with Integrity Tutorial on Moodle;
and
3) I have achieved at least 80% in the Computing with Integrity Self
Test.
I assert that this work is my own. I have appropriately acknowledged
any and all material (data, images, ideas or words) that I have used,
whether directly quoted or paraphrased. Furthermore, I certify that
this assignment was prepared by me specifically for this course.
*********************************************************************/
/*********************************************************
                Compiling the program
*********************************************************
The program should be compiled using the following flags:
-std=c99
-Wall
compiling: gcc -Wall -std=c99 crossJeremyA3.c -o asn3
*********************************************************
                Running the Program
*********************************************************
running: ./asn3
make sure to compile program before using this command to run it
*********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid(int, int, int);
int isBoardFull(char [N][N]);
void createInitialBoard(char [N][N]);
void readUserMove(int *, int *);
void printCurrentBoard(char[N][N]);
int getComputerMove(char [N][N], int *, int *, int, int);
int gameWon(char [N][N], char);
int computerPlaysToWin(char [N][N], int * , int * );
void computerPlaysRandom(int * , int * , int , int );
void sumAllDimensions(char [N][N], int [N], int [N], int *, int *);
int memberOf(int , int [N]);
int computerPlaysToBlock(char [N][N], int * , int * );

int main(){

   int userRow, userCol, computerRow, computerCol;
   int taken;
   char board[N][N];
   char winner = 'N';
   
   srand(time(NULL));
    
   printf("This tic-tac-toe board is of size %d by %d\n", N, N);
   
   printf("Player symbol: X \n Computer symbol: O\n\n");

   printf("Here is the board - spaces are indicated by a ?\n");

   createInitialBoard(board);           // create a 3 X 3 board with '?' in each cell 
   
   while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
   {       
       taken = 0;
       
        while (!(taken))                  // loop used to accept valid row and col values from the user
        {
            readUserMove(&userRow, &userCol);                  //get user's move
            printf("You chose row %d and column %d \n", userRow, userCol);
            
            while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))     // validate user's move
            {
                printf("That's is an invalid row or column number - try again\n");
                readUserMove(&userRow, &userCol);
                printf("You chose row %d and column %d \n", userRow, userCol);
            }
                   
            if (board[userRow-1][userCol-1] == '?')           // if cell is unoccupied
            {
                board[userRow-1][userCol-1] = 'X';          // store an X there
                taken = 1;
            }
            else
            {
                taken = 0;                                  // otherwise inform the user to enter values again
                printf("That spot is taken - please try another one\n");
            }
            
        } //end of while (!taken)
    
       if (gameWon(board, 'X'))   // check if the user wins - game will end if the user does win
       {
           printf("Congrats - you won against the computer :)\n");
           winner = 'Y';
       }
       
       else  if (!(isBoardFull(board)))            //check if the board is already full
       {
           taken = 0;
           
           while (!(taken))
           {
                getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1); // get computer's row and col
           
                if (board[computerRow][computerCol] == '?')         // check if the cell is unoccupied
                {
                    board[computerRow][computerCol] = 'O';
                    taken = 1;
    
                }
                else
                {
                    taken = 0;      //That spot is taken - computer - try another one
                }   
           }
           
           printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);
           
           if (gameWon(board, 'O'))               // check if the computer wins - game must end if it does
           {
               printf("Oh the computer won this time :(( think hard next time\n");
               winner = 'Y';
           }  
       }
     
    printCurrentBoard(board);  
    
    printf("\nPress enter to continue \n");             
    getchar();
           
   } //end of while
   
   if (winner != 'Y')
            printf("Game was a tie - no winner!\n\n");
        
   return 0;
}


int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
/* 
  This function determines computer's move in terms of row (computerRow) and column (computerCol)
  and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
  find one, then it calls function computerPlaysRandom in its attempt to place its symbol in
  the same row or column as the user (userRow, userCol)
*/

   int winningSpot = 0;
   int blocked = 1;
   
   winningSpot = computerPlaysToWin(board, computerRow, computerCol);
   
   if (!winningSpot)            // if computer does find a winning spot, then it plays to block the user 
   {
       computerPlaysRandom(computerRow, computerCol, userRow, userCol);
       
       
       
       
       blocked = computerPlaysToBlock(board, computerRow, computerCol);
       if (blocked == 0)
           computerPlaysRandom(computerRow, computerCol, userRow, userCol);
   }
 
   return winningSpot;
}



/*********************************************************
 isInputValid

 In:
    entered - int which is value that was entered by player
              that is either the desired row or column
    minium - lower bound
    maximum - upper bound
 Out:
    returns a 1 if entered is valid and a 0 if entered is invalid
 Post:
    Checks to see if inputted value is between 1 and 3 inclusive
    if it is valid then returns 1 and program continues
    if it is not valid then returns 0 and player is asked to
    enter a new row and column
*********************************************************/
int isInputValid(int entered, int minimum, int maximum){

    if(entered >= minimum && entered <= maximum){
        return 1;
    }
    else{
        return 0;
    }

}


/*******************************************************
 isBoardFull

 In:
    board - 2D character array of the board for the game
 Out:
    returns 0 if board is not full and returns 1 if full
 Post:
    this function is used to check if the board is full
    in order to stop the game in case of a tie
********************************************************/
int isBoardFull(char board[N][N]){

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] == '?'){
                return 0;
            }
        }
    }

    return 1;
}


/********************************************************
 createInitialBoard

 In:
    board - 2D character array of the board for the game
 Out:
    none
 Post:
    Creates a new board for the game by setting all cells
    in the 2D array of the board to '?'and then prints it
*********************************************************/
void createInitialBoard(char board[N][N]){

    //Loop used to set all cells in 2D board array equal to '?'
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = '?';
        }
    }

    //Print Initial Board
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j < N-1){
                printf(" %c |", board[i][j]);
            }
            else{
                printf(" %c", board[i][j]);
            }
        }
        if(i < N-1){
            printf("\n-----------\n");
        }
    }
    printf("\n");

    return;
}


/************************************************************
 readUserMove

 In:
    *userRow - row for the users move (pass by pointer)
    *userCol - column for the users move (pass by pointer)
 Out:
    Although a void function, both userRow and userCol are
    altered in this function to be used in main
 Post:
    Prompts player for the row and column that they wish to place
    their next 'X'
*************************************************************/
void readUserMove(int* userRow, int* userCol){

    printf("Your move - enter numbers between 1 and 3\n\n");
    printf("Enter row number: ");
    scanf("%d", &*userRow);
    printf("Enter column number: ");
    scanf("%d", &*userCol);
    printf("\n");

    return;
}


/***********************************************************
 printCurrentBoard

 In:
    board - 2D character array of the board for the game
 Out:
    none
 Post:
    Prints current Tic Tac Toe board
***********************************************************/
void printCurrentBoard(char board[N][N]){

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j < N-1){
                printf(" %c |", board[i][j]);
            }
            else{
                printf(" %c", board[i][j]);
            }
        }
        if(i < N-1){
            printf("\n-----------\n");
        }
    }
    printf("\n");

    return;
}


/**************************************************************
 gameWon

 In:
    board - 2D character array of the board for the game
    symbol - a character of the last symbol placed on the board
 Out:
    returns a 1 if the game was won and returns a 0 if not won
 Post:
    Checks to see if any of the possible dimensions have won
    after each move from the player and computer, if the game
    has been won a 1 is returned and the game ends, if the game
    is not won then a 0 is returned and the game continues
***************************************************************/
int gameWon(char board[N][N], char symbol){

    //Initializing variables to be used in sumAllDimensions function
    int sumR[N] = {0, 0, 0};
    int sumC[N] = {0, 0, 0};
    int sumLD = 0;
    int sumRD = 0;

    sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD); //Utility function which finds the sum of all possible dimensions to check for win

    if(symbol == 'X'){ //If last played symbol was 'X'
        for(int i = 0; i < N; i++){
            if(sumR[i] == 3 || sumC[i] == 3){ //If sum of any rows or columns equals 3 then player has won game
                return 1;                     //Return 1 means game has been won
            }
        }
        if(sumLD == 3 || sumRD == 3){ //If sum of either diagonal equals 3 then player has won game
            return 1;
        }
    }
    else{
        for(int i = 0; i < N; i++){
            if(sumR[i] == 12 || sumC[i] == 12){ //If sum of any rows or columns equals 12 then computer has won game
                return 1;
            }
        }
        if(sumLD == 12 || sumRD == 12){ //If sum of either diagonal equals 12 then computer won game
            return 1;
        }
    }
    return 0; //If game was not won then 0 is returned
}


/**********************************************************************
 computerPlaysToWin

 In:
    board - 2D character array of the board for the game
    *cRow - row for computer's next move (pass by pointer)
    *cCol - column for computer's next move (pass by pointer)
 Out:
    Returns a 1 if computer is able to play winning move and a 0
    if the computer cannot play winning move. cRow and cCol are
    pass by pointer and hence are altered in this function to be
    used in main
 Post:
    Checks to see if there is a winning move for the computer to play.
    If there is a winning move available the computer's next move
    is then set to that available move and a 1 is returned. If no winning
    move is found, a 0 is returned and another move for the computer is found
    in other functions
************************************************************************/
int computerPlaysToWin(char board[N][N], int* cRow, int* cCol){

    //Initializing variables to be used in sumAllDimensions function
    int sumR[N] = {0, 0, 0};
    int sumC[N] = {0, 0, 0};
    int sumLD = 0;
    int sumRD = 0;

    sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD); //Utility function used to see if a winning move is a available

    for(int i = 0; i < N; i++){
        if(sumR[i] == 8){ //Check Rows  //If sum of a dimension equals 8 then there is a winning move in that dimension
            for(int j = 0; j < N; j++){ //Searches for empty cell in dimension, when empty cell is found set computer's move to that cell
                if(board[i][j] == '?'){
                    *cRow = i;
                    *cCol = j;
                    return 1; //Return 1 since winning move has been found
                }
            }
        }
        else if(sumC[i] == 8){ //Checks columns
            for(int j = 0; j < N; j++){
                if(board[j][i] == '?'){
                    *cCol = i;
                    *cRow = j;
                    return 1;
                }
            }
        }
    }

    if(sumLD == 8){ //Checks Left diagonal
        for(int i = 0; i < N; i++){
            if(board[i][i] == '?'){
                *cRow = i;
                *cCol = i;
                return 1;
            }
        }
    }
    else if(sumRD == 8){ //Checks Right diagonal
        for(int i = 0; i < N; i++){
            if(board[N-1-i][i] == '?'){
                *cRow = N - 1 - i;
                *cCol = i;
                return 1;
            }
        }
    }

    return 0; //If no winning move has been found return 0

}


/****************************************************************
 computerPlaysRandom

 In:
    *cRow - row for computer's next move (pass by pointer)
    *cCol - column for computer's next move (pass by pointer)
    uRow - row for player's last move
    uCol - column for player's last move
 Out:
    Although a void function, both cRow and cCol are
    altered in this function to be used in main
 Post:
    Chooses the computer's next move by randomly generating which
    dimension of the user's previous move to track,
    (diagonal - only if diagonal is able to tracked, row or column),
    tracking that dimension and randomly generating a location
*******************************************************************/
void computerPlaysRandom(int* cRow, int* cCol, int uRow, int uCol){

    int choice = rand()%3;          //Variable to choose whether to play on same Column, row or diagonal as user's last move
    int validDiagonalChoice = 0;    //Tracks which diagonal is able to followed by computer (if centre cell, plays on Left Diagonal
    int validDiag = 0;              //Acts a boolean replacement to make sure that the diagonal choice is valid
    int newLocation = rand()%3;     //Randomly generated number for computers move location

    if(uRow == uCol){ //For all cells on LD, row and column are equal
        validDiag = 1;  //Valid to play on same diagonal
        validDiagonalChoice = 1;  //Track LD
    }
    else if(N-1-uCol == uRow){ //For all cells on RD, row equals N - 1 - column number (when array index)
        validDiag = 1;
        validDiagonalChoice = 2; //Track RD
    }

    if(choice == 2 && validDiag == 1){  //If user move diagonal is able to be followed and choice to follow diagonal was generated
        if(validDiagonalChoice == 1){
            *cRow = newLocation;     //Sets computer's next move row location to randomly generated location
            *cCol = newLocation;     //Sets computer's next move column location to randomly generated location
        }
        else{
            *cRow = N - 1 - newLocation;
            *cCol = newLocation;
        }
    }
    else{
        if(choice ==  0){   //Tracking same Row
            *cRow = uRow;
            *cCol = newLocation;
        }
        else{               //Tracking same Col
            *cRow = newLocation;
            *cCol = uCol;
        }
    }

    return;
}


/*******************************************************************
 sumAllDimensions

 In:
    board - 2D character array of the board for the game
    sumR - an int array of the sum of all rows
    sumC - an int array of the sum of all columns
    *sumLD - sum of diagonal from top left to bottom right (pass by pointer)
    *sumRD - sum of diagonal from bottom left to top right (pass by pointer)
 Out:
    Although a void function,  sumR, sumC, sumLd and sumRD are
    altered in this function to be used in other functions
 Post:
    A function used to sum all dimensions(rows, columns and diagonals)
    that is to be used for the logic of other functions such as computerPlaysToWin
***********************************************************************/
void sumAllDimensions(char board[N][N], int sumR[N], int sumC[N], int* sumLD, int* sumRD){

    int numbers[N][N]; //Array to store board as integer array ('X' = 1, 'O' = 4 and '?' = 0)


    //Create 2D array with int value equivalents
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] == '?'){ //'?' = 0
                numbers[i][j] = 0;
            }
            else if(board[i][j] == 'O'){ //'O' = 4
                numbers[i][j] = 4;
            }
            else{
                numbers[i][j] = 1;   //'X' = 1
            }
        }
    }

    //Sum all rows and columns
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            sumR[i] += numbers[i][j]; //Sum each row
            sumC[j] += numbers[i][j]; //Sum each column
        }
    }

    *sumLD = numbers[0][0] + numbers[1][1] + numbers[2][2]; //Sum all cells on diagonal from top left to bottom right
    *sumRD = numbers[0][2] + numbers[1][1] + numbers[2][0]; //Sum all cells on diagonal from bottom left to top right

    return;
}


/******************************************************************
 memberOf

 In:
    aNum - number to search for
    someArray - int array
 Out:
    Returns a 1 if aNum is in someArray and a 0 if not
 Post:
    Checks if a number is in an integer array, if yes returns 1, if not returns 0
********************************************************************/
int memberOf(int aNum, int someArray[N]){

    for(int i = 0; i < N; i++){
        if(someArray[i] == aNum){ //If aNum is at someArray[i] then return 1 since it exists in array
            return 1;
        }
    }

    return 0;

}


/**************************************************************
 computerPlaysToBlock

 In:
    board - 2D character array of the game board
    *cRow - row of computer's next move (pass by pointer)
    *cCol - column of computer's next move (pass by pointer)
 Out:
    Returns a 1 if a blocking move is available, returns 0 if no
    blocking move is available. cRow and cCol are also pass by pointers
    which are altered in this function to be used in other functions
 Post:
    Checks to see if the computer can block the player from winning on
    their next turn, if there is such a move, then it will be the computer's
    next move and a 1 is returned. If there is no such move then the computer's
    move will be determined from a different function
****************************************************************/
int computerPlaysToBlock(char board[N][N], int* cRow, int* cCol){

    //Initializing variables to be used in sumAllDimensions
    int sumR[N] = {0, 0, 0};
    int sumC[N] = {0, 0, 0};
    int sumLD = 0;
    int sumRD = 0;

    sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD); //Utility function used to see if any winning moves are able to be blocked

    for(int i = 0; i < N; i++){
        if(sumR[i] == 2){                //If sum of a dimension is 2 then 2 'X's have been placed there and the computer is able to block
            for(int j = 0; j < N; j++){  //Searches for empty cell in dimension, when empty cell is found set computer's move to that cell
                if(board[i][j] == '?'){
                    *cRow = i;
                    *cCol = j;
                    return 1; //Return 1 since the computer was able to block
                }
            }
        }
        else if(sumC[i] == 2){
            for(int j = 0; j < N; j++){
                if(board[j][i] == '?'){
                    *cCol = i;
                    *cRow = j;
                    return 1;
                }
            }
        }
    }

    if(sumLD == 2){
        for(int i = 0; i < N; i++){
            if(board[i][i] == '?'){
                *cRow = i;
                *cCol = i;
                return 1;
            }
        }
    }
    else if(sumRD == 2){
        for(int i = 0; i < N; i++){
            if(board[N-1-i][i] == '?'){
                *cRow = N - 1 - i;
                *cCol = i;
                return 1;
            }
        }
    }

    return 0; //If no blocking moves can be performed then return 0

}
