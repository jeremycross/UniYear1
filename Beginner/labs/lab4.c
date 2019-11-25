#include <stdio.h>

void loopGreeting(int max);

int main (){

	int mainfor;
	int greetfor;
	int numOLoops;
	int guess;

	printf("Enter two number to tell the program how many times the greeting should print (formatted: 'num1 num2')");
	scanf("%d %d", &mainfor, &greetfor);
	printf("How many times will the greeting print\n");
	scanf("%d", &guess);

	numOLoops = mainfor*greetfor;

	for(int i = 0; i < mainfor; i++){
                loopGreeting(greetfor);
        }


	if(guess == numOLoops){
		printf("Correct! The loop is executed %d times\n", numOLoops);
	}
	else{
		printf("Sorry that guess was incorrect, the loop will execute %d * %d times for a total of %d times\n", mainfor, greetfor, numOLoops);
	}


	return 0;
}


void loopGreeting(int max){

	for(int i = 0; i < max; i++){
		printf("Hello\n");
	}
}
