#include <stdio.h>
#include <string.h>

int main(){
	int numberToStretch;
	char originalS[50];
	char stretchedS[60];
	int amountStretched = 0;

	printf("Enter a string: ");
	scanf(" %s", originalS);

	printf("Enter a number between 1 and 5: ");
	scanf(" %d", &numberToStretch);


	for(int i = 0; i < strlen(originalS); i++){
		if(i % 2 == 1){
			for(int j = 0; j < numberToStretch; j++){
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
	printf("Stretched String: \n%s\n", stretchedS);



	return 0;
}
