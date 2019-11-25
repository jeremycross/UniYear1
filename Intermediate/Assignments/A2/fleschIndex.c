/************************fleschIndex.c*****************************
Student Name: Jeremy Cross                    Email Id: jcross04
Date: February 11th, 2019                     Course Name: CIS 2500
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

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int isVowel(char);
int checkPunct(char);

int main(int arg, char** argc){

    FILE *fp;
    char c;
    char prevC;
    char test;
    int index = 0;
    int minSyll = 0; /*Tracks how many syllables for current word*/
    int firstRun = 1; /*Used for logic for first run through the while loop*/
    int sumSyll = 0;
    int sumWords = 0;
    int sumSentence = 0;

    if(arg != 2){
        printf("This program requires a single text file passed along with the command to run\n"); /*Incorrect number of arguments was passed to run program*/
        return (-2);
    }

    fp = fopen(argc[1], "r"); /*open file in read mode*/

    if(fp == NULL){
        printf("Cannot open file or file doesn't exist\n"); /*Issue finding file, cannot run program*/
        return (-1);
    }


    do{ /*Loop will run until fgetc returns EOF and reaches break that checks for C == -1 (meaning c is at end of file)*/

        c = fgetc(fp); /*Set current character to next character in file*/

        if(firstRun == 1){ /*For first run through of loop*/
            prevC = c;
            c = fgetc(fp);
            firstRun--; /*no longer first run through of loop*/
        }

        if(c != ' ' && c != '\n'){ /*If current char is anything but a space or a newline*/
            if(checkPunct(prevC) == 1 && (checkPunct(c) != 1 || c == -1)){ /*If previous character is punctuation and current char is not punction or IS end of file*/
                sumSentence++; /*Increment number of sentences*/
                if(checkPunct(prevC) == 1 && c == -1){ /*The last character of file is a punctuation, word count needs to be incremented*/
                    sumWords++;
                }
            }
            if(isVowel(prevC) == 1 && isVowel(c) == 0){ /*Each group of vowels counts as a syllable*/

                test = toupper(prevC);
                if(test == 'E' && checkPunct(c) == 1){ /*If E is at end of word do not count as extra syllable*/
                }
                else{
                    sumSyll++;
                    minSyll++; /*Number which tracks number of syllables current word has*/
                }
            }
        }
        else{
            if(isVowel(prevC) == 1 && (c == '\n' || c == ' ')){ /*If previous character is a vowel and c is a space or newline, then that is a group of vowels, increment syllable count*/
                sumSyll++;
                minSyll++;

                test = toupper(prevC);
                if(test == 'E'){ /*If e is at end of a word then it should not count as a syllable, reduce syllable count by 1*/
                    sumSyll--;
                    minSyll--;
                }
            }

            if(checkPunct(prevC) == 1 && (checkPunct(c) != 1 || c == -1)){ /*Check if previous character was punctuation and current character is not punctuation or EOF, sentence count needs to be adjusted*/
                sumSentence++;

                if(c == -1){ /*If current char is at EOF, number of words needs to be adjusted (or else it will be off by one)*/
                    sumWords++;
                }
            }

            if(prevC == ' ' || prevC == '\n'){ /*If previous char is a space or a new line, no need to increment word count (multiple spaces between words)*/
            }
            else{
                sumWords++;

                if(minSyll == 0){ /*End of word has been reached, if no syllables were counted for word, syllable count is increased by one*/
                    sumSyll++;
                }
            }

            minSyll = 0;
        }

        if(c == -1){ /*If End of File was reached with the fgetc at beginning of loop, then c will be equal to -1 and the loop will be exited*/
            break;
        }

        prevC = c; /*Set previous character to current character (current character will be replaced with a new one at beginning of loop)*/

    } while(1);

    fclose(fp);

    index = round(206.835 - (84.6 * (sumSyll/sumWords)) - (1.015 * (sumWords/sumSentence)));

    printf("Flesch Index = %d\n", index);
    printf("Syllable Count = %d\n", sumSyll);
    printf("Word Count = %d\n", sumWords);
    printf("Sentence Count = %d\n", sumSentence);

    return 0;
}

/****************************************
 isVowel

 In:
    input - inputted character
 Out:
    If inputted character is a vowel (including y)
    then returns 1, otherwise returns 0
 Post:
    Checks if inputted char is a vowel,
    if it is returns 1, if not returns 0.
    This function is used in the logic of
    counting syllables
****************************************/
int isVowel(char input){

    input = toupper(input);
    if(input == 'A' || input == 'E' || input == 'I' || input == 'O' || input == 'U' || input == 'Y'){
        return 1;
    }

    return 0; /*Is not a vowel*/
}

/*****************************************
 checkPunct

 In:
    input - inputted character
 Out:
    If inputted char is a ? or ! or . or : or ;
    then return 1, otherwise return 0;
 Post:
    Checks if inputted character is a piece
    of punctuation, if it is returns 1,
    if not returns 0. This function is used
    for the logic of counting sentences, words
    and syllables in main
*****************************************/
int checkPunct(char input){

    if(input == '?' || input == '!' || input == '.' || input == ':' || input == ';'){
            return 1;
        }

    return 0;
}

