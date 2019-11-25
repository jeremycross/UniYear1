#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct student{

    int recordCount;
    char *firstName;
    char *lastName;
    char *id;
    char *email;

};

int main(){

    struct student *p;
    char tempString[51];
    int i = 0;
    int j;
    int k;
    int idMalloc;
    int emailMalloc;

    p = malloc(sizeof(struct student));

    while(1){

        printf("First Name: ");
        fgets(tempString, 51, stdin);

        if(tempString[0] == '.' && tempString[1] == '\n'){ /*To exit loop*/
            break;
        }

        p[i].recordCount = i+1; /*Set record count variable*/

        p[i].firstName = malloc(sizeof(char)*(strlen(tempString) + 2)); /*Allocate enough space for first name in current struct*/
        strcpy(p[i].firstName, tempString);

        printf("Last Name: ");
        fgets(tempString, 51, stdin);
        p[i].lastName = malloc(sizeof(char)*(strlen(tempString) + 2)); /*Allocate enough space for last name in current struct*/
        strcpy(p[i].lastName, tempString);

        printf("ID#: ");

        fgets(tempString, 51, stdin);
        idMalloc = (strlen(tempString) + 2); /*Variable is used for correctly sized memory allocation of id number element*/
        p[i].id = malloc(sizeof(char)*idMalloc);
        strcpy(p[i].id, tempString);

        while(tempString[strlen(tempString)-1] != '\n'){ /*Will only run if fgets did not reach end of line*/

            fgets(tempString, 51, stdin);
            idMalloc = (strlen(tempString) + 2 + idMalloc); /*Change value for realloc below*/
            p[i].id = realloc(p[i].id, (sizeof(char)*idMalloc));
            strcat(p[i].id, tempString); /*Add tempString onto end of id element*/
        } /*This process will repeat until end of line is reached*/

        printf("Email: ");

        fgets(tempString, 51, stdin);
        emailMalloc = (strlen(tempString) + 2); /*Variable used for correctly sized memory allocation of email element*/
        p[i].email = malloc(sizeof(char)*emailMalloc);
        strcpy(p[i].email, tempString);

        while(tempString[strlen(tempString)-1] != '\n'){ /*Will only run if fgets did not reach end of line*/

            fgets(tempString, 51, stdin);
            emailMalloc = (strlen(tempString) + 2 + emailMalloc); /*Change value for realloc below*/
            p[i].email = realloc(p[i].email, (sizeof(char)*emailMalloc));
            strcat(p[i].email, tempString); /*Add tempString to end of email element*/
        } /*This process will repeat until end of line is reached*/


        i++;

        p = realloc(p, sizeof(struct student) * (i + 2)); /*Change amount of memory allocated for struct pointer*/
    }

    for(j = 0; j < i; j++){ /*Changes all newline characters to null characters, this is for formatting*/
        for(k = 0; k < strlen(p[j].id); k++){
            if(p[j].id[k] == '\n'){
                p[j].id[k] = '\0';
            }
        }
        for(k = 0; k < strlen(p[j].firstName); k++){
            if(p[j].firstName[k] == '\n'){
                p[j].firstName[k] = '\0';
            }
        }
        for(k = 0; k < strlen(p[j].lastName); k++){
            if(p[j].lastName[k] == '\n'){
                p[j].lastName[k] = '\0';
            }
        }
        for(k = 0; k < strlen(p[j].email); k++){
            if(p[j].email[k] == '\n'){
                p[j].email[k] = '\0';
            }
        }
    } /*End of formatting for loop*/

    /*Print all records in order they were entered*/
    for(j = 0; j < i; j++){
        printf("%s,%s,%s,%s\n", p[j].id, p[j].firstName, p[j].lastName, p[j].email);
    }

    /*Free all memory allocated to each element of each struct created*/
    for(j = 0; j < i; j++){
        free(p[j].id);
        free(p[j].firstName);
        free(p[j].lastName);
        free(p[j].email);
    }

    free(p); /*Free struct pointer*/

    return 0;
}
