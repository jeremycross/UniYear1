#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct linkedContact{

    unsigned long phone_number;
    char* firstName;
    char* lastName;
    char* comName;
    char* email;
    char* sortStr;

}linkCont;

typedef struct contact{

    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;

}contact;

/***************************************************
 userInput

 In:
    ans - char pointer, points to string inputted by user

 Out:
    ans - char pointer, points to string inputted by user

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

/*****************************************************
 deleteContact

 In:
    list - array of structs(linkedContact) that store contact info
    currCont - array index location of contact to be deleted
    *size - pass by pointer, the number of elements in
            struct array

 Out:
    list - array of structs that store contact info

 Post:
    Given the array of structs, the index of the struct to be
    deleted and the size of the struct array. Removes
    all info of that contact, moving all info
    that comes after currContact forward one index, erasing the
    last element completely and reallocing the array to have
    one less contact. Size is also decreased by 1.
*****************************************************/
linkCont* deleteContact(linkCont* list, int currCont, int* size){

    int i;

    for(i = currCont; i < *size-1; i++){

        /*Free current spot in array to be reinitialized*/
        free(list[i].lastName);
        free(list[i].firstName);
        free(list[i].comName);
        free(list[i].email);
        free(list[i].sortStr);

        /*Create each string in its new location, move info from contact 5 to contact 4 for example*/
        list[i].firstName = malloc(sizeof(char) * (strlen(list[i+1].firstName) +1));
        strcpy(list[i].firstName, list[i+1].firstName);

        list[i].lastName = malloc(sizeof(char) * (strlen(list[i+1].lastName) +1));
        strcpy(list[i].lastName, list[i+1].lastName);

        list[i].comName = malloc(sizeof(char) * (strlen(list[i+1].comName) +1));
        strcpy(list[i].comName, list[i+1].comName);

        list[i].email = malloc(sizeof(char) * (strlen(list[i+1].email) +1));
        strcpy(list[i].email, list[i+1].email);

        list[i].sortStr = malloc(sizeof(char) * (strlen(list[i+1].sortStr) +1));
        strcpy(list[i].sortStr, list[i+1].sortStr);

        list[i].phone_number = list[i+1].phone_number;

    }

    /*Free last contact in array*/
    free(list[i].lastName);
    free(list[i].firstName);
    free(list[i].comName);
    free(list[i].email);
    free(list[i].sortStr);

    /*Alter size of array to account for smaller number of structs*/
    *size = *size -1;
    list = realloc(list, sizeof(linkCont) * (*size));

    return list;
}

/*********************************************
 validAddAction

 In:
    actNum - pass by pointer, if Action is numeric
             then this value takes the inputted
             numeric value (as long as number is valid)

 Out:
    returns a 1 if valid action for adding
    a contact and a 0 if invalid

 Post:
    Checks to make sure action entered is one of the
    action options when  adding a contact. If it is
    return 1, if not return 0.
*********************************************/
int validAddAction(char* act){

    if(strcmp(act, "R\0") == 0 || strcmp(act, "S\0") == 0){
        return 1;
    }

    return 0;
}

/*********************************************
 checkPhoneNum

 In:
    number - string entered by a user to be a phone number

 Out:
    returns 1 if valid phone number and 0 if not valid

 Post:
    Checks that string entered by user is all numeric chars
    and that it is 7 or 10 digits long. If yes to both valid
    number and 1 is returned. 0 returned if invalid
*********************************************/
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

/********************************************
 emailCheck

 In:
    email - inputted email from user

 Out:
    returns a 1 if valid email and 0 if invalid

 Post:
    checks if entered email follows the
    name@domain.tld email. name, domain and tld
    must all be at least 1 character long. If they are
    then valid email and 1 is returned, if not 0 returned
********************************************/
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

/*********************************************
 addContact

 In:
    list - array of contacts
    size - pass by pointer, num of elements in list

 Out:
    list - array of contacts

 Post:
    Prompts user for info for new contact
    when finished asks for action, if action
    is 'R' do nothing with new info and return to
    main, if 'S' save new info to list and increment
    size by 1.
*********************************************/
linkCont* addContact(linkCont* list, int* size){

    char* action = malloc(sizeof(char));
    char* tempfName = malloc(sizeof(char));
    char* templName = malloc(sizeof(char));
    char* tempComName = malloc(sizeof(char));
    char* tempEmail = malloc(sizeof(char));
    char* tempPNumber = malloc(sizeof(char));
    unsigned long pNum;
    int resize = *size +1;

    printf("\nNew Contact\n");

    /*Take in info*/
    printf("First Name: ");
    tempfName = userInput(tempfName);

    printf("Last Name: ");
    templName = userInput(templName);

    do{
        printf("Company Name: ");
        tempComName = userInput(tempComName);

    }while(strlen(tempComName) == 0 && strlen(templName) == 0);

    do{
        printf("Phone Number (enter only numbers): ");
        tempPNumber = userInput(tempPNumber);

    }while(checkPhoneNum(tempPNumber) == 0); /*Ensure a phone number is entered properly, or else ask for it again*/

    pNum = strtoul(tempPNumber, NULL, 10);

    do{
        printf("Email: ");
        tempEmail = userInput(tempEmail);

    }while(emailCheck(tempEmail) == 0);


    /*What to do with info*/
    do{
        printf("Action: ");
        action = userInput(action);

    }while(validAddAction(action) == 0);

    if(action[0] == 'R'){
    }
    else if(action[0] == 'S'){

        list = realloc(list, sizeof(linkCont) * (resize));

        /*Save everything into main array*/
        list[*size].firstName = malloc(sizeof(char) * (strlen(tempfName)+1));
        strcpy(list[*size].firstName, tempfName);

        list[*size].lastName = malloc(sizeof(char) * (strlen(templName)+1));
        strcpy(list[*size].lastName, templName);

        list[*size].comName = malloc(sizeof(char) * (strlen(tempComName)+1));
        strcpy(list[*size].comName, tempComName);

        list[*size].email = malloc(sizeof(char) * (strlen(tempEmail)+1));
        strcpy(list[*size].email, tempEmail);

        if(strlen(templName) == 0){
            list[*size].sortStr = malloc(sizeof(char) * (strlen(list[*size].comName)+1));
            strcpy(list[*size].sortStr, list[*size].comName);
        }
        else{
            list[*size].sortStr = malloc(sizeof(char) * (strlen(list[*size].lastName)+1));
            strcpy(list[*size].sortStr, list[*size].lastName);
        }

        list[*size].phone_number = pNum;

        *size = resize;
    }

    /*Free all local variables*/
    free(tempfName);
    free(templName);
    free(tempComName);
    free(tempEmail);
    free(tempPNumber);
    free(action);

    return list;
}


/******************************************
 compareStr

 In:
    a - will be the sortStr linkCont struct element
    b - will be the sortStr linkCont struct element

 Out:
    returns value of strcmp between a and b

 Post:
    Is used to sort contacts with qsort
******************************************/
int compareStr(const void* a, const void* b){

    return strcmp(((linkCont*)a)->sortStr, ((linkCont*)b)->sortStr);

}

/****************************************
 validEditAction

 In:
    act - action entered by user

 Out:
    returns 1 if action is valid and 0 if invalid

 Post:
    checks if action entered by user when editing
    contact is a possible option, if not, returns 0
    and user will be reprompted for action if it is
    returns 1 and action is performed
****************************************/
int validEditAction(char* act){

    if(strcmp(act, "R\0") == 0 || strcmp(act, "S\0") == 0 || strcmp(act, "D\0") == 0){ /*Valid action for edit mode*/
        return 1;
    }

    return 0; /*Invalid action*/
}

/****************************************
 editContact

 In:
    list - array of contacts
    currCont - array index of current contact
    size - pass by pointer, num of elements in
           list

 Out:
    list - array of contacts

 Post:
    Allows user to edit a chosen contacts
    email and phone number. If 'R' is entered for
    action then the edits are discarded and program returns to
    main, if 'D' deletes selected contact and returns to main,
    if 'S' saves changes done to contact and returns to main
****************************************/
linkCont* editContact(linkCont* list, int currCont, int * size){

    char* action = malloc(sizeof(char));
    char* tempPNumber = malloc(sizeof(char));
    char* tempEmail = malloc(sizeof(char));
    long int pNum;

    printf("\nContact #%d\n", currCont+1);

    /*Take in edit info*/
    printf("First Name: %s\n", list[currCont].firstName);
    printf("Last Name: %s\n", list[currCont].lastName);
    printf("Company Name: %s\n", list[currCont].comName);

    do{
        printf("Phone Number (enter only numbers): ");
        tempPNumber = userInput(tempPNumber);

    }while(checkPhoneNum(tempPNumber) == 0);

    pNum = strtoul(tempPNumber, NULL, 10);

    do{
        printf("Email: ");
        tempEmail = userInput(tempEmail);

    }while(emailCheck(tempEmail) == 0);


    /*What to do with editted info*/
    do{
        printf("Action: ");
        action = userInput(action);

    }while(validEditAction(action) == 0);

    if(action[0] == 'D'){
        list = deleteContact(list, currCont, &(*size));
    }
    else if(action[0] == 'R'){
    }
    else if(action[0] == 'S'){

        free(list[currCont].email);

        list[currCont].email = malloc(sizeof(char) * (strlen(tempEmail) +1));
        strcpy(list[currCont].email, tempEmail);

        list[currCont].phone_number = pNum;
    }

    free(tempPNumber);
    free(tempEmail);
    free(action);

    return list;
}

/***********************************************
 validDisplayAction

 In:
    act - action entered by user

 Out:
    returns 1 if action is valid and returns 0 if invalid

 Post:
    checks if action entered by user when displaying
    a certain contacts info is a possible option for an
    action, if it is returns 1 if not returns 0
***********************************************/
int validDisplayAction(char* act){

    if(strcmp(act, "D\0") == 0 || strcmp(act, "R\0") == 0 || strcmp(act, "E\0") == 0){ /*Valid action for display selected contact*/
        return 1;
    }

    return 0; /*Invalid action*/
}

/********************************************
 displayContact

 In:
    list - array of contacts
    currCont - array index of selected contact
    size - pass by pointer, number of elements in
           list

 Out:
    list -array of contacts

 Post:
    Shows selected contacts full info and asks
    action, user can delete, edit or return back to
    full list of contacts
********************************************/
linkCont* displayContact(linkCont* list, int currCont, int * size){

    char* action = malloc(sizeof(char));

    printf("\nContact #%d\n", currCont+1);

    printf("First Name: %s\n", list[currCont].firstName);
    printf("Last Name: %s\n", list[currCont].lastName);
    printf("Company Name: %s\n", list[currCont].comName);
    printf("Phone Number: %lu\n", list[currCont].phone_number);
    printf("Email: %s\n", list[currCont].email);

    do{
        printf("Action: ");
        action = userInput(action);

    }while(validDisplayAction(action) == 0);


    if(action[0] == 'D'){
        list = deleteContact(list, currCont, &(*size));
    }
    else if(action[0] == 'R'){
    }
    else if(action[0] == 'E'){
        list = editContact(list, currCont, &(*size));
    }

    free(action);

    return list;
}

/*******************************************
 saveToFile

 In:
    list - array of contacts
    size - number of elements in list

 Out:
    None

 Post:
    Saves all contacts to file before exiting
    the program, starts fresh with a blank file
*******************************************/
void saveToFile(linkCont* list, int size){

    contact* cont1 = malloc(sizeof(contact));
    long currPosn;
    int index;
    FILE* fp;

    fp = fopen("myContactList.db", "wb"); /*Wipe any info on file currently and to be replaced with new info*/

    fseek(fp, 0, SEEK_SET);

    /*Write all contacts*/
    for(index = 0; index < size; index++){

        cont1->phone_number = list[index].phone_number;

        currPosn = ftell(fp) + sizeof(contact); /*Find current position in file, this variable will be used to predict where strings will be written*/

        /*Position elements*/
        cont1->first_name_posn = (strlen(list[index].firstName) == 0 ? 0 : currPosn); /*If first Name was left blank set its respective position to 0*/
        currPosn += strlen(list[index].firstName) + (strlen(list[index].firstName) == 0 ? 0 : 1); /*If first name was not left blank add one to currPosn, to account for \0 that will be written to file*/

        cont1->last_name_posn = (strlen(list[index].lastName) == 0 ? 0 : currPosn); /*If last Name was left blank set its respective position to 0*/
        currPosn += strlen(list[index].lastName) + (strlen(list[index].lastName) == 0 ? 0 : 1); /*If last name was not left blank add one to currPosn to account for \0 that will be written*/

        cont1->company_name_posn = (strlen(list[index].comName) == 0 ? 0 : currPosn); /*If company Name was left blank set its respective position to 0*/
        currPosn += strlen(list[index].comName) + (strlen(list[index].comName) == 0 ? 0 : 1);

        cont1->email_posn = (strlen(list[index].email) == 0 ? 0 : currPosn); /*If email was left blank set its respective position to 0*/
        currPosn += strlen(list[index].email) + (strlen(list[index].email) == 0 ? 0 : 1);

        cont1->next = currPosn; /*Next will always point to something, no if statements necessary*/


        /*Write info*/
        fwrite(cont1, sizeof(contact), 1, fp); /*Must write struct info first*/

        if(strlen(list[index].firstName) != 0){
            fwrite(list[index].firstName, sizeof(char), strlen(list[index].firstName)+1, fp); /*if a first name was entered, write it to file (add one for a null character)*/
        }
        if(strlen(list[index].lastName) != 0){
            fwrite(list[index].lastName, sizeof(char), strlen(list[index].lastName)+1, fp); /*if a last name was entered, write it to file (add one for null charater)*/
        }
        if(strlen(list[index].comName) != 0){
            fwrite(list[index].comName, sizeof(char), strlen(list[index].comName)+1, fp);
        }
        if(strlen(list[index].email) != 0){
            fwrite(list[index].email, sizeof(char), strlen(list[index].email)+1, fp);
        }

    }

    free(cont1);
    fclose(fp);

    return;
}

/*************************************
 stringFromFile

 In:
    stream - file to be read from

 Out:
    returns the string read from file

 Post:
    Reads a string from a file character by
    character, the string is dynamically allocated
*************************************/
char* stringFromFile(FILE* stream){

    char* string = malloc(sizeof(char));
    char* c = malloc(sizeof(char)*2);
    int count = 0;

    c[1] = '\0';
    strcpy(string, "");

    do{
        count++;
        c[0] = fgetc(stream);
        string = realloc(string, sizeof(char)*(count+1));
        strcat(string, c);

    }while(c[0] != '\0' && string[count] != EOF);

    free(c);

    return string;
}

/*********************************************
 listAll

 In:
    list - array of contacts
    size - number of elements in list

 Out:
    None

 Post:
    Prints all contacts in sorted order, with subheadings
    by character
*********************************************/
void listAll(linkCont* contactList, int size){

    int i;
    char prevC = '\0';

    printf("\nNumber of Contacts = %d\n", size);

    for(i = 0; i < size; i++){
        if(prevC != toupper(contactList[i].sortStr[0])){
            printf("%c\n", toupper(contactList[i].sortStr[0]));
            prevC = toupper(contactList[i].sortStr[0]);
        }

        if(strlen(contactList[i].lastName) == 0){
            printf("    %d. %s\n", i+1, contactList[i].sortStr);
        }
        else{
            if(strlen(contactList[i].firstName) == 0){
                printf("    %d. %s\n", i+1, contactList[i].sortStr);
            }
            else{
                printf("    %d. %s %s\n", i+1, contactList[i].firstName, contactList[i].sortStr);
            }
        }
    }

    return;

}

/****************************************
 validListAction

 In:
    act - action entered by user
    upperbound - the number of contacts
    num - pass by pointer, the number of the
         inputted action, action was numeric

 Out:
    returns 1 if action is valid and non-numeric,
    returns 2 if valid and numeric and returns 0 if
    invalid, num is also changed to the numeric action.

 Post:
    Checks if action if a possible option when contacts are listed
    it also processes if the answer is numeric or not, if it is and
    within the bounds of the contacts then num is changed to that value
    and 2 is returned. if not numeric 1 is returned if action is valid and
    if invalid action, returns 0
****************************************/
int validListAction(char* act, int upperbound, long int *num){

    int isNumber = 1;
    int i = 0;

    for(i = 0; i < strlen(act); i++){
        if(isdigit(act[i]) == 0 && isNumber != 0){ /*See if a number was entered*/
            isNumber = 0;
        }
    }

    if(isNumber == 1){
        *num = strtol(act, NULL, 10); /*Convert to string to number*/

        if(*num >= 1 && *num <= upperbound){ /*Check if number is valid*/
	    *num = *num -1;
            return 2;
        }
    }
    else{
        *num = 0; /*Set this to something to avoid undefined behaviour*/
        if(strcmp(act, "A\0") == 0 || strcmp(act, "X\0") == 0){ /*If not a number check if its another valid action*/
            return 1;
        }
    }

    return 0;
}


int main(){

    int exit = 0;
    char* action = malloc(sizeof(char));
    long int actNum;
    int check;
    FILE* fp;
    linkCont* contactList = malloc(sizeof(linkCont));
    contact* tempCont = malloc(sizeof(contact));
    long end;
    int size;
    int index = 0;
    int i;
    int (*compare_ptr)(const void *a, const void* b);

    compare_ptr = &compareStr;

    fp = fopen("myContactList.db", "a+b");


    /*Get Contacts*/
    fseek(fp, 0, SEEK_END);
    end = ftell(fp);

    fseek(fp, 0, SEEK_SET);

    do{
        if(ftell(fp) == end){ /*Avoid unncessary reading if file is empty*/
            break;
        }

        fread(tempCont, sizeof(contact), 1, fp);
        contactList = realloc(contactList, sizeof(linkCont)*(index+1));


        /*Get First Name*/
        if(tempCont->first_name_posn != 0){
            fseek(fp, tempCont->first_name_posn, SEEK_SET);
            contactList[index].firstName = stringFromFile(fp);
        }
        else{
            contactList[index].firstName = malloc(sizeof(char));
            strcpy(contactList[index].firstName, "\0");
        }

        /*Get Last Name*/
        if(tempCont->last_name_posn != 0){
            fseek(fp, tempCont->last_name_posn, SEEK_SET);
            contactList[index].lastName = stringFromFile(fp);
        }
        else{
            contactList[index].lastName = malloc(sizeof(char));
            strcpy(contactList[index].lastName, "\0");
        }

        /*Get Company Name*/
        if(tempCont->company_name_posn != 0){
            fseek(fp, tempCont->company_name_posn, SEEK_SET);
             contactList[index].comName = stringFromFile(fp);
        }
        else{
            contactList[index].comName = malloc(sizeof(char));
            strcpy(contactList[index].comName, "\0");
        }

        /*Get email*/
        if(tempCont->email_posn != 0){
            fseek(fp, tempCont->email_posn, SEEK_SET);
             contactList[index].email = stringFromFile(fp);
        }
        else{
            contactList[index].email = malloc(sizeof(char));
            strcpy(contactList[index].email, "\0");
        }

        /*Get sorting string, to be used for qsort function*/
        if(tempCont->last_name_posn == 0){
            contactList[index].sortStr = malloc(sizeof(char)*(strlen(contactList[index].comName)+1));
            strcpy(contactList[index].sortStr, contactList[index].comName);
        }
        else{
            contactList[index].sortStr = malloc(sizeof(char)*(strlen(contactList[index].lastName)+1));
            strcpy(contactList[index].sortStr, contactList[index].lastName);
        }

        contactList[index].phone_number = tempCont->phone_number;

        fseek(fp, tempCont->next, SEEK_SET); /*Ensure in correct spot to read next struct info*/
        index++;

    }while(tempCont->next != end && ftell(fp) != end);

    fclose(fp); /*Done reading in info*/

    size = index;

    /*Loop until asked to exit*/
    do{
	if(size > 1){ /*Only sort if more than 1 contact*/
            qsort(contactList, size, sizeof(linkCont), compare_ptr);
        }
        listAll(contactList, size);

        /*Get action to perform*/
        do{
            printf("Action: ");
            action = userInput(action);

        }while((check = validListAction(action, size, &actNum)) == 0); /*Check for valid action*/

        if(check == 1){ /*If action was valid and non numeric*/
            if(action[0] == 'A'){
                contactList = addContact(contactList, &size);
            }
            else if(action[0] == 'X'){ /*Leave loop*/
                exit = 1;
            }
        }
        else if(check == 2){ /*If action was a valid and numeric*/
            contactList = displayContact(contactList, actNum, &size);
        }

    }while(exit == 0);

    saveToFile(contactList, size); /*Save info to file*/

    /*Free everything*/
    for(i = 0; i < size; i++){
        free(contactList[i].firstName);
        free(contactList[i].lastName);
        free(contactList[i].comName);
        free(contactList[i].email);
        free(contactList[i].sortStr);
    }

    free(tempCont);
    free(contactList);
    free(action);

    return 0;
}
