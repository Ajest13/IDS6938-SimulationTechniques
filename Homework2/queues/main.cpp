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

	  for (;
		   !Checkin.is_within_error_range(0.002) ||
		   !Officer1.is_within_error_range(0.002) ||
		   !Officer2.is_within_error_range(0.002) ||
		   !Officer3.is_within_error_range(0.002) //||
		   ;)	   //TODO: add is_within_error_range check
/*
		Checkin.is_within_confidence_interval();//Double check to see if this is right
	   Officer1.is_within_confidence_interval();
	   Officer2.is_within_confidence_interval();
	   Officer3.is_within_confidence_interval();
	  // Boarding.is_within_confidence_interval();
	  */
   {
		   Customer cust = Checkin.process_next_event();    //  TODO: process next event;
		   Customer cust2 = Officer1.process_next_event();   //  TODO: process next event;
		   Customer cust3 = Officer2.process_next_event();   //  TODO: process next event;
		   Customer cust4 = Officer3.process_next_event();   //  TODO: process next event;
		   Customer cust5 = Boarding.process_next_event();	// boarding customer
	   //TODO: one more process_next_event for the last object.
	          
	if (cust.get_type() == Customer::COMPLETED())
       {
          switch(next)
          {
            case 0:
				//TODO add_external_arrival() for your security gates;
				Officer1.add_external_arrival();
				break;
            case 1:
				//TODO add_external_arrival() for your security gates;
				Officer2.add_external_arrival();
				break;
            case 2:
                //TODO add_external_arrival() for your security gates;
				Officer3.add_external_arrival();
				break;
          }
          next++;
          if (next%3==0) next = 0;
       }
       if (cust2.get_type() == Customer::COMPLETED() || cust3.get_type() == Customer::COMPLETED() || cust4.get_type() == Customer::COMPLETED())
       {
		   //TODO add_external_arrival(); on your final boarding MM1_Queue object
		   Boarding.add_external_arrival();

       }
   }



   //TODO Output statistics airport senario. 
	  Checkin.output(); std::cout << "*****" << endl;
	   Officer1.output(); std::cout << "*****" << endl;
	   Officer2.output(); std::cout << "*****" << endl;
	   Officer3.output(); std::cout << "*****" << endl;
	   Boarding.output(); std::cout << "*****" << endl;
	   Checkin.plot_results_output();
	Checkin.get_current_time();
	Checkin.plot_results_output();

   //**************************************************************************



   }

   return(0);
}

