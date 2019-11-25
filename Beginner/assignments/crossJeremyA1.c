/************************crossJeremyA1.c *********************
Student Name: Jeremy Cross                    Email Id: jcross04
Date: October 5th, 2018                       Course Name: CIS 1500
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
/*********************************************************
                Compiling the program
*********************************************************
The program should be compiled using the following flags:
-std=c99
-Wall
compiling: gcc -Wall -std=c99 crossJeremyA1.c -o asn1
*********************************************************
                Running the Program
*********************************************************
running: ./asn1
make sure to compile program before using this command to run it
The user is prompted for 11 different inputs before the output is
generated.
*********************************************************/




#include <stdio.h>

int main(void){

	double wLabs;
	double dailyPract;
	double lExam1;
	double lExam2;
	double asgn1;
	double asgn2;
	double asgn3; //declaration of variables to be used as marks

	int mossAsgn1;
	int mossAsgn2;
	int mossAsgn3; //declaration of moss output variables, if all of these are 0 then an automatic fail is given

	double desiredGr; //variable used to store desired grade

	double wLabsPer;
	double dailyPractPer;
	double lExam1Per;
	double lExam2Per;
	double asgn1Per;
	double asgn2Per;
	double asgn3Per; //these variables store the weighted mark of each element

	double bonusLabExams = 0.0; //this variable is only needed if 100 is achieved on both lan exams

	double currentGr; //variable to store current course mark

	double final; //mark needed on final to achieve desired mark, this is what we are calculating

	//INPUT
	printf("Enter the following marks (each out of 100): \n\n");

	printf("Weekly Labs: ");
	scanf("%lf", &wLabs); //sets wLabs to inputted number
	printf("Daily Practice: ");
	scanf("%lf", &dailyPract);
	printf("Lab Exam I: ");
	scanf("%lf", &lExam1);
	printf("Lab Exam II: ");
	scanf("%lf", &lExam2);
	printf("Assignment1: ");
	scanf("%lf", &asgn1);
	printf("MOSS output for A1 (0/1): ");
	scanf("%d", &mossAsgn1);
	printf("Assignment2: ");
        scanf("%lf", &asgn2);
        printf("MOSS output for A2 (0/1): ");
	scanf("%d", &mossAsgn2);
	printf("Assignment3: ");
        scanf("%lf", &asgn3);
        printf("MOSS output for A3 (0/1): ");
	scanf("%d", &mossAsgn3);

	if(mossAsgn1 == 0 && mossAsgn2 == 0 && mossAsgn3 == 0){     //if student gets flagged for academic misconduct on all 3 assignments, print this message
		printf("**************************************************\n");
		printf("You cannot pass the course - try harder next time.\n");
		printf("**************************************************");
	}
	else{                        //this branch runs as long as the student did not get flagged on all 3 assignments
		if(mossAsgn1 == 0){  //if assignment 1 was flagged with a moss test failure run this branch, which sets assignment 1 mark to 0
			asgn1 = 0.0;
		}
		if(mossAsgn2 == 0){  //if assignment 2 was flagged with a moss test failure set its mark to 0
			asgn2 = 0.0;
		}
		if(mossAsgn3 == 0){  //if assignment 3 was flagged set its mark to 0
			asgn3 = 0.0;
		}


		printf("\n\nHow much do you desire as an overall course grade: ");
		scanf("%lf", &desiredGr); //sets desiredGr to inputted number

		//CALCULATIONS
		wLabsPer = (wLabs * 0.1); //Assigns wLabsPer with the weighted value(10% of overall grade in this case) of the wLabs(weekly labs) mark
		dailyPractPer = (dailyPract * 0.1);
		lExam1Per  = (lExam1 * 0.1);
		lExam2Per = (lExam2 * 0.1);
		asgn1Per = (asgn1 * 0.05);
		asgn2Per = (asgn2 * 0.1);
		asgn3Per = (asgn3 * 0.1);

		currentGr = (wLabsPer + dailyPractPer + lExam1Per + lExam2Per + asgn1Per + asgn2Per + asgn3Per); //calculation of the students current grade of 65


		if((int)lExam1 == 100 && (int)lExam2 == 100){ //first the double values are casted to ints to ensure that the comparison works properly: if 100 is achieved on both lab exams, student 3 bonus marks
			bonusLabExams = 3.0;
		}
		final = (desiredGr - currentGr - bonusLabExams); //calculation of what mark out of 35 student needs on final to get desired grade


		//OUTPUT
		printf("*********************************************************\n");
		printf("Assessment            Weight          Marks\n");
		printf("---------------------------------------------------------\n");
		printf("Weekly Labs           10              %.2lf\n", wLabs);
		printf("Daily Practice        10              %.2lf\n", dailyPract);
		printf("Lab Exam I            10              %.2lf\n", lExam1);
		printf("Lab Exam II           10              %.2lf\n", lExam2);
		printf("Bonus from lab exams:                 %.0lf\n", bonusLabExams);
		printf("Assignment 1          5               %.2lf\n", asgn1);
		printf("Assignment 2          10              %.2lf\n", asgn2);
		printf("Assignment 3          10              %.2lf\n", asgn3);
		printf("Final Exam            35       To be determined\n\n");
		printf("*********************************************************\n");
		printf("\nCurrent course mark = %.2lf / 65.00",currentGr+bonusLabExams); //currentGr + bonusLabExams is the current course mark
		printf("\nYou need %.2lf / 35.00 to reach your goal (%.0lf)", final, desiredGr);
		printf("\nIn percentage, you need %.0lf %% to reach your goal (%.0lf)\n", (final/35.0)*100, desiredGr); //simple calculation of what percent is needed on the final
		printf("*********************************************************\n");
	}//end of else


	return 0;
}//end of main


