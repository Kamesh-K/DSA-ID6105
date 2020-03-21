#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>
#define POP_SIZE 100 
const char genes[] = "1234567890"; 
char target[100] = "123456"; 
  
// Create random genes for mutation 
char mut_gene() 
{ 
    int len = strlen(genes); 
    int r = rand()%len; 
    return genes[r]; 
} 
  
// create chromosome or string of genes 
char* create_gnome() 
{ 
    int len = strlen(target); 
    char gnome[100]; 
    for(int i = 0;i<len;i++) 
        gnome[i]= mut_gene(); 
    gnome[len]='\0';
    return gnome; 
} 

// Function to create random numbers
int gen_rand(int l, int r) 
{ 
    int range = (r-l)+1; 
    int randnum = l+(rand()%range); 
    return randnum; 
} 
  
// Strucuture representing organism in population 
struct organism 
{ 
    char chromosome[100]; 
    int fitness; 
}; 
  
void organism_init(struct organism *org, char chromosome[]) 
{ 
    int len=strlen(chromosome);
    for(int i=0;i<len+1;i++)
        org->chromosome[i]=chromosome[i];
    org->fitness = calc_fitness();  
}; 
  
// Perform mating and produce new offspring 
void crossover(struct organism par1,struct organism par2,struct organism *offspring) 
{ 
    // chromosome for offspring 
    char child_chromosome[100]; 
  
    int len = strlen(par1.chromosome); 
    for(int i = 0;i<len;i++) 
    { 
        // random probability  
        float p = gen_rand(0, 100)/100; 
        // Selection of Gene happen with the obtained probability   
        // if p is less than 0.45, insert gene from parent 1  
        if(p < 0.45) 
            child_chromosome[i]= par1.chromosome[i]; 
  
        // if p is between 0.45 and 0.90, insert gene from parent 2 
        else if(p < 0.90) 
            child_chromosome[i]= par2.chromosome[i]; 
  
        // otherwise mututate the gene 
        else
            child_chromosome[i]= mut_gene(); 
    } 
    child_chromosome[len]='\0';
    organism_init(offspring,child_chromosome);
    // Function returning the new offspring  
}; 
  
  
// In this case fitness score is the number of matching characters in the strings   
int calc_fitness(struct organism *org) 
{ 
    int fitness =0,a,b,c,d,e,f;
    a=org->chromosome[0]-'0';
    b=org->chromosome[1]-'0';
    c=org->chromosome[2]-'0';
    d=org->chromosome[3]-'0';
    e=org->chromosome[4]-'0';
    f=org->chromosome[5]-'0';
    fitness = 16 * (a*a*a) - b*b*e - c*a*b*c + c*d*e - e*d - d*a*a + c*a*b*e + f*f*f*a*b - f*d*c;
    //    fitness = 16*(exp(a)) - 10 * (exp(b)) + (c)*(c) + d*d*d + e*e;
};
  
// Function to swap two organisms   
void organism_copy(struct organism *org1, struct organism *org2)
{
    char chrom[100],fit;
    strcpy(chrom,org1->chromosome);
    strcpy(org1->chromosome,org2->chromosome);
    strcpy(org2->chromosome,chrom);
    fit=org1->fitness;
    org1->fitness=org2->fitness;
    org2->fitness=fit;
}
// Comparator Operator for QuickSort inbuilt
int comparator(const void* p, const void* q) 
{ 
    return ((struct organism*)p)->fitness >
                  (((struct organism*)q)->fitness); 
} 

int main() 
{ 
    srand((unsigned)(rand())); 
    printf("Enter the target string : ");
    gets(target);
    puts(target);
    
    double time1,time2;
    // Start Time 
    time1=omp_get_wtime();
    // Generation ID 
    int generation = 0; 
    // Dynamic memory allocation for storing the population
    int found = 0; 
    struct organism population[100];
    // create initial population 
    for(int i = 0;i<POP_SIZE;i++) 
    { 
        char gnome[100];
        int len = strlen(target); 
        for(int i = 0;i<len;i++) 
        gnome[i]= mut_gene();   
        gnome[len]='\0';
    //  puts(gnome);
        organism_init(&population[i],gnome);
         }
    int count=0, prev_fitness;
     while(!found) 
    { 
        // We assumed that lowest fitness score is the best
        // Hence we sort the population in increasing order of fitness score 
       qsort(population, 100, sizeof(struct organism), comparator); 
       // quickSort(population,0,100);
        //printf("%d OLD GEN - %s %d \n",found,population[0].chromosome,population[0].fitness);
        if(count>=15) 
        { 
            printf("Match found at  generation %d - %s ,Fitness - %d \n",generation,population[0].chromosome,population[0].fitness);
            found = 1; 
            break; 
        } 
        // Dynamic memory allocation for offsprings forming new generation  
        struct organism new_generation[100]; 
  
        // Top 10% directly qualifies for the next generation 
        int s = (10*POP_SIZE)/100; 
        for(int i = 0;i<s;i++) 
        {
            organism_init(&new_generation[i],population[i].chromosome);
        } 
        puts(population[0].chromosome);
        // Mating for 90% of Population size is done to maintain the population size as constant value 
        s = (90*POP_SIZE)/100; 
        for(int i = 0;i<s;i++) 
        { 
            int r = gen_rand(0, 50); 
            // Selecting two random parents from the fittest 50 population
            struct organism parent1 = population[r]; 
            r = gen_rand(0, 50); 
            struct organism parent2 = population[r]; 
            struct organism offspring;
            crossover(parent1,parent2,&offspring); 
            organism_init(&new_generation[i+10],offspring.chromosome);  
            puts(new_generation[i+10].chromosome);
        } 
        for (int i=0;i<100;i++)
        population[i] = new_generation[i]; 
        puts(new_generation[0].chromosome);
        generation++; 
        if(population[0].fitness == prev_fitness)
            count++;
        else 
            count=0;
        prev_fitness=population[0].fitness;
     }
     time2=omp_get_wtime();
          printf("Time taken for the process - %f s\n",time2-time1);
    return 0;
}