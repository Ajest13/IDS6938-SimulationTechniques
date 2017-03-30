#Homework 2 :  Discrete-Event Simulation Assignment



## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)



###Extension Request: 2 days



[University of Central Florida](http://www.ist.ucf.edu/grad/)

This is the framework for homework #2. 



The assignment is due: **Tuesday, March 28 at 11:59PM (EST)**





# Introduction

A Discrete-event Model simulates a complex system as an ordered sequence of well-defined events. Mathematically Discrete-event models use Markov Processes, Queuing systems, events, probability / statistics, and random variables. The purpose of this assignment is to learn the mathematical foundations, how to program these models, and how to simulate them. The assignment is due Tuesday, March 28, 2017 at 11:59 P.M.



Major parts for the Assignment

You can think of the assignment broken up to 4 major parts:

* Empirical Tests of Randomness

* Snakes and Ladders (Discrete Event Markov Chains and Monte Carlo Simulations)

* Discrete Event Simulation - Queue Simulation

* Composing a final report



The goal of this assignment is to become familiar with the concepts in the second third of the class. You will be expected to compose a *final report* which demonstrates your understanding on the material in each section of the assignment. Be visual! - Pictures say a thousand words so you do not have to. Show off your different configurations and really explore the assignment.



# Assignment

##Part 0 - Getting Started

Read the assignment. Sync your fork with the [main IDS6938 repository](https://github.com/hepcatjk/IDS6938-SimulationTechniques). Use CMake to create project files for the Homework 2 assignment (*Hint: and Discrete Lecture folders*). Set your *startup project* to the correct project. Test building and executing the homework 2 project. Look over and understand the framework and find the functions you need to edit for the assignment.







##Part 1: Empirical Tests of Randomness (20 pts).

We looked at different ways to generate [pseudo-random numbers](https://en.wikipedia.org/wiki/Pseudorandom_number_generator) and [quasi random numbers](https://en.wikipedia.org/wiki/Low-discrepancy_sequence). Generating random numbers are crucial to Discrete-Event simulations which rely on random variables and stochastic processes. This problem explores different random number generators, distributions, and statistics. Different [C++ pseudo-random numbers engines are instantiated](http://www.cplusplus.com/reference/random/) already for you. Also a a wide variety of standard distributions are implemented. Two quasi random number generators are also provided.

* **(a) - 3pts:** Output the results of five different random number engines, using a uniform distribution for values between [0-100]. Generate useful charts and statistics from the output to analyze how uniform these values truly are. You are expected to look at some advanced statistics and test, for example: tests like the Kolmogorov-Smirnov test, Chi-square test, Autocorrelation test, and Spearman’s Rank Correlation Coefficient are a few examples of ones your could use.)

![](images/Random NumberGeneratorsUniformDistribution.png?raw=true)

#####Descriptive Statistics

![](images/DescriptivesN10000.PNG?raw=true)

#####SpearmansRankCorrelation

![](images/SpearmansRankCorrelation.PNG?raw=true)

* **(b) - 2pts:**  Vary *N* (amount of samples). How do things change.

#####Descriptive Statistics

![](images/DescriptivesN500.PNG?raw=true)

#####AutoCorrelation

![](images/ACF500.PNG?raw=true)



~~~

The main differences when altering N comes with the Standard Error and Confidence level. Both values increase as we decrease N. Therefore, increasing N also increases accuracy and decreases skewness.

~~~

* **(c) - 3pts:** Fix a random engine of your choice from part (a), and now vary five different [distributions](http://www.cplusplus.com/reference/random/) for just the psedo-random numbers. Again, analyze your results with graphs and statistics of choice.

![](images/VaryingDistributions.png?raw=true)

* **(d/f)- 4pts:** Generate random numbers in two-dimensions for a unit square. Plot the results for the different random number engines. The vertical axis should vary N in increasing order. The horizontal axis should show of the random number engines.

####N=1000

![](images/N1000Plots.bmp?raw=true)![](images/SobolPlot1000.bmp?raw=true)

####N=2500

![](images/N2500Plots.bmp?raw=true)![](images/SobolPlot2500.bmp?raw=true)

####N=5000

![](images/N5000Plots.bmp?raw=true)![](images/SobolPlot5000.bmp?raw=true)

* **(e)- 4pts:** Generate random numbers in two-dimensions for a unit square. Plot the results for the different distributions. The vertical axis should vary N in increasing order. The horizontal axis should show of the random number engines. (See [Random Numbers Webcourse page](https://webcourses.ucf.edu/courses/1246518/pages/random-numbers?module_item_id=10541423) for a rough idea what you should produce.)

#####Distribution plots for N=500 

![](images/Chisquare.bmp?raw=true)

![](images/NMsquare.bmp?raw=true)

![](images/WBsquare.bmp?raw=true)

![](images/Poissonsquare.bmp?raw=true)



* * **(f)- 4pts:** Repeat parts (d) and (e) with a unit circle.

~~~

Anwers above.
~~~


Data sheets can be found here 



[Part 1](HW2 Part 1A.xlsx)



[Part 2](HW2 Part 1B.xlsx)



[Part 3](Different Distributions)

                                



##Part 2 - Snakes and Ladders (Discrete Event Markov Chains and Monte Carlo Simulations) (30 pts)



We all love board games. A board game can be viewed mathematically as a Markov chain, where the probability of moving to the next position depends only on the position you are currently at and the chances provided by tossing a dice. For this part of the homework we will simulate the game "*Snakes and Ladders*" (This goes by other names: Chutes and Ladders, Moksha Patam but all essentially the same gameplay.)



| Moksha Patam  | Snakes and Ladders |

| ------------- | ------------- |

| ![](images/snake1.jpg?raw=true)  | ![](images/snake2.jpg?raw=true) |



##### Background

The classic game has 100 positions on the board. You toss one die, and move squares based on the result of the die. If you land on a ladder you move up the ladder to a higher numbered square. If you land on a snake's mouth, you descend to a lower numbered square. For purposes of simulation, we will add one extra square 0 (starting position). So there are 101 positions on the board.



The game is **memoryless** - your progression to the next position is independent of how you arrived there (opposed to Blackjack or Candyland where your progression is based on what cards have been drawn). A Markov Chain defines the probability of a move from state *i* to state *j* by a **Transition Matrix**, *T*. So in the case of *Snakes and Ladders* the dimensions of a transition matrix is 101x101.



* **(a) Null State Game transition matrix - 10pts:** The *null state game* is defined by a game with no snakes and no ladders. This simplifies the game to just the moves of the two dice rolls. Create the transition matrix for the null state game. The Transition Matrix would be decided by the roll of a fair, six-sided die, so it would start to look like:

<BR>![](images/null.png?raw=true)<BR>

From state 0 it is equally probable of landing on squares 1-6. From state 1 t is equally probable of landing on squares 2-7, and so on. Create this transition matrix. The end is trickier, we will consider any roll past 100 a win case. (Opposed to rolling exactly onto square 100.) Confirm you have a well formed stochastic matrix (Write checks for confirming each row of T sums to one and all elements are non-negative). The Transition Matrix methods can be found in the TransitionMatrix.h file.



```cpp

		for (int i = 0; i < TransitionMatrix.rows() - 6; i++) 

		{



			TransitionMatrix(i, i + 1) = prob;

			TransitionMatrix(i, i + 2) = prob;

			TransitionMatrix(i, i + 3) = prob;

			TransitionMatrix(i, i + 4) = prob;

			TransitionMatrix(i, i + 5) = prob;

			TransitionMatrix(i, i + 6) = prob;









		}

		TransitionMatrix(TransitionMatrix.rows() - 6, TransitionMatrix.rows() - 6 + 1) = prob;

		TransitionMatrix(TransitionMatrix.rows() - 6, TransitionMatrix.rows() - 6 + 2) = prob;

		TransitionMatrix(TransitionMatrix.rows() - 6, TransitionMatrix.rows() - 6 + 3) = prob;

		TransitionMatrix(TransitionMatrix.rows() - 6, TransitionMatrix.rows() - 6 + 4) = prob;

		TransitionMatrix(TransitionMatrix.rows() - 6, TransitionMatrix.rows() - 6 + 5) = prob * 2;



		TransitionMatrix(TransitionMatrix.rows() - 5, TransitionMatrix.rows() - 5 + 1) = prob;

		TransitionMatrix(TransitionMatrix.rows() - 5, TransitionMatrix.rows() - 5 + 2) = prob;

		TransitionMatrix(TransitionMatrix.rows() - 5, TransitionMatrix.rows() - 5 + 3) = prob;

		TransitionMatrix(TransitionMatrix.rows() - 5, TransitionMatrix.rows() - 5 + 4) = prob * 3;



		TransitionMatrix(TransitionMatrix.rows() - 4, TransitionMatrix.rows() - 4 + 1) = prob;

		TransitionMatrix(TransitionMatrix.rows() - 4, TransitionMatrix.rows() - 4 + 2) = prob;

		TransitionMatrix(TransitionMatrix.rows() - 4, TransitionMatrix.rows() - 4 + 3) = prob * 4;



		TransitionMatrix(TransitionMatrix.rows() - 3, TransitionMatrix.rows() - 3 + 1) = prob;

		TransitionMatrix(TransitionMatrix.rows() - 3, TransitionMatrix.rows() - 3 + 2) = prob * 5;



		TransitionMatrix(TransitionMatrix.rows() - 2, TransitionMatrix.rows() - 2 + 1) = prob * 6;



		TransitionMatrix(TransitionMatrix.rows() - 1, TransitionMatrix.rows() - 1) = prob * 6;

	//*

	}	

```    



* **(b) Simulate and analyze the results of Null State Game - 10pts:** What is the modal number of moves required by a single player to finish the game? We will be simulating the game two different ways. **(1) Markov Chain**: The game can be analyzed with a row vector, *v* with 101 components, representing the probabilities that the player is on each of the positions. V(0) is (1,0,0,...,0) since we know we start at square 0. v evolves by: <BR>![](images/prob.png?raw=true)<BR>



```cpp

	for (int i = 0; i < TransitionMatrix.rows; i++)

	{

		v = v.transpose() * TransitionMatrix;//ref:Dr.Kider/piazza

	}

```

For this part (1) use the *Markov project* in the Snake and Ladders starter code.<BR>

**(2) Monte Carlo**: he will will use a monte carlo process to solve our Discrete Time Markov Chains. Here (2) use the DTMC project, and utilize the DTMC method similar to what we did in class. <BR><BR>Produce graphs to analyze the results and show how the game evolves over time for both methods. Plot useful statistics of the results such as percentage chance of finishing the game in n-moves, cumulative probability of finishing the game in n-moves, and other ways to convey useful information of the results.

![](images/TotalRollsNull.PNG?raw=true)



```

The modal number of rolls for a single player to complete the Null State game is : 28



The average maximum number of rolls for a single player to complete the Null State game is: 38



The minimum number of rolls for a single player to complete the Null State game is: 17

```

* **(c) Simulate and analyze the results of Snakes and Ladders -10pts:**  Construct a new transition matrix based on the table:





Ladders From  | Ladders To | |  Snakes From  | Snakes To 

-------- | -------- | ------------- | -------- | -------- 

3|19| |11|7

15|37| |18|13

22|42| |28|12

25|64| |36|34

41|73| |77|16

53|74| |47|26

63|86| |83|39

76|91| |92|75

84|98| |99|70

 ```cpp

 for (int i = 0; i < TransitionMatrix.rows(); i++)

	{

		//Ladders

		// 3-19

		if (TransitionMatrix(i, 3) > 0)

		{

			TransitionMatrix(i, 19) = TransitionMatrix(i, 19) + TransitionMatrix(i, 3);

			TransitionMatrix(i, 3) = 0;

		}

		// 15-37

		if (TransitionMatrix(i, 15) > 0)

		{

			TransitionMatrix(i, 37) = TransitionMatrix(i, 37) + TransitionMatrix(i, 15);

			TransitionMatrix(i, 15) = 0;

		}

		// 22-42

		if (TransitionMatrix(i, 22) > 0)

		{

			TransitionMatrix(i, 42) = TransitionMatrix(i, 42) + TransitionMatrix(i, 22);

			TransitionMatrix(i, 22) = 0;

		}

		//  25-64

		if (TransitionMatrix(i, 25) > 0)

		{

			TransitionMatrix(i, 64) = TransitionMatrix(i, 64) + TransitionMatrix(i, 25);

			TransitionMatrix(i, 25) = 0;

		}

		//  41-73

		if (TransitionMatrix(i, 41) > 0)

		{

			TransitionMatrix(i, 73) = TransitionMatrix(i, 73) + TransitionMatrix(i, 41);

			TransitionMatrix(i, 41) = 0;

		}

		//53=74

		if (TransitionMatrix(i, 53) > 0)

		{

			TransitionMatrix(i, 74) = TransitionMatrix(i, 74) + TransitionMatrix(i, 53);

			TransitionMatrix(i, 53) = 0;

		}

		//63-86

		if (TransitionMatrix(i, 63) > 0)

		{

			TransitionMatrix(i, 86) = TransitionMatrix(i, 86) + TransitionMatrix(i, 63);

			TransitionMatrix(i, 63) = 0;

		}

		//76-91

		if (TransitionMatrix(i, 76) > 0)

		{

			TransitionMatrix(i, 91) = TransitionMatrix(i, 91) + TransitionMatrix(i, 76);

			TransitionMatrix(i, 76) = 0;

		}

		//84-98

		if (TransitionMatrix(i, 84) > 0)

		{

			TransitionMatrix(i, 98) = TransitionMatrix(i, 98) + TransitionMatrix(i, 84);

			TransitionMatrix(i, 84) = 0;

		}

		//SNAKES

		//11-7

		if (TransitionMatrix(i, 11) > 0)

		{

			TransitionMatrix(i, 7) = TransitionMatrix(i, 7) + TransitionMatrix(i, 11);

			TransitionMatrix(i, 11) = 0;

		}

		//18-13

		if (TransitionMatrix(i, 18) > 0)

		{

			TransitionMatrix(i, 13) = TransitionMatrix(i, 13) + TransitionMatrix(i, 18);

			TransitionMatrix(i, 18) = 0;

		}

		//28-12

		if (TransitionMatrix(i, 28) > 0)

		{

			TransitionMatrix(i, 12) = TransitionMatrix(i, 12) + TransitionMatrix(i, 28);

			TransitionMatrix(i, 28) = 0;

		}

		//36-34

		if (TransitionMatrix(i, 36) > 0)

		{

			TransitionMatrix(i, 34) = TransitionMatrix(i, 34) + TransitionMatrix(i, 36);

			TransitionMatrix(i, 36) = 0;

		}

		//77-16

		if (TransitionMatrix(i, 77) > 0)

		{

			TransitionMatrix(i, 16) = TransitionMatrix(i, 16) + TransitionMatrix(i, 77);

			TransitionMatrix(i, 77) = 0;

		}

		//47-26

		if (TransitionMatrix(i, 47) > 0)

		{

			TransitionMatrix(i, 26) = TransitionMatrix(i, 26) + TransitionMatrix(i, 47);

			TransitionMatrix(i, 47) = 0;

		}

		//83-29

		if (TransitionMatrix(i, 83) > 0)

		{

			TransitionMatrix(i, 39) = TransitionMatrix(i, 39) + TransitionMatrix(i, 83);

			TransitionMatrix(i, 83) = 0;

		}

		//92-75

		if (TransitionMatrix(i, 92) > 0)

		{

			TransitionMatrix(i, 75) = TransitionMatrix(i, 75) + TransitionMatrix(i, 92);

			TransitionMatrix(i, 92) = 0;

		}

		//99-70

		if (TransitionMatrix(i, 99) > 0)

		{

			TransitionMatrix(i, 70) = TransitionMatrix(i, 70) + TransitionMatrix(i, 99);

			TransitionMatrix(i, 99) = 0;

		}

		//*/

	}

```

![](images/TotalRollSNL.PNG?raw=true)



~~~

The modal number of rolls for a single player to complete the snake and ladders game is : 26



The average maximum number of rolls for a single player to complete the snakes and ladders game is: 101



The minimum number of rolls for a single player to complete the snakes and ladders game is: 6

~~~

~~~

The distribution of the Snakes and Ladders iteration is wider than that of the Null matrix. It has a lower minimum roll and higher average maximum rolls. This is due to the changes of probilities for certain positions within the matrix

~~~



##Part 3 - Discrete Event Simulation - Queue Simulation (30 pts)



This problem will look at queues and commonly used performance measures. For this problem we will look to design a simple airport security check. We will make the following assumptions: (1) there is only one airline - Southwest; (2) passengers' interarrival times are independent and identically distributed (IID) with an exponential distribution with mean 1 / lambda. The service times are also assumed to be IID and exponentially distributed random variables with mean 1 / mu.

<BR>![](images/queue.png?raw=true)<BR>

When a passanger arrives they have to wait in a queue to present their ID and ticket to the gate agent with all the other passengers. Once approved by the agent they will have to pass through a security check. Since this is Orlando, there are only 3 open metal/screening devices open and again passangers have to wait in a queue. After passing through security you again have to wait in a queue to board your plane.



* **(a) - 4pts:** To start create the senario in the figure above in *main.cpp*. Checkin will have a *mu* of 53 and accept new arrivals, the security gates will have a *mu* of 20, and will not accept new arrivials, boarding will have a *mu* of 80. You will have to set up  the appropriate *MM1_Queue* objects to capture the functionality above.





```cpp

 for (int cur_lambda = 3; cur_lambda < 34; cur_lambda++)

   {

	   MM1_Queue Checkin;

	   Checkin.set_file_names("Checkin_log.txt", "Checkin_wait.txt", "Checkin_service.txt");

	   Checkin.set_lambda(cur_lambda);   // for this assignment this is set to a variable from the for loop.

	   Checkin.set_mu(53);

	   Checkin.autogenerate_new_arrivals(true);

	   Checkin.initialize();

	   Checkin.set_seed(rd(), rd());





	   MM1_Queue Officer1;

	   Officer1.set_file_names("Officer1_log.txt", "Officer1_wait.txt", "Officer1_service.txt");

	   Officer1.set_mu(20);

	   Officer1.set_lambda(cur_lambda);

	   Officer1.autogenerate_new_arrivals(false);

	   Officer1.initialize();

	   Officer1.set_seed(rd(), rd());



	   MM1_Queue Officer2;

	   Officer2.set_file_names("Officer2_log.txt", "Officer2_wait.txt", "Officer2_service.txt");

	   Officer2.set_mu(20);

	   Officer2.set_lambda(cur_lambda);

	   Officer2.autogenerate_new_arrivals(false);

	   Officer2.initialize();

	   Officer2.set_seed(rd(), rd());



	   MM1_Queue Officer3;

	   Officer3.set_file_names("Officer3_log.txt", "Officer3_wait.txt", "Officer3_service.txt");

	   Officer3.set_mu(20);

	   Officer3.set_lambda(cur_lambda);

	   Officer3.autogenerate_new_arrivals(false);

	   Officer3.initialize();

	   Officer3.set_seed(rd(), rd());



	   MM1_Queue Boarding;

	   Boarding.set_file_names("Boarding_log.txt", "Boarding_wait.txt", "Boarding_service.txt");

	   Boarding.set_mu(80);

	   Boarding.set_lambda(cur_lambda);

	   Boarding.autogenerate_new_arrivals(false);

	   Boarding.initialize();

	   Boarding.set_seed(rd(), rd());

```



* **(b) - 4pts:** You want to add a check that your process is within an error range *is_within_error_range(float)* where the error range will be 0.002. You also want to process the next event, and add an external arrival where marked.



```cpp

	  for (;

		   !Checkin.is_within_error_range(0.002) ||

		   !Officer1.is_within_error_range(0.002) ||

		   !Officer2.is_within_error_range(0.002) ||

		   !Officer3.is_within_error_range(0.002) //||

		   ;)

```



* **(c) - 3pts:** in *mm1_queue.cpp* : add code to caculate the expected results for: 

  *  expected_server_utilization 

  *    expected idle prob

  *   expected queue length 

  *  expected number customers 

  * expected waiting time

  * expected response time 



```cpp

      expected_server_utilization_ = lambda_/mu_;

      expected_idle_prob_ = 1.0 - expected_server_utilization_;

	  expected_queue_length_ = (expected_server_utilization_)*(expected_server_utilization_) / (expected_idle_prob_);

	  expected_number_customers_ = expected_server_utilization_*expected_idle_prob_*(1.0 / (expected_idle_prob_*expected_idle_prob_));

	  expected_waiting_time_ = expected_server_utilization_ / (mu_ - lambda_);

	  expected_response_time_ = 1.0 / (mu_ - lambda_);

```

      

*  **(d) - 4pts:** Write code to call the functions to output and generate data from the airport senario. Plot and analyze the useful statistics/results in the program of your choice.  (Hint -  basically call  *.output();* on the MM1_Queue objects you create. Hint2 - two other use functions are *get_current_time()* and  *plot_results_output()* call intially on your intial MM1_Queue object.)  



```cpp

	  Checkin.output(); std::cout << "*****" << endl;

	   Officer1.output(); std::cout << "*****" << endl;

	   Officer2.output(); std::cout << "*****" << endl;

	   Officer3.output(); std::cout << "*****" << endl;

	   Boarding.output(); std::cout << "*****" << endl;

	   Checkin.plot_results_output();

	Checkin.get_current_time();

	Checkin.plot_results_output();

```



* **(e) - 15pts:** Download the personal edition of **[Anylogic](http://www.anylogic.com/)**, read through the [documentation](http://www.anylogic.com/learn-simulation) as needed, and set up the same type of simulation discussed above.

![](images/2DALSIM.PNG?raw=true)



##Part 4 - Implementing Extra Features (10 pts)

Implementing 2 features on the extra features list. Pick any feature on the "*extra features*" list below to customize your assignment to fit your interests. Please document this in your writeup. (*Note: These should total 10pts. You could successfully implement a feature worth 10pts or greater. This also fulfills this requirement. The features are assigned points based on difficulty. The 5pt features are more straightforward.*)



* **(10 Points)** - Add a 2D visualization to AnyLogic for Part 3.

![](images/2DALSIM1.PNG?raw=true)



* **(10 Points)** - Add a 3D visualization to AnyLogic for Part 3.

![](images/3DALSIM.PNG?raw=true)



