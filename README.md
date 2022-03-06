# GenNet
A Neurological network that tries to mimic a sinus wave without ever been told how to do this.
I have created this in a China Internship where I had the honor to get lessens from professor and AI researcher Hugo de Garis.

It is a C++ console application.
Unfortionatlly I lost the end resul code, this is an early version. 


Some notes I took during these lessons:

**Program parameters:**

Parameter | Value | Explanation
--- | --- | --- 
Populationsize | 100 | The amount of chromosomes that compete with each other
Number of neurons | 16 | The amount of connections in one chromosomes
Number of bits/weight| 10 | (9+1) 9 bits + 1 for + or – =(P)
Length of chromosomes| 2560 | N² (P) = 16² (10) 
Mutation rate | ~1 | Bitflips per chromosome per generation
Number of ticks | 60 | Amount of steps one GenNet takes to create a sinus 

**A: Build population**
Build a neurologic network in an array like the following:

| W11 | W12 | W13 | …. | W21 | W22 | W23 | … | 
| - | - | - | - | - | - | - | - | 


<img src="https://user-images.githubusercontent.com/19152655/156929699-a46540c8-dee2-40be-878e-f1ec0704d356.png" width="334" height="174">


Each position stands for one weight of a connection in the network	
  
Fill the neural network with random numbers:
Build print output function for testing 		
							

**B: Calculate weights**

`Wtc[c][i][j]`  = 1e array is chromosomes itself

i is from where, j is the where to (the interconnection of neurons)

Array calculate weights:
```
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
```

 <img src="https://user-images.githubusercontent.com/19152655/156931013-5549f503-b4e5-493e-a340-ca84331913b0.png" width="475" height="212">
 
 
 **C: Create 2 signal tables**
 
- Start the table at 0 so the only thing that is added is the input (external value)
- One tick you fill on table with neurons next tick fill the other table 
with the outcome of the first one. (The first tick one table is output 
the next tick the same table it is input)


**D: Calculate fitness**

How to calculate the fitness.
- Store the network signal table with the length of ticks
- Take the best network from a tick and store in the network signal table then calculate the fitness trough calculate the difference between the ideal value and the current value.
- In the fitness table you rank all the Neurons and do GA(rank, kill weak population, 
For the mutation pick a random number 
In the chromosomes and flip it 
(change 1 to 0 and 0 to 1)
For the crossover let the chromosomes have sex.
 
**EVOLVABILITY (E.E) USE FULL TRICKS:**

What can you do to help the chromosomes to evolve:

Stepwise or incremental:
- Make the target smaller
- Store the chromosomes
- Make the problem bigger again
- reload the chromosomes 

If increasing the mutation rate was successful in the past keep on doing this and visa versa if decreasing was successful in the past.




The result:

<img src="https://user-images.githubusercontent.com/19152655/156931411-5d0869fe-34b5-47dc-b193-f2389dc0f1c9.png" width="457" height="555">

- The block that you see is one population of cromosomes
- The Fitness is the end result value
- The errorsize tells how far there of from there end goal

**What happens**
- The application starts with a new set of random generated weights for each chromosome (The weight are the interconnections between the neurons, the thickness of all the weights determines the chromosome's end value. (see the weight as the thickness of a real neuron, the thicker it is the stronger the signals are that pass through it)
- The population is a list of these chromosomes.
- It is evaluated how far these neurons are of from their end goal. (there fitness is calculated)
- The 50% part of the population that is most wrong is killed/removed.
- In the top 50% (the most elite chromosomes) mutations are applied, bits are flipped in their weights.
- There is a change that this evolution brought something good, in that case in the next fitness calculation they will reach again the top 50% part. if it was a bad mutation they are killed.
- This process repeats itself until for example 100.000 times. You will see that some chromosomes become really good in reaching their best possible fitness.

The nice thing is that you don't need to tell the chromosomes how to reach their goal, in many evolutions they will reach it without help.
Now the goal is simple, but this app was the beginning of an application where a stick figure with legs though itself how to walk in the most efficient way.
It could also be an application that controls valves of a rocket, and then teach itself how to reach the moon in the most efficient way.

I had a lot of fun with this app and became truly inspired with the possibilities of these AI application. Hopefully it may also inspire you.
