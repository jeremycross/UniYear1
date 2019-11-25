#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int emailCheck(char* email){

    int index = 0; /*tracks index of array*/
    int nameLen = 0;
    int domLen = 0;
    int tldLen = 0;

    while(index < strlen(email) && email[index] != '@'){ /*increment name length until end of string or '@' is reached*/
        index++;
        nameLen++;
    }

    index++; /*Move index one forward from '@', if loop above was exited because '@' was reached, this allows algorithm to work properly*/

    while(index < strlen(email) && email[index] != '.'){ /*increment domain length until end of string or '.' is reached*/
        index++;
        domLen++;
    }

    index++; /*Move index one forward from '.', if loop above was exited because '.' was reached, this allows algorithm to work properly*/

    while(index < strlen(email)){ /*increment tld length until end of string*/
        index++;
        tldLen++;
    }

    if(nameLen > 0 && domLen > 0 && tldLen > 0){ /*If name length, domain length and tld length are all greater than 0, valid email and return 1*/
        return 1;
    }

    return 0; /*invalid email*/
}

int checkPhoneNum(char *number){

    int allNumeric = 1; /*Tracks if all digits are numeric*/
    int i;

    for(i = 0; i < strlen(number); i++){
        if(isdigit(number[i]) == 0 && allNumeric != 0){ /*If current character is not a digit (0-9) and this if statement hasn't run before, set allNumeric to 0 (false)*/
            allNumeric = 0;
        }
    }

    if(allNumeric == 1 && (strlen(number) == 7 || strlen(number) == 10)){ /*If all digits are numeric and length is 7 or 10, valid and return 1*/
        return 1;
    }

    return 0; /*Invalid phone number*/
}

char* userInput(char* ans){

    char *c = malloc(sizeof(char) *2);
    int count = 0;

    c[1] = '\0';
    ans = realloc(ans, sizeof(char) *2);
    strcpy(ans, "");

    do{
        count++;
        c[0] = fgetc(stdin);
        ans = realloc(ans, sizeof(char)*(count + 1));
        strcat(ans, c);

    }while(c[0] != '\n');

    ans[count-1] = '\0'; /*Trim off newline character*/

    free(c); /*Free malloc'd variable*/

    return ans;
}


int main(){

    char* email = malloc(sizeof(char));
    char* pNum = malloc(sizeof(char));

    do{
        printf("Enter an email:");
        email = userInput(email);


    }while(emailCheck(email) == 0);

    do{
        printf("Enter a phone number: ");
        pNum = userInput(pNum);

    }while(checkPhoneNum(pNum) == 0);

    free(email);
    free(pNum);

    return 0;
}
