/*
*  Description:	Here are the neurons build
*  Created on:		24 oktober 2009
*  Author:		    R. Heijligers
*/

/// personal notes:
/// highest number : 1      2      3      4      5      6        7        8         9 bits + 1 +/- bit
/// max values of nr 1      2      4      8      16     32       64       128       256                             512  +
///                                                          
/// Possible numbers 1      0      1      0      1      0        1        0         1                                         
///                  1+     0+     4+     0+     16+    0+       64+      0         256 = 314 / 512 = 0,666015625
///                  .5    .25     .125   .0625  ,03125 ,015625  ,0078125 ,00390625 ,001953125

#include <time.h>


#include <cmath>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

const double TARGET = 0.8;
const int NUMBER_OF_GENERATIONS = 100;
const int NEURONOUTPUT = 0;
const double INPUT_SIGNAL = 0.5;        // the input signal of the chromosone
const int POPULATION_SIZE = 50;         // Population of the chromosones
const int NUMBER_OF_NEURONS = 16;       // Number of neurons that will be created
const int WEIGHT_lENGHT = 10;           // Number of bits/weight
const int POSSIBLE_WEIGHT_VALUES = 512; // Possible values with 10 bits weight (9 bits + 1 for +or �) 
const int NUMBER_OF_BITSTRINGS = 256;   // Number of bitstrings in one chromosome
const float MUTATION_RATE = 10;          // The rate of crossover 1 =  1 bit/ chromozone/generation (
const int NUMBER_OF_TICKS = 50;          // Number of ticks/generations
const int LENGHT_OF_CHROMOZONES = NUMBER_OF_NEURONS * NUMBER_OF_NEURONS * WEIGHT_lENGHT; // Length of chromozones (total amount of weights)

class Chromozone
{
public:
    Chromozone();
    ~Chromozone();
    void Print();
    void InputSignal(double);
    
    void CalculateWeights(int,double);
    void ConvertDecimalToBinairy();
    void ConvertBinairyToDecimal();
    void ClearBinConnectionWeight();
    std::string BinConnectionWeight[NUMBER_OF_BITSTRINGS]; 
    double fitnessTable[NUMBER_OF_TICKS];
    double totalError;
 

    
private:
    void CreateRandomWeights();
    void CreateInitialWeights(float,int);
    void ClearTables();
    void sortSignalTables();
    std::string intToString(int intConvert);

    
    double decConnectionWeights[NUMBER_OF_BITSTRINGS];
    double signalTableEast[NUMBER_OF_NEURONS];
    double signalTableWest[NUMBER_OF_NEURONS];
    
};

Chromozone::Chromozone()
{ 
    CreateRandomWeights();
    ClearTables();
}

Chromozone::~Chromozone()
{ }

void Chromozone::Print()
{
    std::cout << "Fitness is: " << fitnessTable[0];
    std::cout << "\tTotal errorSize: " << totalError << std::endl;
    //for(int i=0;i<NUMBER_OF_BITSTRINGS;i++)
    //{
    //    std::cout << BinConnectionWeight[i] << std::endl;
    //}
}

/// creates random weights but what is the connection between them  
void Chromozone::CreateRandomWeights()
{
    
    for(int i=0; i<NUMBER_OF_BITSTRINGS; i++)
    {
        decConnectionWeights[i] = float (rand()%POSSIBLE_WEIGHT_VALUES)/POSSIBLE_WEIGHT_VALUES;   
    }
}

/// multiply the extValue and weight(because the assiment tells that the weight should be 0 and extValue 0.5 
/// the ideeel value of 0.8 can only be made trough evolutions. 
void Chromozone::CreateInitialWeights(float extValue, int weight)
{
    for(int i=0; i<NUMBER_OF_BITSTRINGS; i++)
    {
        decConnectionWeights[i] = float (extValue * weight);
    }
}


///Convert the Binairy string to de decimal string
void Chromozone::ConvertDecimalToBinairy()
{
    int temp = 0;
    bool negative;
    
    ClearBinConnectionWeight();
    for (int i = 0; i<NUMBER_OF_BITSTRINGS; i++)
    { 
        negative = false;
        temp = int (decConnectionWeights[i]*POSSIBLE_WEIGHT_VALUES);
        if (temp < 0)
        {
            negative = true;
            temp -= (temp * 2);
        }
        for(int j=0; j < WEIGHT_lENGHT; j++)
        {  
            BinConnectionWeight[i] += intToString(temp %2);  /// turn the decimal number into binairy
            temp /= 2;            
        }           
        if (negative)
        {
            BinConnectionWeight[i][WEIGHT_lENGHT-1] = '1'; ///put a one on the end if the number is negative
        }
        std::reverse(BinConnectionWeight[i].begin(),BinConnectionWeight[i].end());  ///reverse the order of the binairy weight so it starts with the least significant number
    }
}

/// cenver the binairy string to a decimal string
void Chromozone::ConvertBinairyToDecimal()
{
    int value;    
    for(int i = 0;i<NUMBER_OF_BITSTRINGS-1;i++)
    {
        value = 1;
        decConnectionWeights[i] = 0;
        
        //loop trough every binairy number in BinConnectionWeight
        for(int j = WEIGHT_lENGHT-1; j > 0; j--)
        {
            if (BinConnectionWeight[i][j] == '1')
            {
                decConnectionWeights[i] += value;
            }
            value *= 2;            
        }
        /// determine if the number is negative
        if(BinConnectionWeight[i][0] == '1')
        {
            decConnectionWeights[i] *= -1;        
        }
        decConnectionWeights[i] /= POSSIBLE_WEIGHT_VALUES;
    }
}

//calculates the weights of the neurons
void Chromozone::CalculateWeights(int ticks, double inputValue) 
{
    double sum;
    totalError = 0;
    int counter;
    for(int nrTicks=0;nrTicks<ticks;nrTicks++)
    {
        counter=0;
        for (int i =0; i<NUMBER_OF_NEURONS; i++) //calculate total chromozome network
        {
            sum = inputValue;
            for (int j=0;j<NUMBER_OF_NEURONS;j++) // calculate one neuron
            {   
                if(nrTicks % 2==0) // if true then even so fill the west table                    
                {
                    sum += decConnectionWeights[counter] * signalTableEast[j];
                    counter++;
                }
                else // if false then odd so fill the east table
                {
                    sum += decConnectionWeights[counter] * signalTableWest[j];            
                    counter++;
                }
            }
            if(nrTicks % 2==0) // even or uneven
            {
                //squash function and filling of the signal table East
                signalTableWest[i]  = sum / (abs(sum) +1);                
            }           

            else
            {
                //squash function and filling of the signal table East
                signalTableEast[i]  = sum / (abs(sum) +1);                
            }
        }        
    
        // give the value of one neoron as a output of the cromosome (one time for every tick)
        if(nrTicks % 2==0)
        {
            fitnessTable[nrTicks] = signalTableWest[NEURONOUTPUT];
            totalError += (signalTableWest[NEURONOUTPUT] - TARGET) * (signalTableWest[NEURONOUTPUT] - TARGET);
        }
        else
        {
           fitnessTable[nrTicks] = signalTableEast[NEURONOUTPUT];
           totalError += (signalTableEast[NEURONOUTPUT] - TARGET) * (signalTableEast[NEURONOUTPUT] - TARGET);
        }
    }
    totalError = 1 / totalError;
}

void Chromozone::ClearTables()// resets the fitness and signal tables 
{     
    for (int i = 0; i < NUMBER_OF_NEURONS; i++)
    {
        signalTableWest[i] = 0; 
        signalTableEast[i] = 0;  
    }
}

///inputs the signal in one of the neurons (East signal table)
void Chromozone::InputSignal(double signal)
{
    srand((unsigned)time(NULL));
    int random;
    random = int (rand() %NUMBER_OF_NEURONS);
    signalTableEast[random] = signal;
}

///Convert an int to a string this function is used in the ConvertDecimalToBinairy function
std::string Chromozone::intToString(int intConvert)
{ 
    std::ostringstream temp;
    temp<<intConvert;
    return temp.str();
}

void Chromozone::ClearBinConnectionWeight()
{
    for (int i = 0;i<NUMBER_OF_BITSTRINGS;i++)
    {
        BinConnectionWeight[i] = "";
    }
}

//-------------------------------------------Main program-------------------------------------------
void SortPopulationAndFitnessTable();
void EliminateWeakChromosomes();
void ConvertPopulationToBinairy();
void ConvertPopulationToDecimal();
void Mutation();
void StorePopulation();
void AskForPopulationSource();


int notChanged;
Chromozone tempChrom;
Chromozone population[POPULATION_SIZE]; 


int main()
{
    AskForPopulationSource();
    srand((unsigned)time(NULL));
    notChanged = 0;
    int generationCount = 0;    
    while(notChanged <= NUMBER_OF_GENERATIONS) //number of generations
    {
        
        for(int j=0; j<POPULATION_SIZE; j++)   // the size of the population
        {                       
             population[j].CalculateWeights(NUMBER_OF_TICKS,INPUT_SIGNAL);  // calculate the weights of the chromosomes
        } 
        // GA
        SortPopulationAndFitnessTable();   
        EliminateWeakChromosomes();
        ConvertPopulationToBinairy();
        Mutation(); 
        ConvertPopulationToDecimal();

        if(tempChrom.totalError == population[0].totalError)
        {
            notChanged++;
        }else{
            tempChrom = population[0];
            //notChanged = 0;
            notChanged++;
        }

        std::cout<< "\nGeneration " << generationCount << std::endl;
        std::cout<< "Elite not changed x "<< notChanged << std::endl;
        for(int j=0; j<POPULATION_SIZE; j++)   // the size of the population
        {
            population[j].Print();
        }
        

        generationCount++;
    }
    StorePopulation();
}

/// calculates how close the given value is near the target value (is used in the SortPopulationAndFitnessTable function)
double giveTargetValue(double calculate)
{
    double difference = calculate - TARGET;
    if(calculate < 0.)
    {
        difference *= difference;
    }    
    return difference;
}


void SortPopulationAndFitnessTable()
{
    Chromozone temp2;// = new Chromozone();
    for(int i=0; i < POPULATION_SIZE;i++)
    {
        for(int j = 1; j < POPULATION_SIZE-i;j++)
        {
            if (population[j-1].totalError < population[j].totalError)
            {
                temp2 = population[j-1];
                population[j-1] = population[j];
                population[j] = temp2;
            }
        }
    }
}

/// copies the top (elite) cromosomes over the bottom chromosomes
void EliminateWeakChromosomes()
{
    int halfPopulation = POPULATION_SIZE / 2;
    for(int i=0; i < halfPopulation;i++)
    {
        population[i+halfPopulation] = population[i];
    }
}

/// (flip the bit) mutate the a random bit of a random neuron in a random chromosome.
void Mutation()
{
    srand((unsigned)time(NULL));
    int rapedChromosome = int(rand()%(POPULATION_SIZE-1))+1;
    int rapedNeuron;
    int rapedBit;
    for(int i=0; i < MUTATION_RATE ;i++)
    {
        rapedBit = int(rand()%WEIGHT_lENGHT);
        rapedNeuron = int(rand()%NUMBER_OF_BITSTRINGS);

        population[rapedChromosome].ConvertDecimalToBinairy();
        if(population[rapedChromosome].BinConnectionWeight[rapedNeuron][rapedBit] == 1)
        {
            population[rapedChromosome].BinConnectionWeight[rapedNeuron][rapedBit] = 0;
        }
        else
        {
             population[rapedChromosome].BinConnectionWeight[rapedNeuron][rapedBit] = 1;
        }
    }
    std::cout << "Chromosome: " << rapedChromosome << " is raped\n";
}

void ConvertPopulationToDecimal()
{
    for(int j=0; j<POPULATION_SIZE; j++)   // the size of the population
    {
        population[j].ConvertBinairyToDecimal();
    }
}

void ConvertPopulationToBinairy()
{
    for(int j=0; j<POPULATION_SIZE; j++)   // the size of the population
    {
        population[j].ConvertDecimalToBinairy();
    }
}

void StorePopulation()
{
    std::string anwser;
    std::cout << "do you wish to store the current population? type: Y/N" << std::endl;
    std::cin >> anwser;
    if(anwser == "Y")
    {        
        std::ofstream myfile ("Population.gen");
        if (myfile.is_open())
        {
            for(int nrOfCromosomes = 0;nrOfCromosomes < POPULATION_SIZE; nrOfCromosomes++)
            {
                for(int nrOfBitStrings = 0;nrOfBitStrings < NUMBER_OF_BITSTRINGS; nrOfBitStrings++)
                {
                    myfile << population[nrOfCromosomes].BinConnectionWeight[nrOfBitStrings];
                }
                myfile << "\n";
            }          
            myfile.close();
        }
        else std::cout << "Unable to open file";
    }

}



void AskForPopulationSource()
{
    std::string anwser;
    std::cout << "do you wish to start load new population? type: Y/N" << std::endl;
    std::cin >> anwser;
    if(anwser == "Y")
    {
        std::string line;
        std::string oneWeight;
        std::ifstream myfile ("Population.gen");
        if (myfile.is_open())
        {
            for(int nrOfCromosomes = 0;nrOfCromosomes < POPULATION_SIZE; nrOfCromosomes++)
            {
                population[nrOfCromosomes].ClearBinConnectionWeight();
                getline(myfile,line);
                for(int nrOfBitStrings = 0;nrOfBitStrings < NUMBER_OF_BITSTRINGS; nrOfBitStrings++)
                {
                    population[nrOfCromosomes].BinConnectionWeight[nrOfBitStrings] += line.substr((nrOfBitStrings*10),10);
                
                }
                 population[nrOfCromosomes].ConvertBinairyToDecimal();
            }
         /*if(myfile.eof())
         {
             std::cout" copied\n";
         }*/
        }
        else 
        {
            std::cout << "Unable to open file\n Starting new Population";
        }
    }
}

;            
    