
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/struct.h"

/****************************************************
 rePrompCheck

 In:
    ans - char pointer (string)

 Out:
    returns 1 or 0

 Post:
    checks to see if inputted string is Yes or No,
    if it is not return 1, if it is return 0
****************************************************/
int rePromptCheck(char* ans){

    if(!(ans[0] == 'Y' && ans[1] == 'e' && ans[2] == 's' && ans[3] == '\0') && !(ans[0] == 'N' && ans[1] == 'o' && ans[2] == '\0')){
        return 1; /*Return 1 is not Yes or No*/
    }

    return 0; /*ans is Yes or No, return 0*/

}

/***************************************************
 userInput

 In:
    ans - char pointer (string)

 Out:
    ans - char pointer (string)

 Post:
    Takes inputted string from stdin, and stores into
    a dynamically allocated string, this string is then
    returned
***************************************************/
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

/***************************************************
 printFromFile

 In:
    stream - file to be read from

 Out:
    none

 Post:
    Given a file to read from, reads from current position
    in file and prints as it goes, reads until a null character
    is reached
***************************************************/
void printFromFile(FILE* stream){

    char c;

    do{
        c = fgetc(stream);
        printf("%c", c);

    }while(c != '\0');


    return;
}

/*************************************************
 addContact

 In:
    fp - file pointer of file being written to

 Out:
    none

 Post:
    Prompts user for information of contact, only
    phone number is needed meanwhile all others
    are optional. Calculates where strings not in
    struct contact will be written and writes all
    of this info to inputted file pointer. If a
    field is left blank (besides phone number)
    its respective position in the struct is set to
    0 and it is not written to the file.
*************************************************/
void addContact(FILE* fp){

    long currPosn;
    char* fName = malloc(sizeof(char));
    char* lName = malloc(sizeof(char));
    char* comName = malloc(sizeof(char));
    char* pNumber = malloc(sizeof(char));
    char* email = malloc(sizeof(char));
    contact* cont1 = malloc(sizeof(contact));

    fseek(fp, 0, SEEK_END);

    /*Take in contact info*/
    printf("First Name: ");
    fName = userInput(fName);

    printf("Last Name: ");
    lName = userInput(lName);

    printf("Company Name: ");
    comName = userInput(comName);

    do{
        printf("Phone Number (enter only numbers): ");
        pNumber = userInput(pNumber);

    }while(strlen(pNumber) == 0); /*Ensure a phone number is entered, or else ask for it again*/

    printf("Email: ");
    email = userInput(email);

    cont1->phone_number = strtoul(pNumber, NULL, 10); /*Add entered phone number to struct*/

    currPosn = ftell(fp) + sizeof(contact); /*Find current position in file, this variable will be used to predict where strings will be written*/

    /*Position elements*/
    cont1->first_name_posn = (strlen(fName) == 0 ? 0 : currPosn); /*If first Name was left blank set its respective position to 0*/
    currPosn += strlen(fName) + (strlen(fName) == 0 ? 0 : 1); /*If first name was not left blank add one to currPosn, to account for \0 that will be written to file*/

    cont1->last_name_posn = (strlen(lName) == 0 ? 0 : currPosn); /*If last Name was left blank set its respective position to 0*/
    currPosn += strlen(lName) + (strlen(lName) == 0 ? 0 : 1); /*If last name was not left blank add one to currPosn to account for \0 that will be written*/

    cont1->company_name_posn = (strlen(comName) == 0 ? 0 : currPosn); /*If company Name was left blank set its respective position to 0*/
    currPosn += strlen(comName) + (strlen(comName) == 0 ? 0 : 1);

    cont1->email_posn = (strlen(email) == 0 ? 0 : currPosn); /*If email was left blank set its respective position to 0*/
    currPosn += strlen(email) + (strlen(email) == 0 ? 0 : 1);

    cont1->next = currPosn; /*Next will always point to something, no if statements necessary*/


    /*Write info*/
    fwrite(cont1, sizeof(contact), 1, fp); /*Must write struct info first*/

    if(strlen(fName) != 0){
        fwrite(fName, sizeof(char), strlen(fName)+1, fp); /*if a first name was entered, write it to file (add one for a null character)*/
    }
    if(strlen(lName) != 0){
        fwrite(lName, sizeof(char), strlen(lName)+1, fp); /*if a last name was entered, write it to file (add one for null charater)*/
    }
    if(strlen(comName) != 0){
        fwrite(comName, sizeof(char), strlen(comName)+1, fp);
    }
    if(strlen(email) != 0){
        fwrite(email, sizeof(char), strlen(email)+1, fp);
    }

    /*Free all pointers*/
    free(cont1);
    free(fName);
    free(lName);
    free(comName);
    free(pNumber);
    free(email);

    return;
}

/**************************************************
 searchContact

 In:
    fp - pointer to file that will be read from

 Out:
    none

 Post:
    Searches for a contact based on its phone number
    if a matching phone number is found in the file
    print out all information of contact. If no match
    was found, says "no match found."
**************************************************/
void searchContact(FILE* fp){

    int found = 0;
    char* cNum = malloc(sizeof(char));
    contact* cont = malloc(sizeof(contact));
    unsigned long phoneNum;
    long end;

    fseek(fp, 0, SEEK_END); /*Set current position in file to end of file*/

    end = ftell(fp); /*end will be used to track if we have reached the end of the file*/

    fseek(fp, 0, SEEK_SET); /*Set current position in file to start of file*/

    do{
        printf("Phone Number: ");
        cNum = userInput(cNum);

    }while(strlen(cNum) == 0); /*Ensure a phone number is entered*/

    phoneNum = strtoul(cNum, NULL, 10);


    while(ftell(fp) != end && found != 1){ /*Loop until end of file or if a contact was found*/

        fread(cont, sizeof(contact), 1, fp); /*Read in struct*/

        if(cont->phone_number == phoneNum){ /*Compare phone number entered and one of current struct, if they match, match has been found and loop will exit*/
            found = 1;
        }

        fseek(fp, cont->next, SEEK_SET); /*Set current position in file to the start of the next contact struct*/
    }

    if(found == 1){ /*If contact was found*/
        printf("First Name: ");

        if(cont->first_name_posn != 0){ /*Only try to print first name if it was entered in the first place*/
            fseek(fp, cont->first_name_posn, SEEK_SET);
            printFromFile(fp);
        }

        printf("\nLast Name: ");

        if(cont->last_name_posn != 0){ /*Only try to print last name if it was entered in the first place*/
            fseek(fp, cont->last_name_posn, SEEK_SET);
            printFromFile(fp);
        }

        printf("\nCompany Name: ");

        if(cont->company_name_posn != 0){
            fseek(fp, cont->company_name_posn, SEEK_SET);
            printFromFile(fp);
        }

        printf("\nPhone Number: %lu", cont->phone_number); /*This will print no matter what, because phone number is required to write*/

        printf("\nEmail: ");

        if(cont->email_posn != 0){
            fseek(fp, cont->email_posn, SEEK_SET);
            printFromFile(fp);
        }

        printf("\n");

    }
    else{ /*No contact with matching phone number*/
        printf("No match found.\n");

    }

    fseek(fp, 0, SEEK_END);

    /*free pointers*/
    free(cNum);
    free(cont);

    return;
}

