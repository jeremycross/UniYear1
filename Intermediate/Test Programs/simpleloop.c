#include <string.h>
#include <stdio.h>

int main(){

    int isFinished = 0;
    char str[5];

    do{
        printf("Contact?\n");
        scanf("%s", str);
        printf("%s", str);

        if(strcmp(str, "Yes") == 0){
            printf("Run add contact\n");
        }
        else if(strcmp(str, "No") == 0){
            printf("Search?\n");
            scanf("%s", str);
            printf("%s", str);

            if(strcmp(str, "Yes") == 0){
                printf("Run search\n");
            }
            else if(strcmp(str, "No") == 0){
                printf("No twice in a row\n");
                isFinished = 1;
            }
        }



    }while(isFinished == 0);

    printf("End of program\n");


    return 0;
}
