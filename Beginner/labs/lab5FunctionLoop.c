#include <stdio.h>

void banner();

int main (void){

	int max;

	printf("Enter how many times you want the banner function to run: ");
	scanf("%d", &max);

	for(int i = 0; i < max; i++){
		banner();
	}

	return 0;
}



void banner(){
	int num;

        printf("Please enter a number between 1 and 31: ");
        scanf("%d", &num);
        printf("\n************************************************\n");
        printf("! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !\n");
        printf("************************************************\n");
        printf("Welcome to week 2 lab - your lucky number is %d\n", num);
        printf("************************************************\n");
        printf("! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !\n");
        printf("************************************************\n\n\n");


        printf("\n************************************************\n");
        printf("! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !\n");
        printf("************************************************\n");
        printf("Welcome to week 2 lab - your lucky number is %d\n", num);
        printf("************************************************\n");
        printf("! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !\n");
        printf("************************************************\n\n");
}
