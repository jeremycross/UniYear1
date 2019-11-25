#include <stdlib.h>
#include "compareElements.h"

int compare_id_ascending (const void *a, const void *b){
    /*returns the difference between the id_number in struct a and the id_number in struct b, if a is smaller returns a negative, meaning they are inorder (for ascending)*/
    return (((struct element*)a)->id_number) - (((struct element*)b)->id_number); /*must cast void pointer to a struct element pointer to tell compiler what we are using*/
}

