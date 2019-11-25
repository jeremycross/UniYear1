#include <stdio.h>
int main(void){

	double length;
	int choice;

	printf("Enter the length in cms: ");
	scanf("%lf", &length);

	if(length <= 0){
		printf("Incorrect input for length. Goodbye.");
		return 1;
	}
	else{
		printf("What would you like to compute - area or perimeter?\n");
		printf("Enter a choice (1 for Area or 2 for Perimeter)");

		scanf("%d", &choice);

		if(choice != 1 && choice != 2){
			printf("incorrect choice. Goodbye");
			return -1;
		}
		else{
			if(choice == 1){
				printf("The area of a square with length %.0lf is %.2lf cms squared." , length, length*length);
			}
			else{
				printf("The perimeter of a square with length %.0lf is %.2lf cms", length, length*4);
			}

		}

	}





	return 0;
}
