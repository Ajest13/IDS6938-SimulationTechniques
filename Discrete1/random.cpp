//Eulers Method to solve a differential equation
#define _USE_MATH_DEFINES

#include <cmath>
#include<iostream>
#include<iomanip>
#include<math.h>

#include<random>
#include <chrono>

//#include <fstream>


std::mt19937_64 rng;
std::uniform_real_distribution<double> unif;

bool IntializeRandom(double lower, double upper)
{
	
	// initialize the random number generator with time-dependent seed
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);
	// initialize a uniform distribution between 0 and 1
	unif = std::uniform_real_distribution<double>(lower, upper);
	// ready to generate random numbers
	
	return true;
}







int main()
{

	IntializeRandom(0.0, 1.0);
    unsigned int range = 30;

	//std::ofstream myfile;

    for (unsigned int i = 0; i < range; i++)
    {
		std::cout << unif(rng) << std::endl;
		//myfile << unif(rng) << std::endl;  // send to file.
    }

	//myfile.close();/

    return 0;
}