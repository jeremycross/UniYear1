#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/functions.h"


int main(){

    FILE *fp;
    char *answer = malloc(sizeof(char));
    int isFinished = 0;


    /*Main Loop, to exit say No to both questions in a row*/
    do{
        fp = fopen("myContactList.db", "a+b"); /*Do not need to check for fp == NULL, since we create file if not found*/

        do{
            printf("Do you wish to enter a new contact (Yes or No)?: ");
            answer = userInput(answer);

        }while(rePromptCheck(answer) == 1); /*Ensures that Yes or No are entered before leaving loop*/

        if(answer[0] == 'Y' && answer[1] == 'e' && answer[2] == 's' && answer[3] == '\0'){ /*Add a contact*/
            addContact(fp);
        }
        else if(answer[0] == 'N' && answer[1] == 'o' && answer[2] == '\0'){

            do{
                printf("Do you wish to retrieve a contact (Yes or No)?: ");
                answer = userInput(answer);

            }while(rePromptCheck(answer) == 1);

            if(answer[0] == 'Y' && answer[1] == 'e' && answer[2] == 's' && answer[3] == '\0'){ /*Search for contact*/
                searchContact(fp);
            }
            else if(answer[0] == 'N' && answer[1] == 'o' && answer[2] == '\0'){ /*No is said twice in a row, leave loop*/
                isFinished = 1;
            }
        }

        fclose(fp); /*Close file to allow any writing to save*/

    }while(isFinished == 0);


    free(answer);


    return 0;
}
