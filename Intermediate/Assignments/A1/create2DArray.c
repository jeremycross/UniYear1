/***********************create2DArray.c*****************************
Student Name: Jeremy Cross                    Email Id: jcross04
Date: January 24th, 2019                      Course Name: CIS 2500
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
********************************************************************/

#include "arrayDefns.h"
#include <stdio.h>
#include <stdlib.h>


/*****************************************
 create2DArray

 In:
    rows - number of rows in array to be created
    cols - number of columns in array to be created
 Out:
    Returns a pointer that points to the memory
    allocated for the 2D array
 Post:
    Creates a pointer that points to memory allocated
    for a 2D array of a size based on the inputted number
    of rows and columns
******************************************/
int *create2DArray(int rows, int cols){

    int *pointer; /*pointer for memory allocated to the array*/

    pointer = malloc(sizeof(int) * ((rows * cols) + 2)); /*Allocating enough memory for a rows x cols 2D array + 2 extra slots to store extra info*/

    pointer[0] = rows; /*pointer to store total number of rows in array*/
    pointer[1] = cols; /*pointer in memory to store total number of columns in array*/

    return pointer;
}

/*****************************************
 set2DElement

 In:
    array - pointer that points to allocated memory,
            operated as an array
    row - row where value to be set will be placed in the 2D
          array (rows are inferred to begin at 0)
    col - column where value to be set will be placed
          (columns are inferred to begin at 0)
    value - The value to be placed in array
 Out:
    None
 Post:
    Will place an integer (value) at the coordinates
    row, col. This is done by treating the pointer as a 2D array
    even though it truly functions as a 1D array
*****************************************/
void set2DElement(int *array, int row, int col, int value){

    /*Row and col are inferred to start at 0 (similar to how 2D array indices function)*/

    array[2+(row*array[1])+col] = value; /*Setting the element at a 2D coordinate as a 1D address, 0 address starts at 2 (due to extra stored info)*/

    return;
}

/****************************************
 get2DElement

 In:
    array - pointer that points to allocated memory,
            operated as an array
    row - row coordinate of element to be found
          (rows are inferred to begin at 0)
    col - column coordinate of element to be found
          (columns are inferred to begin at 0)
 Out:
    Returns the value located at (row, col) in the 2D array
 Post:
    Returns the value located in the 1D array given its 2D
    coordinates
****************************************/
int get2DElement(int *array, int row, int col){

    /*Row and col are inferred to start at 0 (similar to how 2D array indices function)*/
    return array[2+(row*array[1])+col]; /*returns value at the 1D address corresponding to its 2D coordiantes*/
}

/**************************************
 free2DArray
 In:
    array - pointer that points to allocated memory,
            operated as an array
 Out:
    None
 Post:
    Frees the memory that was allocated for the inputted pointer
**************************************/
void free2DArray(int *array){

    free(array); /*Free memory allocated for inputted array (pointer)*/
    array = NULL; /*Set pointer equal to NULL after freeing as safe practice*/

    return;
}
