#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

	srand(time(NULL));

	int random = rand()%101;
	int guess;

	printf("Guess a number between 0 and 100 and enter it here: ");
	scanf("%d", &guess);



	if(guess == random){
		printf("Yes - that is correct :)");
	}
	else if(guess < random){
		printf("You guessed it wrong :(  you should have gone higher.");
	}
	else{
		printf("You guessed it wrong :( you should have gone lower.");
	}

	printf("\n%d", random);






	return 0;
}
