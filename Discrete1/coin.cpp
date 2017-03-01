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

int m_heads = 0;
int m_tails = 0;


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


int toss()
{	
	double random_double_value = unif(rng);
	
//TODO
	
}




int main()
{

	IntializeRandom(0.0, 1.0);
    unsigned int range = 10;



	//std::ofstream myfile;


    for (unsigned int i = 0; i < range; i++)
    {
		switch ( toss() ) {
		case 0: 
			//std::cout << "TAILS" << std::endl;
			m_tails++;
			break;      
		case 1: 
			//std::cout << "HEADS" << std::endl;
			m_heads++;
			break;
		}
    }

	std::cout << "--------------" << std::endl;
	std::cout << "HEADS: "<<m_heads << std::endl;
	std::cout << "TAILS: "<<m_tails << std::endl;
	std::cout << "--------------" << std::endl;
	std::cout << "Percentage Heads: " << (double)m_heads/range << std::endl;
	std::cout << "Percentage Tails: " << (double)m_tails / range << std::endl;

	//myfile.close();/

    return 0;
}