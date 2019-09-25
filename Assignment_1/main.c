// Program to calculate the roots of a given Quadratic Equation
// The program take "Equations.txt" as input, which contains the a,b,c values in the same order
// The program generates the output file "Solutions.txt" which contains the root of the Quadratic Equation
// To compile and run on linux use the following command :
// gcc main.c -lm -o QuadSolv.out && ./QuadSolv.out 
#include<stdio.h>
#include<math.h>
void input(double *a, double *b, double *c)
{
	// Function to obtain the input from the file
    FILE *input_file;
    input_file=fopen("Equations.txt","r");
    fscanf(input_file,"%lf %lf %lf",a,b,c);
}
double deter(double a, double b, double c)
{
	// Function to calculate the determinant of the quadratic equation
    double det=(b*b)-(4*a*c);
    return det;
}
double QuadSolver(double a,double b,double c)
{
	// Function to calculate the roots of the given quadratic equation
    FILE *output_file;
    output_file=fopen("Solutions.txt","w");
    double sol1,sol2,Isol1,sqrt_det;
    if(a==0)
    {

    	fprintf(output_file, "Not a quadratic equation\n");
    	return 0;
    }
    double det=deter(a,b,c);
    fprintf(output_file,"Nature of Root : ");
	if(det==0)
    {
    	// Case 1: Single real root 
        sol1=(double)(-1*b/(2*a));
        fprintf(output_file,"Single Real Root \nRoot = %lf",sol1);
    }
    else if(det>0)
    {
    	// Case 2: Two real roots  
        sqrt_det=sqrt(det);
        double sol1,sol2;
        sol1=(-1*b+sqrt_det)/(2*a);
        sol2=(-1*b-sqrt_det)/(2*a);
        fprintf(output_file,"Real Roots \nRoot 1 = %lf \nRoot 2 = %lf \n",sol1,sol2);
    }
    else
    {
    	// Case 3: Imaginary roots
        sol1=-1*b/(2*a);
        sqrt_det=sqrt(-1*det);
        Isol1=sqrt_det/(2*a);
        fprintf(output_file,"Imaginary Roots \nRoot 1 = %lf + %lf i \nRoot 2 = %lf - %lf i \n",sol1,Isol1,sol1,Isol1);
    }
}	
int main(){
	// Declaring the variables for the QuadSolver
    double a,b,c;
    // Invoking the input function
    input(&a,&b,&c);
    // Invoking the Quadratic Solver function
    QuadSolver(a,b,c);
    return 0;
}
