#include <string.h>
#include <stdio.h>

int checkWords(char []);
int checkMax(int, int);

int main(){
    char str[100][50];
    int line = 0;
    char check[3] = ".\n";

    printf("Enter a poem\n");

    while(line < 99){
        fgets(str[line], 50, stdin);

        if(strcmp(str[line], check) == 0){
            break;
        }
        if(checkWords(str[line]) >= 10){
            printf("Please enter line %d again:\n", line+1);
            line--;
        }
        line++;
    }


    return 0;
}


int checkWords(char str1[50]){
    int max = 0;
    int currentSize = 0;

    for(int i = 0; i < strlen(str1); i++){
        if(str1[i] != ' ' && str1[i] != '\n'){
            currentSize++;
            max = checkMax(currentSize, max);
        }
        else{
            currentSize = 0;
        }
    }
    return max;
}

int checkMax(int num1, int num2){
    if(num1 > num2){
        return num1;
    }

    return num2;
}
