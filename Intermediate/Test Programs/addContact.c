#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct contact{
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;

}contact;

char* userInput(char* ans, FILE* stream){

    char *c = malloc(sizeof(char) *2);
    int count = 0;

    c[1] = '\0';
    ans = realloc(ans, sizeof(char) *2);
    strcpy(ans, "");

    do{
        count++;
        c[0] = fgetc(stream);
        ans = realloc(ans, sizeof(char)*(count + 1));
        strcat(ans, c);
    }while(c[0] != '\n');

    ans[count-1] = '\0'; /*Trim off newline character*/
    printf("Length of ans %lu\n", strlen(ans));

    free(c); /*Free malloc'd variable*/

    return ans;
}

int main(){

    FILE* fp;
    long currPosn;
    char* fName = malloc(sizeof(char));
    char* lName = malloc(sizeof(char));
    char* comName = malloc(sizeof(char));
    char* pNumber = malloc(sizeof(char));
    char* email = malloc(sizeof(char));
    contact* cont1 = malloc(sizeof(contact));

    fp = fopen("test.db", "a+b");
    fseek(fp, 0, SEEK_END);

    /*Take in contact info*/
    printf("First Name: ");
    fName = userInput(fName, stdin);

    printf("Last Name: ");
    lName = userInput(lName, stdin);

    printf("Company Name: ");
    comName = userInput(comName, stdin);

    do{
        printf("Phone Number (enter only numbers): ");
        pNumber = userInput(pNumber, stdin);

    }while(strlen(pNumber) == 0); /*Ensure a phone number is entered, or else ask for it again*/

    printf("Email: ");
    email = userInput(email, stdin);

    cont1->phone_number = strtoul(pNumber, NULL, 10); /*Add entered phone number to struct*/

    currPosn = ftell(fp) + sizeof(contact); /*Find current position in file*/

    /*Position elements*/
    cont1->first_name_posn = (strlen(fName) == 0 ? 0 : currPosn);
    currPosn += strlen(fName) + (strlen(fName) == 0 ? 0 : 1);

    printf("fNP = %ld\n", cont1->first_name_posn);

    cont1->last_name_posn = (strlen(lName) == 0 ? 0 : currPosn);
    currPosn += strlen(lName) + (strlen(lName) == 0 ? 0 : 1);

    printf("lNP = %ld\n", cont1->last_name_posn);

    cont1->company_name_posn = (strlen(comName) == 0 ? 0 : currPosn);
    currPosn += strlen(comName) + (strlen(comName) == 0 ? 0 : 1);

    printf("cNP = %ld\n", cont1->company_name_posn);

    cont1->email_posn = (strlen(email) == 0 ? 0 : currPosn);
    currPosn += strlen(email) + (strlen(email) == 0 ? 0 : 1);

    printf("eP = %ld\n", cont1->email_posn);

    cont1->next = currPosn;

    printf("next = %ld\n", cont1->next);

    fwrite(cont1, sizeof(contact), 1, fp);

    if(strlen(fName) != 0){
        fwrite(fName, sizeof(char), strlen(fName)+1, fp);
    }
    if(strlen(lName) != 0){
        fwrite(lName, sizeof(char), strlen(lName)+1, fp);
    }
    if(strlen(comName) != 0){
        fwrite(comName, sizeof(char), strlen(comName)+1, fp);
    }
    if(strlen(email) != 0){
        fwrite(email, sizeof(char), strlen(email)+1, fp);
    }

    printf("Written stuff\n");

    /*Free all pointers*/
    fclose(fp);
    free(cont1);
    free(fName);
    free(lName);
    free(comName);
    free(pNumber);
    free(email);

    return 0;
}
