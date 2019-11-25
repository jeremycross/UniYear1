#include <stdlib.h>
#include "compareElements.h"

int compare_id_descending (const void *a, const void *b){
    /*returns the difference between the id_number in struct b and the id_number in struct a, if a is larger returns a negative number, they are in order*/
    return (((struct element*)b)->id_number) - (((struct element*)a)->id_number); /*Void pointers must be cast before use*/
}

