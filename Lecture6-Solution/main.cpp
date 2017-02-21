//Eulers Method to solve a differential equation
#define _USE_MATH_DEFINES

#include <cmath>
#include<iostream>
#include<iomanip>
#include<math.h>
#include <string>
#include <sstream>

/*
Compute the dy/dx
*/
double df(double x, double y)            //function for defining dy/dx
{
    return y - (1.0 / 2.0)*exp(x / 2.0)*sin(5.0 * x) + 5.0 * exp(x / 2.0)*cos(5.0 * x);
}


/*
Compute the exact answer
*/
double exact(double x)            //function for defining dy/dx
{
    return exp(x / 2.0)*sin(5.0 * x);
}


/*
Calculate the error
*/
double error(double exact, double approx)
{
    return abs(exact - approx) / exact;
}


/*
This implements the Euler method equation
*/
double rk1(double y, double h, double x)
{
    return y + h * df(x, y);
}


/*
This implements the Midpoint method equation
*/
double rk2(double y, double h, double x)
{
	double k1 = df(x, y);
	double h_half = h / 2.0;
    return  y + h * df( x + h_half, y + (h_half * k1) );
}


/*
This implements the RK4 method equation
*/
double rk4(double y, double h, double x)
{
	double h_half = h/2.0;
	double k1 = df(x, y);
	double k2 = df(x+ h_half, y + (h_half * k1));
	double k3 = df(x + h_half, y + (h_half * k2));;
	double k4 = df(x + h, y + (h * k3));;
    return  y + h * (1.0 / 6.0)*(k1 + 2.0 * k2 + 2.0 * k3 + k4);
}



std::string toString(double x, double y_euler, double y_midpoint, double y_RK4, double y_exact, double presision)
{
	
	std::ostringstream out;
	out << std::setprecision(2) << x << "\t";
	out << std::setprecision(presision) << y_euler << "\t";
	out << std::setprecision(presision) << y_midpoint << "\t";
	out << std::setprecision(presision) << y_RK4 << "\t";
	out << std::setprecision(presision) << y_exact << "\t";
	out << std::setprecision(3) << error(exact(x), y_midpoint) << "%\t";
	out << std::setprecision(3) << error(exact(x), y_RK4)<<"%";
	out << std::setprecision(3) << error(exact(x), y_euler) << "%\t";
	
	return   out.str();
}




int main()
{

    double y_euler = 0.00;
	double y_midpoint = 0.00;
	double y_RK4 = 0.00;
    double x = 0.00;
	double xb = 10.00;   // addition
	double h = .1;

	int range = (xb - x) / h;  //addition

	std::cout << std::fixed << std::showpoint;
    // Header information for column printouts
	std::cout << "x" << "\t" << "y (Euler)" << "\t" << "y (midpoint)" << "\t" << "y (RK44)" << "\t"
		<< "EXACT" << "\t\t" << "%Err(E)" << "\t\t" << "%Err(M)" << "\t\t" << "%Err(RK4)" << std::endl;
	std::cout << "----" << "\t" << "----------" << "\t" << "----------" << "\t" << "----------"
		<< "\t" << "----------" << "\t" << "-------"<<"\t\t" << "-------" << "\t\t" << "------" << std::endl;

	//intial values
	std::cout<< toString(x, y_euler, y_midpoint, y_RK4, exact(x), 10) << std::endl;

    for (int i = 0; i < range; i++)
    {
		y_euler = rk1(y_euler,h,x);  //caculate y_{i+1}
		y_midpoint = rk2(y_midpoint, h, x);  //caculate y_{i+1}
		y_RK4 = rk4(y_RK4, h, x);  //caculate y_{i+1}
        x = x + h;       //increment x

		std::cout << toString(x, y_euler, y_midpoint, y_RK4, exact(x), 10) << std::endl;
	}


    return 0;
}