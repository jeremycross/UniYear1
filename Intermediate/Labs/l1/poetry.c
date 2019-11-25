#include <stdio.h>
#include <string.h>

int sumWords(int [], int);
int checkWords(char []);
int checkMax(int, int);
int checkPunct(char []);

int main(){
    char str[100][100];
    int numWords[100] = {0};
    char check[100] = ".\n";
    int line = 0;
    int totalWords = 0;
    int i;
    int j;

    printf("Enter a poem: \n");

    while(line < 99){
        fgets(str[line], 100, stdin);

        if(strcmp(str[line], check) == 0){
            break;
        }
        if(checkWords(str[line]) > 10){
            printf("Does not comply with constraints(Word longer than 10 characters). Please enter line %d again:\n", line+1);
            line--;
        }
        else if(checkPunct(str[line]) == 1){
            printf("Does not comply with constraints(Punctuation used). Please enter line %d again:\n", line+1);
            line--;
        }
        else if(strlen(str[line]) > 50){
            printf("Does not comply with constraints(Line longer than 50 characters). Please enter line %d again:\n", line+1);
            line--;
        }
        line++;
    }

    for(i = 0; i < line; i++){
        for(j = 0; j < strlen(str[i]); j++){
            if(str[i][j] == ' ' || str[i][j] == '\n'){
                numWords[i]++;
            }
        }
    }

    totalWords = sumWords(numWords, line);

    if(totalWords == 1 && line == 1){
        printf("%d word on %d line\n", totalWords, line);
    }
    else if(line == 1){
        printf("%d words on %d line\n", totalWords, line);
    }
    else{
        printf("%d words on %d lines\n", totalWords, line);
    }

    for(i = 0; i < line; i++){
        printf("%d ", numWords[i]);
    }

    printf("\n");

    return 0;
}



int sumWords(int numWords[100], int numLines){

    int sum = 0;
    int i;

    for(i = 0; i < numLines; i++){
        sum += numWords[i];
    }

    return sum;
}

int checkWords(char str1[100]){
    int max = 0;
    int currentSize = 0;
    int i;

    for(i = 0; i < strlen(str1); i++){
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

int checkPunct(char str1[100]){

    int i;

    for(i = 0; i < strlen(str1); i++){
        if(str1[i] == '?' || str1[i] == '!' || str1[i] == '.' || str1[i] == ','){
            return 1;
        }
    }

    return 0;
}
