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


/* Number of realisations per run */
int N;
/* Number of runs */
int M;



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




/**
* Generates <i>N</i> birthdays.
* @returns true if two birthdays are the same, false otherwise.
*/

bool generateBirthdays() {
	std::vector<bool> birthdays;
	birthdays.resize(365);
	for (int i = 0; i < birthdays.size(); i++)
		birthdays[i] = false;
	int n = 0;
	bool sameBirthday = false;
	while (n < N && !sameBirthday) {
		int newBirthday = unif(rng);
		sameBirthday = birthdays[newBirthday];
		birthdays[newBirthday] = true;
		n++;
	}
	return sameBirthday;
}


void printRealisation() {
	int success = 0;
	for (int run = 0; run < M; run++) {
		bool sameBirthday = generateBirthdays();
		if (sameBirthday) success++;
	}
	double p = (double)success / (double)M;
	std::cout<<"P(" << N << ") = " << p <<std::endl;
}





int main()
{
	N = 5;
	M = 10000;
	IntializeRandom(0.0, 365);
	printRealisation();

	return 0;
}