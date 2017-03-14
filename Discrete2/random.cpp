#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <functional> 
#include <numeric>     

int main()
{
	// Get a random seed
	
	//use a random device
	std::random_device rd;

	// 1) Change random number generators
	std::mt19937_64 engine(rd());
	//std::knuth_b engine(rd());
	//std::minstd_rand engine(rd());
	//std::ranlux48 engine(rd());


	// Another seed intialization routine (this is just here for future reference for you.)
	// initialize the random number generator with time-dependent seed
	//uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	//std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	//std::mt19937_64 e2;
	//e2.seed(ss);

	

	//  2) - Change distribution types
	std::uniform_real_distribution<> dist(0, 100);  // example of a uniform distribution
	//std::normal_distribution<> dist(50,10);    // example of a normal distribution


	auto generator = std::bind(dist, engine);

	// 3) Play with N
	unsigned int N = 100000;  // number of values generated
	double randomValue;
	std::map<int, int> hist; //Counts of discrete values
	std::vector<double> raw; //raw random values 


	for (unsigned int i = 0; i < N; ++i) {
		randomValue = generator();
		
		++hist[std::round(randomValue)]; // count the values
		raw.push_back(randomValue);  //push the raw values
	}

	for (auto p : hist) {
		
		// Uncomment if you want to see the values
		//std::cout << std::fixed << std::setprecision(1) << std::setw(2)
		//	<< p.first << " -  "<< p.second << std::endl;

		std::cout << std::fixed << std::setprecision(1) << std::setw(2)
			<< p.first << "  " << std::string(p.second / (N/500), '*') << std::endl;

	}


	// Print Results to File
	std::ofstream myfile;
	myfile.open("histogram_results.txt");
	for (auto p : hist) {
		myfile << std::fixed << std::setprecision(1) << std::setw(2)
			<< p.first << "\t" << p.second  << std::endl;
	}
	myfile.close();

	myfile.open("raw_results.txt");
	for (auto p : raw) {
		myfile << std::fixed << std::setprecision(5) << std::setw(2)
			<< p << std::endl;
	}
	myfile.close();


	//if you choose to write useful stats here
	myfile.open("useful_stats.txt");
	double sum = std::accumulate(raw.begin(), raw.end(), 0.0);
	double mean = sum / raw.size();
	myfile << "mean: " << mean << std::endl;
	std::cout << "mean: " << mean << std::endl;

	std::vector<double> diff(raw.size());
	std::transform(raw.begin(), raw.end(), diff.begin(),
	std::bind2nd(std::minus<double>(), mean));
	double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
	double stdev = std::sqrt(sq_sum / raw.size());
	myfile << "stdev: " << stdev << std::endl;
	std::cout << "stdev: " << stdev << std::endl;
	
	myfile.close();

}