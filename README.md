# GenNet
A Neurological network that tries to mimic a sinus wave without ever been toled how to do this.
I have created this in a China Internship where I had the honor to get lessens from professor and AI researcher Hugo de Garis.

Some notes I took during these lessons


**Program parameters:**

Parameter | Value | Explenation
--- | --- | --- 
Populationsize | 100 | The amount of chromozones that compete with each other
Number of neurons | 16 | The amount of connections in one chromozones
Number of bits/weight| 10 | (9+1) 9 bits + 1 for + or – =(P)
Length of chromozones| 2560 | N² (P) = 16² (10) 
Mutation rate | ~1 | Bitflips per chromosome per generation
Number of ticks | 60 | Amount of steps one GenNet takes to creata a sinus 

**A: Build population**
Build an neurologic network in an array like the following:

| W11 | W12 | W13 | …. | W21 | W22 | W23 | … | 
| - | - | - | - | - | - | - | - | 

Each position stands for one weight of a connection in the network	
  
Fill the neural network with random numbers:
Build print output function for testing 		
							

B: Calculate weights 
Wtc[c][i][j]  = 1e array is chromosomes, i is the from, j is the where


Array calculate weights:
Do C 1 to 100
	Do  i 1 to 16
	 	Do j  1 to 16
		{
			Look at first bit is it 0 or 1;
			Translate the binary to decimal 
			and store them in the weight
			 tables; 
		}
	}
}


 
 C: Create 2 signal tables
- Start the table at 0 so the only thing that is added in the input (ext)
- One tick you fill on table with neurons next tick fill the other table 
with the outcome of the first one. (The first tick one table is output 
the next tick the same table it is input)


D: Calculate fitness
How to calculate the fitness.
- Store the network signal table with the length of ticks
- Take the best network from a tick and store in the network signal table then calculate the fitness trough calculate the difference between the ideal value and the current value.
- In the fitness table you rank all the Neurons and do GA(rank, kill weak population, 
For the mutation pick a random number 
In the chromosomes and flip it 
(change 1 to 0 and 0 to 1)
For the crossover let the chromosomes have sex.
 
EVOLVABILITY (E.E) USE FULL TRICKS:
What can you do to help the chromosomes to evolve:
Stepwise or incremental
- Make the target smaller
- Store the chromosomes
- Make the problem bigger again
- reload the chromosomes 

If increasing the mutation rate was successful in the past keep on doing this and visa versa if decreasing was successful in the past.
