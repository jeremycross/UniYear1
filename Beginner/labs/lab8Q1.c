#include <stdio.h>

void areaPerimeter (double, double*, double*);

int main(){
	double length, area, perimeter;

	printf("Enter the length in cms: ");
	scanf("%lf", &length);

	areaPerimeter(length, &area, &perimeter);

	printf("Area of a square of length %.2lf cms = %.2lf cms squared\n", length, area);
	printf("Perimeter of a sqaure of length %.2lf cms = %.2lf cms\n", length, perimeter);

	return 0;
}

void areaPerimeter(double len, double* area, double* per){
	*area = len * len;
	*per = len * 4;

	return;
}
