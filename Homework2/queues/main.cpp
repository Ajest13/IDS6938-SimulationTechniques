/*
  A simple program that simulates 5 MM1 queues at an airport. The first queue
  feeds 3 other queues that work in parallel. These feed a final queue.
  Simulation runs until error below threshold and, at the end,
  a performance evaluation report is shown, and logs are generated
  for plotting and analysis.
*/

using namespace std;

#include <random>
#include "customer.h"
#include "mm1_queue.h"


std::random_device rd;

void pause()
{
 std::string sInputString;
 // Wait for input from stdin (the keyboard)
 cout << "Continue (y)?";
 std::cin >> sInputString;
}



int main(int argc, char* argv[])
{
   int next = 0;
//   test_random_number_generator();

   for (int cur_lambda = 3; cur_lambda < 34; cur_lambda++)
   {
      
	   //TODO Create MM1_Queue objects to capture the airport senario.

	   //************************************************************


   for (; 
		//TODO: add is_within_error_range check
       ;)
   {
	   Customer cust  ;    // =  TODO: process next event;
	   Customer cust2  ;   // =  TODO: process next event;
	   Customer cust3  ;   // =  TODO: process next event;
	   Customer cust4  ;   // =  TODO: process next event;
	   //TODO: one more process_next_event for the last object.

       if (cust.get_type() == Customer::COMPLETED())
       {
          switch(next)
          {
            case 0:
				//TODO add_external_arrival() for your security gates;
                 break;
            case 1:
				//TODO add_external_arrival() for your security gates;
                 break;
            case 2:
                //TODO add_external_arrival() for your security gates;
                 break;
          }
          next++;
          if (next%3==0) next = 0;
       }
       if (cust2.get_type() == Customer::COMPLETED() || cust3.get_type() == Customer::COMPLETED() || cust4.get_type() == Customer::COMPLETED())
       {
		   //TODO add_external_arrival(); on your final boarding MM1_Queue object
       }
   }



   //TODO Output statistics airport senario.



   //**************************************************************************



   }

   return(0);
}

