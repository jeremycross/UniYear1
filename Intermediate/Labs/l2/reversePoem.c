#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

    char **str;
    int currentString = 0;
    int i;
    char tempString[1001];

    str = malloc(sizeof(char *));

    while(1){
        fgets(tempString, 1000, stdin);
        str[currentString] = malloc(sizeof(char) * (strlen(tempString)+2));
        strcpy(str[currentString], tempString);

        if(str[currentString][0] == '.' && str[currentString][1] == '\n'){
            break;
        }
        currentString++;

        str = realloc(str, sizeof(char *) * (currentString + 1));
    }

    for(i = (currentString-1); i >= 0; i--){
        printf("%s", str[i]);
    }

    for(i = 0; i < (currentString+1); i++){
        free(str[i]);
    }

    free(str);

    return 0;
}

