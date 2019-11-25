#include <stdio.h>

void read3Numbers(int *, int *, int *);
void add3Numbers(int, int, int, int*);

int main(void){
	int num1, num2, num3, sum;

	read3Numbers(&num1, &num2, &num3);

	add3Numbers(num1, num2, num3, &sum);
	printf("\nSum is %d\n", sum);

	return 0;
}


void read3Numbers(int* number1, int* number2, int* number3){
	printf("Enter 3 integers(formatted d d d): ");
	scanf("%d %d %d", &*number1, &*number2, &*number3);

	return;
}

void add3Numbers(int num1, int num2, int num3, int* sum){

	*sum =  num1 + num2 + num3;
}
