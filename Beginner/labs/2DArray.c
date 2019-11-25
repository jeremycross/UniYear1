#include <stdio.h>
#include <string.h>

void print2DArray(int array[5][4]);
int main (){
	int nov5Onwards [5][4] = { {5,12,19,26},
				 {6,13,20,27},
				 {7,14,21,28},
				 {8,15,22,29},
				 {9,16,23,30}};


	print2DArray(nov5Onwards);


	return 0;
}

void print2DArray(int array[5][4]){
	char days[5][10];
	strcpy(days[0], "Monday");
	strcpy(days[1], "Tuesday");
	strcpy(days[2], "Wednesday");
	strcpy(days[3], "Thursday");
	strcpy(days[4], "Friday");

	for(int i = 0; i < 5; i++){
		printf("%s:", days[i]);
		for(int j = 0; j < 4; j++){
			printf("%d ", array[i][j]);
		}
		printf("\n");

	}


}
