#include <bits/stdc++.h>
#include <omp.h> 
using namespace std; 
#define POP_SIZE 100 
const string genes = "1234567890";
// Declaring a base case for the length size 
string target = "123456"; 
  
// Create random genes for mutation 
char mut_gene() 
{ 
    int len = genes.size(); 
    int r = rand()%len; 
    return genes[r]; 
} 
  
// create chromosome or string of genes 
string create_gnome() 
{ 
    int len = target.size(); 
    string gnome = ""; 
    for(int i = 0;i<len;i++) 
        gnome += mut_gene(); 
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
public: 
    string chromosome; 
    int fitness; 
    organism(string chromosome); 
    organism mate(organism parent2); 
    int calc_fitness(); 
}; 
  
organism::organism(string chromosome) 
{ 
    this->chromosome = chromosome; 
    fitness = calc_fitness();  
}; 
  
// Perform mating and produce new offspring 
organism organism::mate(organism par2) 
{ 
    // chromosome for offspring 
    string child_chromosome = ""; 
  
    int len = chromosome.size(); 
    for(int i = 0;i<len;i++) 
    { 
        // random probability  
        float p = gen_rand(0, 100)/100; 
        // Selection of Gene happen with the obtained probability   
        // if p is less than 0.45, insert gene from parent 1  
        if(p < 0.45) 
            child_chromosome += chromosome[i]; 
  
        // if p is between 0.45 and 0.90, insert gene from parent 2 
        else if(p < 0.90) 
            child_chromosome += par2.chromosome[i]; 
  
        // otherwise mututate the gene 
        else
            child_chromosome += mut_gene(); 
    } 
    // Function returning the new offspring  
    return organism(child_chromosome); 
}; 
  
  
// In this case fitness score is the number of non-matching characters in the strings   
int organism::calc_fitness() 
{ 
    int len = target.size(); 
    int fitness =0,a,b,c,d,e,f;
    a=chromosome[0]-'0';
    b=chromosome[1]-'0';
    c=chromosome[2]-'0';
    d=chromosome[3]-'0';
    e=chromosome[4]-'0';
    f=chromosome[5]-'0';
    fitness = 16 * (a*a*a) - b*b*e - c*a*b*c + c*d*e - e*d - d*a*a + c*a*b*e + f*f*f*a*b - f*d*c;
    //    fitness = 16*(exp(a)) - 10 * (exp(b)) + (c)*(c) + d*d*d + e*e;
    return fitness;    
}; 
  
// Overloading < operator for sorting 
bool operator<(const organism &ind1, const organism &ind2) 
{ 
    return ind1.fitness < ind2.fitness; 
} 
  
int main() 
{ 
    srand((unsigned)(time(0))); 
    double time1,time2;
    // Start Time 
    time1=omp_get_wtime();
    // Generation ID 
    int generation = 0; 
    double last_fitness = 0,count=0;
    // Dynamic memory allocation for storing the population
    vector<organism> population; 
    bool found = false; 
  
    // create initial population 
    for(int i = 0;i<POP_SIZE;i++) 
    { 
        string gnome = create_gnome(); 
        population.push_back(organism(gnome)); 
    } 
  
    while(! found) 
    { 
  
        // We assumed that lowest fitness score is the best
        // Hence we sort the population in increasing order of fitness score 
        sort(population.begin(), population.end()); 
        // Dynamic memory allocation for offsprings forming new generation  
        vector<organism> new_generation; 
  
        // Top 10% directly qualifies for the next generation 
        int s = (10*POP_SIZE)/100; 
        for(int i = 0;i<s;i++) 
            new_generation.push_back(population[i]); 
        // Mating for 90% of Population size is done to maintain the population size as constant value 
        s = (90*POP_SIZE)/100; 
        for(int i = 0;i<s;i++) 
        { 
            int len = population.size(); 
            int r = gen_rand(0, 50); 
            // Selecting two random parents from the fittest 50 population
            organism parent1 = population[r]; 
            r = gen_rand(0, 50); 
            organism parent2 = population[r]; 
            organism offspring = parent1.mate(parent2); 
            new_generation.push_back(offspring);  
        } 
        if(population[0].fitness == last_fitness)
            count++;
        else 
            count=0;
        last_fitness=population[0].fitness;
        if (count >=15)
            break;
        population = new_generation; 
        cout<<population[0].chromosome<<'\t'<<fitness<<"\n"; 
        generation++; 
     } 
    cout<< "Generation: " << generation << "\t"; 
    cout<< "Final combination generated: "<< population[0].chromosome <<"\t"; 
    cout<< "Fitness: "<< population[0].fitness << "\n"; 
    time2=omp_get_wtime();
    cout<<"Time taken for the complete process = "<<time2-time1<<'s'<<endl;
} 
