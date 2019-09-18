#include<stdio.h>
#include<math.h>
double deter(double a, double b, double c)
{
    double det=(b*b)-(4*a*c);
    return det;
}
double QuadSolver(double a,double b,double c)
{
    FILE *output_file;
    output_file=fopen("Solutions    .txt",'n');
    double sol1,sol2,Isol1,sqrt_det;
    double det=deter(a,b,c);
    if(det==0)
    {
        sol1=(double)(-1*b/(2*a));
        fprintf(output_file,"Single Solution = %lf",sol1);
    }
    else if(det>0)
    {
        sqrt_det=sqrt(det);
        double sol1,sol2;
        sol1=(-1*b+sqrt_det)/(2*a);
        sol2=(-1*b-sqrt_det)/(2*a);
        fprintf(output_file,"Real Roots \n Root 1 = %lf \n Root 2 = %lf \n",sol1,sol2);
    }
    else
    {
        sol1=-1*b/(2*a);
        sqrt_det=sqrt(-1*det);
        Isol1=sqrt_det/(2*a);
        fprintf(output_file,"Imaginary Roots \n Root 1 = %lf + %lf i \n Root 2 = %lf - %lf i \n",sol1,Isol1,sol1,Isol1);
    }
}
void input(double a, double b, double c)
{
    FILE *input_file;
    input_file=fopen("Equations.txt",'r');
    fscanf(input_file,"%lf %lf %lf",&a,&b,&c);
}
int main(){
    int i,j,k;
    double a,b,c,det,sol;
    input(a,b,c);
    printf("a = %lf b=%lf c=%lf\n",a,b,c);
    QuadSolver(a,b,c);
    return 0;
}
