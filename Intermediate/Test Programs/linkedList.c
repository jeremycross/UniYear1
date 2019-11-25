#include <stdlib.h>
#include <stdio.h>

typedef struct data{
    int num;
    struct data *next;
}data;


int main(){

    int i;
    data *head;
    data *current, *ptr;

    head = NULL;
    ptr = NULL;

    /*Add members to the list*/
    for(i = 0; i < 6; i++){
        ptr = malloc(sizeof(data));
        ptr->num = i + 10;
        ptr->next = head;
        head = ptr;
    }

    current = head;
    data *temp;

    /*Print the members of list and free the memory as we go*/
    while(current != NULL){
        printf("%d\n", current->num);
        temp = current;
        current = current->next;
        free(temp);
    }



    return 0;
}
