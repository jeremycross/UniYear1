#include <stdio.h>

int lastElement(int array[5][4], int row);

int main(){
	int row;
	int finalElement;
        int nov5Onwards [5][4] = { {5,12,19,26},
                                 {6,13,20,27},
                                 {7,14,21,28},
                                 {8,15,22,29},
                                 {9,16,23,30}};

	printf("Enter a value between 0 and 4: ");
	scanf("%d", &row);

	while(row > 4 || row < 0){
		printf("Enter a value between 0 and 4: ");
        	scanf("%d", &row);

	}

	finalElement = lastElement(nov5Onwards, row);

	printf("Final Element of row %d is: %d", row, finalElement);

	return 0;
}

int lastElement(int array[5][4], int row){

	return array[row][3];
}


