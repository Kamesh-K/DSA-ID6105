#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define loop(i,a,b) for(i=a;i<b;i++)
#define N_MAX 10
void input(int *n_years, int *num_iter)
{
  FILE *input_file;
  input_file=fopen("Input.txt","r");
  fscanf(input_file,"%d %d",n_years,num_iter);
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
void SimStock(int *pStockVal,int set_s[], int n_days, int n_iter)
{
  int i;
  int *rand_arr;
  rand_arr=(int*) malloc(n_days*sizeof(int));
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
}
int main()
{
  int n_years,num_iter,n_days,n_iter;
  int *pStockVal;
  int set_s[]={-2,-1,0,1,2};
  n_years=10;
  num_iter=1;
  input(&n_years,&num_iter);
  n_days=n_years*365;
  pStockVal=(int*)malloc(n_days*sizeof(int));
  loop(n_iter,0,num_iter)
    SimStock(pStockVal,set_s,n_days,n_iter);
  return 0;
}
