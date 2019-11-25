#include <stdio.h>
int main(void){
	const double PI = 3.14159265;
	double r;
	scanf("%lf", &r);
	printf("The area of a circle with radius %lf is: %lf\n", r, PI*r*r);
	printf("The circumference of the circle is: %lf\n", 2*PI*r);
	return 0;
}
