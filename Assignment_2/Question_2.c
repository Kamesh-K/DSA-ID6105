#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define loop(i,a,b) for(i=a;i<b;i++)
#define N_MAX 10
void input(int *n_years, int *num_iter, int *n_avg)
{
  FILE *input_file;
  input_file=fopen("Input.txt","r");
  fscanf(input_file,"%d %d %d",n_years,num_iter,n_avg);
}
void rand_generator(int arr[],int n)
{
  srand(rand());
  int i;
  FILE *output_file;
  output_file=fopen("RandVal.txt","w");
  fprintf(output_file, "Days,Random Number\n");
  loop(i,0,n)
    {
    arr[i]=(rand()%5);
//    fprintf(output_file,"%d,%d\n",i+1,arr[i]);
    }
}
void MovingAverage(int *pStockVal, double *mv_avg, int n_days, int n_iter, int n_avg)
{
  int i=0,j;
  double avg;
  loop(i,0,n_days)
    {
      avg=0.00;
      loop(j,0,n_avg)
        {
          avg+=pStockVal[i];
        }
        mv_avg[i/n_avg]=(double) (avg/n_avg);
        i=i+n_avg-1;
    }
    FILE *output_file;
    char filename[]="MovingAverageX.txt";
    filename[13]='0'+n_iter;
    output_file=fopen(filename,"w");
    fprintf(output_file, "Days,Stock Price\n");
    loop(i,0,(n_days/n_avg))
      fprintf(output_file,"%d,%lf\n",i+1,mv_avg[i]);
}
void SimStock(int *pStockVal,int set_s[], int n_days, int n_iter, int n_avg)
{
  int i;
  int *rand_arr;
  double *mv_avg;
  rand_arr=(int*) malloc(n_days*sizeof(int));
  mv_avg=(double*)malloc((n_days/n_avg)*sizeof(double));
  rand_generator(rand_arr,n_days);
  pStockVal[0]=set_s[rand_arr[0]];
  loop(i,1,n_days)
  {
    pStockVal[i]=pStockVal[i-1]+set_s[rand_arr[i]];
  }
  FILE *output_file;
  char filename[]="SimStockValX.txt";
  filename[11]='0'+n_iter;
  output_file=fopen(filename,"w");
  fprintf(output_file, "Days,Stock Price\n");
  loop(i,0,n_days)
    fprintf(output_file,"%d,%d\n",i+1,pStockVal[i]);
  MovingAverage(pStockVal,mv_avg,n_days,n_iter,n_avg);
}
int main()
{
  int n_years,num_iter,n_days,n_iter,n_avg;
  int *pStockVal;
  int set_s[]={-2,-1,0,1,2};
  n_years=10;
  num_iter=1;
  input(&n_years,&num_iter,&n_avg);
  n_days=n_years*365;
  pStockVal=(int*)malloc(n_days*sizeof(int));
  loop(n_iter,0,num_iter)
    SimStock(pStockVal,set_s,n_days,n_iter,n_avg);
  return 0;
}
