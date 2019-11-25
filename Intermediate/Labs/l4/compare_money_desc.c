#include <stdlib.h>
#include "compareElements.h"

int compare_money_descending (const void *a, const void *b){
    /*returns the difference between the salary element in struct b and the salary element in struct a, if a is larger returns negative, these two are inorder*/
    return (((struct element*)b)->salary) - (((struct element*)a)->salary); /*Cast void pointer to struct element pointer before dereferencing*/
}
