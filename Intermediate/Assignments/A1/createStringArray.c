/************************createStringArray.c **************************
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
#include <string.h>


/*********************************************
 createStringArray

 In:
    number - the number of strings that memory will be
             allocated for (each string is given 255 characters);
 Out:
    Returns the array of pointers for the strings
 Post:
    Given a inputted number the function allocates enough
    memory for the inputted number of strings each with 255 characters
*********************************************/
char **createStringArray(int number){

    char **cPointer;
    int i;

    cPointer = malloc(sizeof(char*) * number); /*Allocates a series of pointers to point to the individual strings*/

    for(i = 0; i < number; i++){
        cPointer[i] = malloc(sizeof(char) * 255); /*Allocates memory for 255 characters for each string*/
    }

    return cPointer;
}

/*********************************************
 setStringArray

 In:
    array - 2D array of character pointers
            used to store a series of strings
    index - the index of the array to play inputted string
    string - string to be added to the array
 Out:
    None
 Post:
    Places an inputted string at a given index in the
    2D array
*********************************************/
void setStringArray(char **array, int index, char *string){

    strcpy(array[index], string); /*Sets pointer at array[index] to the start of the inputted string*/

    return;
}

/*******************************************
 getStringArray

 In:
    array - 2D array of character pointers
            used to store a series of strings
    index - the index of the string to be returned
 Out:
    The string at the inputted index is returned
 Post:
    Returns the string in the 2D array at the
    inputted index
*******************************************/
char *getStringArray(char **array, int index){

    return array[index];
}

/******************************************
 freeStringArray

 In:
    array - 2D array of character pointers
            used to store a series of strings
    number - the number of strings that can be stored in array
 Out:
    None
 Post:
    Frees all memory that was allocated for the inputted
    array of pointers
******************************************/
void freeStringArray(char **array, int number){

    int i;

    for(i = 0; i < number; i++){
        free(array[i]); /*Make sure to free each row of pointers before freeing the pointers to the rows*/
        array[i] = NULL; /*It is safe practice to set a pointer to NULL after freeing*/

    }

    free(array); /*Now that the rows are free it is safe to free the pointer to the rows*/
    array = NULL;

    return;
}
