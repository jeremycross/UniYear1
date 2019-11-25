#include <stdlib.h>
#include <string.h>
#include "compareElements.h"

int compare_name_descending (const void *a, const void *b){
    /*strcmp returns negative value if last_name in struct b is less than last_name in a (0 is they are equal and positive value is b is larger), if b is less than a they are in order*/
    return strcmp(((struct element*)b)->last_name, ((struct element*)a)->last_name); /*return value of comparison between last_name of a and last_name of b*/
}

