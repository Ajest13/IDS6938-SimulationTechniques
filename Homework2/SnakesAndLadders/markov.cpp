#include "markov.h"


//Markov simulation functions

std::vector<int> DTMC (Eigen::MatrixXf trans, int steps, int start){
  //random generator
  std::random_device rd;
  std::mt19937 gen(rd());
  //initialize state vector
  std::vector<int> myVec(steps+1);
  myVec[0] = start;
  //initialize counter variables
  int count;
  double sum;
  double U;

  //for each step, simulate the next step from the current state row
  for(int i=0; i<steps; i++){
    count = 0;
    sum = 0;
    U = std::generate_canonical<double,10>(gen);
    while(sum < U){
      sum += trans(myVec[i], count);
      if(sum > U){
        myVec[i+1] = count;
      }
      count++;
    }
  }
  return myVec;
}


