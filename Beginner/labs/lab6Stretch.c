#include <stdio.h>
#include <string.h>

void stretchMe(char [], int, char[]);

int main(){

	char originalS[50];
	char stretchedS[60];
	int numberToStretch;

	printf("Enter a String: ");
	scanf(" %s", originalS);
	printf("Enter a number between 1 and 5: ");
	scanf(" %d", &numberToStretch);
	stretchMe(originalS, numberToStretch, stretchedS);
	printf("Original String = %s *** Stretched String is %s\n", originalS, stretchedS);



	return 0;
}

void stretchMe(char originalS[], int num, char stretchedS[]){

	int amountStretched = 0;

	for(int i = 0; i < strlen(originalS); i++){
                if(i % 2 == 1){
                        for(int j = 0; j < num; j++){
                                stretchedS[amountStretched] = originalS[i];
                                //printf("If: %d:  %c\n", amountStretched, stretchedS[amountStretched]);
                                amountStretched++;
                        }
                }
                else{
                        stretchedS[amountStretched] = originalS[i];
                        //printf("else: I: %d     amt: %d:  %c\n", i, amountStretched, stretchedS[amountStretched]);
                        amountStretched++;
                }

        }

        stretchedS[amountStretched] = '\0';


}
