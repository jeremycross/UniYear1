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
void printFromFile(FILE* stream){

    char c;

    do{
        c = fgetc(stream);
        printf("%c", c);

    }while(c != '\0');


    return;
}

int main(){

    FILE* fp;
    int found = 0;
    char* cNum = malloc(sizeof(char));
    contact* cont = malloc(sizeof(contact));
    unsigned long phoneNum;
    long end;
    long currPos;

    fp = fopen("test.db", "a+b");

    fseek(fp, 0, SEEK_END);

    end = ftell(fp);

    printf("End: %lu\n", end);

    fseek(fp, 0, SEEK_SET);

    printf("Phone Number: ");
    cNum = userInput(cNum, stdin);

    phoneNum = strtoul(cNum, NULL, 10);
    printf("Inputted number: %lu\n", phoneNum);


    while(ftell(fp) != end && found != 1){
        fread(cont, sizeof(contact), 1, fp);

        printf("Current Number check: %lu vs %lu\n", cont->phone_number, phoneNum);

        if(cont->phone_number == phoneNum){
            found = 1;
            printf("Found!\n");
        }

        fseek(fp, cont->next, SEEK_SET);
        currPos = ftell(fp);
        printf("Current position: %ld\n", currPos);
    }

    if(found == 1){
        printf("First Name: ");

        if(cont->first_name_posn != 0){
            fseek(fp, cont->first_name_posn, SEEK_SET);
            printFromFile(fp);
        }

        printf("\nLast Name: ");

        if(cont->last_name_posn != 0){
            fseek(fp, cont->last_name_posn, SEEK_SET);
            printFromFile(fp);
        }

        printf("\nCompany Name: ");

        if(cont->company_name_posn != 0){
            fseek(fp, cont->company_name_posn, SEEK_SET);
            printFromFile(fp);
        }

        printf("\nPhone Number: %lu", cont->phone_number);

        printf("\nEmail: ");

        if(cont->email_posn != 0){
            fseek(fp, cont->email_posn, SEEK_SET);
            printFromFile(fp);
        }

    }
    else{
        printf("\nNo match found.");

    }

    fseek(fp, 0, SEEK_END);

    fclose(fp);
    free(cNum);
    free(cont);

    return 0;
}
