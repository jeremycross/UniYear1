/************************crossJeremyA2.c **************************
Student Name: Jeremy Cross                    Email Id: jcross04
Date: November 3rd, 2018                      Course Name: CIS 1500
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
compiling: gcc -Wall -std=c99 crossJeremyA2.c -o asn2
*********************************************************
                Running the Program
*********************************************************
running: ./asn2
make sure to compile program before using this command to run it
*********************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_QUESTIONS 7

//function prototypes

void promptPlayerForName (char [50]);
void printWelcomeMessage (char  [50]);
int  calculateCurrentAward (int ,int);
void popUpCurrentQuestion4choices (int);
char askPlayerForLifeLine (void);
void popUpCurrentQuestion2choices (int);
char acceptPlayersFinalAnswer (void);
bool isCorrectFinalAnswer (char, int, char [MAX_QUESTIONS]);
void generateRandomGreeting (char [20]);
int calculateReducedAward (int, int);

int main(){

	char allCorrectAnswers [MAX_QUESTIONS + 1] = "CBCBACA";   // for my set of questions
	char greet [20];
	char nameForGame[50];
	int lifeLineUsed = 0;
	int questionNumber = 1;
	char playersResponseLifeLine;
	char finalAnswer;
	int currentAwardAmount ;
   	int reducedAmount;

	promptPlayerForName(nameForGame);

	printWelcomeMessage(nameForGame);

	while (questionNumber <= MAX_QUESTIONS){
		currentAwardAmount = calculateCurrentAward(questionNumber, currentAwardAmount);

		popUpCurrentQuestion4choices(currentAwardAmount);

		if (lifeLineUsed == 0){
			playersResponseLifeLine = askPlayerForLifeLine();

			if (playersResponseLifeLine == 'Y' || playersResponseLifeLine == 'y'){

				popUpCurrentQuestion2choices(currentAwardAmount);
				lifeLineUsed ++;
				printf("\nReminder - You get only 1 50-50 lifeline - and you are using it now \n\n");
			}
		}

		finalAnswer = acceptPlayersFinalAnswer ();

		if (isCorrectFinalAnswer (finalAnswer, questionNumber, allCorrectAnswers) ){

		 	generateRandomGreeting(greet);
			printf("%s - You just won $ %d\n", greet, currentAwardAmount);

			if (questionNumber < MAX_QUESTIONS){
				printf("Let us play the next question now\n\n");
			}
		}

		else {
			printf  ("Oops - that was incorrect.");

                        reducedAmount = calculateReducedAward (questionNumber, currentAwardAmount);

			printf("You still won $%d. Well done.\n\n", reducedAmount);

	                questionNumber = MAX_QUESTIONS;
		}
		questionNumber ++;
	}

	printf("It was fun playing with you \n\n");

	return 0;

}

/********************************************
promptPlayerForName
In:
	fullName - a string which stores the player's name
Out:
	none
Post:
	Asks player for their first and last name that is to be printed in the welcome message
**********************************************/
void promptPlayerForName(char fullName[]){
	char lastName[25];
	printf("Enter your first name: ");
	scanf("%s", fullName);
	strcat(fullName, " "); //Adds a space to end of first name entered

	printf("Enter your last name: ");
	scanf("%s", lastName);
	strcat(fullName, lastName);

	return;
}

/**********************************************
printWelcomeMessage
In:
	fullName - a string which stores the player's name
Out:
	none
Post:
	Prints a welcome message for the player
***********************************************/
void printWelcomeMessage(char fullName[]){
	printf("*\n");
	printf("**\n");
	printf("***\n");

	for(int i = 0; i < strlen(fullName) + 8; i++){
		printf("*"); //Runs a different amount of times depending on the inputted name
	}
	printf("\nWelcome %s\n", fullName);
	printf("Let us play WDWM!\n");

	for(int i = 0; i < strlen(fullName) + 8; i++){
                printf("*");
        }
	printf("\n***\n");
	printf("**\n");
	printf("*\n\n");

	return;
}

/*****************************************
calculateCurrentAward
In:
	questionNumber - an integer which stores the number of the current question
	awardPreviousQuestion - an integer which stores the previous award amount
Out:
	currentAward - an integer which stores the current award amount
Post:
	currentAward is calculated and returned based on question number and previous award amount
******************************************/
int calculateCurrentAward(int questionNumber, int awardPreviousQuestion){
	int currentAward;

	if(questionNumber == 1){
		currentAward = 100;
	}
	else{
		if(questionNumber % 2 == 0){
			currentAward = awardPreviousQuestion * 5; //if odd numbered question multiply previous award by 5
		}
		else{
			currentAward = awardPreviousQuestion * 2; //if even numbered question multiply previous award by 2
		}

	}
	return currentAward;
}


/******************************************
popUpCurrentQuestion4Choices
In:
	currentAwardAmount - an integer value of the award amount for the current question
Out:
	none
Post:
	Prints out the current question with all 4 options for answers
*******************************************/
void popUpCurrentQuestion4choices(int currentAwardAmount){

	printf("Here is the $ %d question\n\n", currentAwardAmount);

	if(currentAwardAmount == 100){
		printf("Which of the following programming language is taught in CIS1500 at the University of Guelph?\n");
		printf("A. Python				B. Cobra\n");
		printf("C. C 					D. Java\n\n");
	}
	else if(currentAwardAmount == 500){
		printf("Which Canadian chain first opened in Hamilton in 1964?\n");
		printf("A. McDonalds  				B. Tim Hortons\n");
		printf("C. Wendys     				D. Mr. Sub\n\n");
	}
	else if(currentAwardAmount == 1000){
		printf("What is Canada's national sport?\n");
		printf("A. Hockey  				B. Lacrosse\n");
		printf("C. Hockey and Lacrosse 			D. Baseball\n\n");
	}
	else if(currentAwardAmount == 5000){
		printf("Which Canadian city ranks as the most educated in the country?\n");
		printf("A. Montreal 				B. Ottawa\n");
		printf("C. Vancouver 				D. Toronto\n\n");
	}
	else if(currentAwardAmount == 10000){
		printf("What is Canada's highest mountain?\n");
		printf("A. Mount Logan, Yukon 			B. Whistler Mountain, BC\n");
		printf("C. Mont Tremblant, Quebec  		D. Tip Top Mountain, Ontario\n\n");
	}
	else if(currentAwardAmount == 50000){
		printf("What is the easternmost province of Canada?\n");
		printf("A. Ontario 				B. Prince Edward Island\n");
		printf("C. Newfoundland 			D. Nova Scotia\n\n");
	}
	else{
		printf("The southernmost point of mainland Canada is called Point Pelee. What province is it in?\n");
		printf("A. Ontario 				B. Quebec\n");
		printf("C. Newfoundland				D. Nova Scotia\n\n");
	}

	return;
}


/**********************************************
askPlayerForLifeLine
In:
	none
Out:
	respone - a character for the player's response to if they want to use 50-50 lifeline
Post:
	Asks player if they want to use lifeline, will not accept any answer other than 'Y' or 'y'(yes) 'N' or 'n'(no)
**********************************************/
char askPlayerForLifeLine(){
	char response;
	printf("Would you like to use a lifeline (50-50)?\n");
	printf("Enter Y or y, N or n: ");
	scanf(" %c", &response);

	while(response != 'Y' && response != 'y' && response != 'N' && response != 'n'){
		printf("\nInvalid option entered\n\n");//This loop will continually ask for an input until a correct one is entered

		printf("Enter Y or y, N or n: ");
		scanf(" %c", &response);
	}
	printf("\n");

	return response;
}


/**************************************
popUpCurrentQuestion2Choices
In:
	currentAwardAmount - an integer that stores the value of the award for the current question
Out:
	none
Post:
	If player used their lifeline this function will run, two of the possibile answers for the current question are restated
	(one correct and the other wrong)
****************************************/
void popUpCurrentQuestion2choices(int currentAwardAmount){
	printf("\nOK - here are your choices after using the 50-50 lifeline\n\n");

	if(currentAwardAmount == 100){
                printf("A. Python\n");
                printf("C. C\n");
        }
        else if(currentAwardAmount == 500){
                printf("A. McDonalds\n");
                printf("B. Tim Hortons\n");
        }
        else if(currentAwardAmount == 1000){
                printf("B. Lacrosse\n");
                printf("C. Hockey and Lacrosse\n");
        }
        else if(currentAwardAmount == 5000){
                printf("B. Ottawa\n");
                printf("D. Toronto\n");
        }
        else if(currentAwardAmount == 10000){
                printf("A. Mount Logan, Yukon\n");
                printf("D. Tip Top Mountain, Ontario\n");
        }
	else if(currentAwardAmount == 50000){
                printf("B. Prince Edward Island\n");
                printf("C. Newfoundland\n");
        }
        else{
                printf("A. Ontario\n");
                printf("B. Quebec\n");
        }

	return;
}


/*********************************************
acceptPlayersFinalAnswer
In:
	none
Out:
	answer - a character which stores the players response to the multiple choice question
Post:
	Prompts player for their final answer to the current question, continues to ask player for final answer until a correct response of an
	'A','B','C' or 'D' is inputted
**********************************************/
char acceptPlayersFinalAnswer(){
	char answer;

	printf("Enter your FINAL ANSWER ('A', 'B', 'C' OR 'D') here: ");
	scanf(" %c", &answer);

	while(answer != 'A' && answer != 'B' && answer != 'C' && answer != 'D'){
		printf("Enter your FINAL ANSWER('A', 'B', 'C' OR 'D') here: "); //this loop will run until a correct input is entered
        	scanf(" %c", &answer);
	}
	printf("\n");

	return answer;
}


/*********************************************
isCorrectFinalAnswer
In:
	finalAnswer - a character that stores the player's final answer to the current question
	questionNumber - an integer that stores the current question number
	allCorrectFinalAnswers - an array of characters that stores the correct final answer for all of the questions
Out:
	boolean - a 1(True) or a 0(False) depending on if finalAnswer was correct
Post:
	Checks if player's final answer to current question is correct, if correct returns a true (1) and if wrong returns a false (0)
*********************************************/
bool isCorrectFinalAnswer(char finalAnswer, int questionNumber, char allCorrectAnswers[]){

	if(finalAnswer == allCorrectAnswers[questionNumber - 1]){ //checks if final answer from user is the same as the correct answer
		return 1; //TRUE is returned for boolean
	}
	else{
		return 0; //FALSE is returned for boolean
	}
}


/*******************************************
generateRandomGreeting
In:
	greet - an string which stores a random greeting
Out:
	none
Post:
	Uses a random number to change greet to a random congratulatory statement
********************************************/
void generateRandomGreeting(char greet[]){
	int random;

	random = (rand() % 5) + 1; //Generates a random number from 1-5

	switch (random){
		case 1:
			strcpy(greet, "Bravo"); //if random number is 1
			break;
		case 2:
			strcpy(greet, "Congrats");
			break;
		case 3:
			strcpy(greet, "Well done");
			break;
		case 4:
			strcpy(greet, "Very nice");
			break;
		default:
			strcpy(greet, "Proud of you");
			break;
	}

	return;
}


/*********************************************
calculateReducedAward
In:
	questionNumber - an integer that stores the current question number
	currentAwardAmount - an integer value of the award amount for the current question
Out:
	reducedAward - an integer value that stores the reduced award amount
Post:
	If the player gets the current question wrong the reduced award amount is calculated based on the current award and question number
*********************************************/
int calculateReducedAward(int questionNumber, int currentAwardAmount){
	int reducedAward;

	if(questionNumber == 1){
		reducedAward = 100; //100 is the minimum prize, this will occur if they get question 1 wrong
	}
	else if(questionNumber % 2 == 0){
		reducedAward = currentAwardAmount / 5;
	}
	else{
		reducedAward = currentAwardAmount / 2;
	}

	return reducedAward;
}
