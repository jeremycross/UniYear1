/************************createArray.c **************************
Student Name: Jeremy Cross                    Email Id: jcross04
Date: January 26th, 2019                      Course Name: CIS 2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
1) I have read and understood the University policy on academic
integrity;
2) I have completed the Computing with Integrity Tutorial on Moodle;
and
3) I have achieved at least 80% in the Computing with Integrity Self
Test.
I assert that this work is my own. I have appropriately acknowledged
any and all material (data, images, ideas or words) that I have used,
whether directly quoted or paraphrased. Furthermore, I certify that
this assignment was prepared by me specifically for this course.
*********************************************************************/

#include "arrayDefns.h"
#include <stdlib.h>
#include <stdio.h>


/****************************************
 createArray

 In:
    rows - the number of rows in the array
    cols - the number of columns in the array
 Out:
    The dynamically allocated array is returned
 Post:
    Using the inputted amount of rows and columns
    the function dynamically allocates a 2D
    array of pointers
****************************************/
int **createArray(int rows, int cols){

    int **pointer;
    int i;

    pointer = malloc(sizeof(int *) * rows); /*Allocates memory for a series of pointers (one for each row of the array)*/

    for(i = 0; i < rows; i++){
        pointer[i] = malloc(sizeof(int) * cols); /*Allocates memory for each pointer*/
    }

    return pointer;
}

/***************************************
 freeArray

 In:
    array - the 2D array of pointers
    rows - the number of rows in array
    cols - the number of columns in array
 Out:
    None
 Post:
    Frees the memory that was allocated for the
    inputted array
***************************************/
void freeArray(int **array, int rows, int cols){

    int i;

    /*A for loop to free the rows of the inputted array of pointers*/
    for(i = 0; i < rows; i++){
        free(array[i]); /*Make sure to free the memory allocated for each row before freeing pointers that point to rows*/
        array[i] = NULL; /*As good practice set pointer equal to NULL after freeing it*/
    }

    free(array); /*Now that the rows are freed it is now safe to free the pointers for the rows*/
    array = NULL;

    return;
}
