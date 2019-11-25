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

linkCont* deleteContact(linkCont* list, int currCont, int* size){

    int i;

    for(i = currCont; i < *size-1; i++){

        /*Free current spot in array to be reinitialized*/
        free(list[i].lastName);
        free(list[i].firstName);
        free(list[i].comName);
        free(list[i].email);
        free(list[i].sortStr);

        /*Create each string in its new location*/
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

    /*i = size-1*/
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

int validAddAction(char* act){

    if(strcmp(act, "R\0") == 0 || strcmp(act, "S\0") == 0){
        return 1;
    }

    return 0;
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

linkCont* addContact(linkCont* list, int* size){

    char* action = malloc(sizeof(char));
    char* tempfName = malloc(sizeof(char));
    char* templName = malloc(sizeof(char));
    char* tempComName = malloc(sizeof(char));
    char* tempEmail = malloc(sizeof(char));
    char* tempPNumber = malloc(sizeof(char));
    unsigned long pNum;
    int resize = *size +1;

    printf("In add function\n");

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
        printf("Return with no save\n");
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


int compareStr(const void* a, const void* b){

    return strcmp(((linkCont*)a)->sortStr, ((linkCont*)b)->sortStr);

}

int validEditAction(char* act){

    if(strcmp(act, "R\0") == 0 || strcmp(act, "S\0") == 0 || strcmp(act, "D\0") == 0){ /*Valid action for edit mode*/
        return 1;
    }

    return 0; /*Invalid action*/
}

linkCont* editContact(linkCont* list, int currCont, int * size){ /*This will need to return struct array in actual code, will be returned to display contact*/

    char* action = malloc(sizeof(char));
    char* tempPNumber = malloc(sizeof(char));
    char* tempEmail = malloc(sizeof(char));
    long int pNum;

    printf("In edit function: %d\n", currCont);

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
        printf("Return with no save to full list\n");
    }
    else if(action[0] == 'S'){

        free(list[currCont].email);

        list[currCont].email = malloc(sizeof(char) * (strlen(tempEmail) +1));
        strcpy(list[currCont].email, tempEmail);

        list[currCont].phone_number = pNum;

        printf("Return with save to full list\n");
    }

    free(tempPNumber);
    free(tempEmail);
    free(action);

    return list;
}

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

int main(){


    FILE* fp;
    linkCont* contactList = malloc(sizeof(linkCont));
    contact* tempCont = malloc(sizeof(contact));
    long end;
    int size;
    int index = 0;
    int i;
    char prevC = '\0';
    int (*compare_ptr)(const void *a, const void* b);

    compare_ptr = &compareStr;

    fp = fopen("myContactList.db", "a+b");

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
        printf("%lu\n", contactList[index].phone_number);

        fseek(fp, tempCont->next, SEEK_SET); /*Ensure in correct spot to read next struct info*/
        index++;

    }while(tempCont->next != end && ftell(fp) != end);

    size = index;

    printf("Printing out inputted array\n");
    for(i = 0; i < size; i++){
        printf("first Name: %s\n", contactList[i].firstName);
        printf("last Name: %s\n", contactList[i].lastName);
        printf("com Name: %s\n", contactList[i].comName);
        printf("email: %s\n", contactList[i].email);
        printf("sort: %s\n", contactList[i].sortStr);
    }

    if(size > 1){ /*Only sort if more than 1 contact*/
        qsort(contactList, size, sizeof(linkCont), compare_ptr);
    }


    /*LIST CONTACTS*/
    printf("Number of Contacts = %d\n", size);

    for(i = 0; i < size; i++){
        if(prevC != toupper(contactList[i].sortStr[0])){
            printf("%c\n", toupper(contactList[i].sortStr[0]));
            prevC = toupper(contactList[i].sortStr[0]);
        }

        if(strlen(contactList[i].lastName) == 0){
            printf("   %d. %s\n", i+1, contactList[i].sortStr);
        }
        else{
            if(strlen(contactList[i].firstName) == 0){
                printf("   %d. %s\n", i+1, contactList[i].sortStr);
            }
            else{
                printf("   %d. %s %s\n", i+1, contactList[i].firstName, contactList[i].sortStr);
            }
        }
    }

    contactList = editContact(contactList, 3, &size);

    printf("\nAfter edit: size = %d\n\n", size);
    for(i = 0; i < size; i++){
        printf("first Name: %s\n", contactList[i].firstName);
        printf("last Name: %s\n", contactList[i].lastName);
        printf("com Name: %s\n", contactList[i].comName);
        printf("email: %s\n", contactList[i].email);
        printf("Phone: %lu\n", contactList[i].phone_number);
        printf("sort: %s\n", contactList[i].sortStr);
    }


    contactList = deleteContact(contactList, 1, &size);

    printf("\nAfter delete: size = %d\n\n", size);

    for(i = 0; i < size; i++){
        printf("first Name: %s\n", contactList[i].firstName);
        printf("last Name: %s\n", contactList[i].lastName);
        printf("com Name: %s\n", contactList[i].comName);
        printf("Phone: %lu\n", contactList[i].phone_number);
        printf("email: %s\n", contactList[i].email);
        printf("sort: %s\n", contactList[i].sortStr);
    }

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
    fclose(fp);

    return 0;
}
