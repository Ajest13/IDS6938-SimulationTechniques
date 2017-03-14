#include <iostream>
#include <functional>   
#include <numeric> 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <Eigen\dense>

#include "markov.h"
#include "TransitionMatrix.h"

int main(){

	SetTransitionMatrix();

	//Output Vector
	v.setZero();
	v(0) = 1.0;

	// Print Results to File
	std::ofstream myfile;
	myfile.open("markov_results.txt");

	
   // TODO add Markov vector - Matrix multiplication


	std::cout <<  v << std::endl;
	//myfile << v << std::endl;  //this is just a sample, becareful how you print to file so you can mine useful stats
	
	myfile.close();


  return 1;
}