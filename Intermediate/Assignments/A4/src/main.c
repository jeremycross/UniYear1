#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../includes/structs.h"
#include "../includes/functions.h"


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
