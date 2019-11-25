
#include <stdio.h>

int process(int array1[]);

int main(){
	int array1[10];
	int index = 0;

	index = process(array1);


	printf("\n\nPRINT IN MAIN starting from subscript %d\n", index);
	for(int i = index; i < 10; i++){
		printf("%d ", array1[i]);
	}
	printf("\n");

	return 0;
}

int process(int array1[]){
	int index = 0;
	int sum = 0;

	for(int i = 0; i < 10; i++){
                printf("Enter value %d: ", i);
                scanf("%d", &array1[i]);
        }
	printf("PRINTING IN FUNCTION: \n\n");

        for(int i = 0; i < 10; i++){
                printf("%d ", array1[i]);
        }

	printf("\n\n");
        for(int i = 0; i < 10; i++){
                if(sum <= 50){
                        index++;
                        printf("%d ", array1[i]);
                }
                sum += array1[i];
        }

	return index;
}
