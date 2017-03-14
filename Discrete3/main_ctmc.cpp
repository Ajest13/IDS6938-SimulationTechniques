#include <iostream>
#include <functional>   
#include <numeric>  
#include <map>
#include "markov.h"

int main() {
	//SIMULATE CONTINUOUS TIME MARKOV CHAIN
	std::vector< std::vector<double> > matrix(3, std::vector<double>(3)); //initializes a 3x3 matrix with zeros

	//set transition matrix
	matrix[0][1] = 1;
	matrix[1][2] = 1;
	matrix[2][0] = 1;

	int start = 0;
	double T = 8.5;

	//simulate continuous time Markov Chain
	//The Markov Chain is simulated until time T.The initial state is given by 
	//start(the states are indexed from 0 to n - 1 where n is the 
	//number of arrays in transMatrix).
	CTMC continuousMC(matrix);


//	unsigned int N = 50;
//	std::map<int, int> hist;
//	for (unsigned int i = 0; i < N; ++i){
		 continuousMC.simulate(T, start);
//		  ++hist[std::round(continuousMC.getStates().back())];
//		  std::cout << std::endl << "End State is: " << continuousMC.getStates().back() << std::endl << std::endl;
//	  }

	std::vector<double> times = continuousMC.transTimes(); //time in each state
	std::vector<int> states = continuousMC.getStates(); //number it stayed in that state


	for (auto elem : times)
		std::cout << elem << std::endl;
	std::cout << std::endl;

	for (auto elem : states)
		std::cout << elem << std::endl;
	std::cout << std::endl;
	std::cout << std::endl << "End State is: " << states.back() << std::endl << std::endl;

//	  for (auto p : hist)
//		  std::cout << p.first << "\t" << (double)p.second/N << std::endl;

	return 0;
}