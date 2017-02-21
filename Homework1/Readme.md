#Homework 1 : The Jello Cube (Continuous Simulation Assignment
## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

#####Alexander Almodovar

######(a) Solve for the exact symbolic (analytical) solution. (Hint: take the integral.)

Exact: y(x) = e^(x/2) sin(5 x)

######(b) After step (a) you have the values for the df and exact functions. Translate the mathematical formulas you now have into the df and exact functions.

Funtions: 

df:  y - (1.0 / 2.0) * exp(x / 2.0) * sin(5.0 * x) + 5.0 * exp(x / 2.0) * cos(5.0 * x)

exact:  exp(x / 2.0)* sin(5.0 * x)

######(c) Run three numerical integration solutions: RK1, RK2, and RK4 to generate the numerical and exact values. To start use h = 0.1, for x =< 0.0, 10.0 >. (Hint: this produces 100 values for each solution.) Graph the results of RK1, RK2, and RK4 and the exact solution. (Use whatever approach you like to graph this data: R, Python, Matlab, Excel - you should produce a graph with 4 curves.)
![](images/NumericalIntegrationValues.png?raw=true)

######(d)Plot the error percentages for RK1, RK2, and RK4 in another graph. Remeber the error is defined as : |(exact - approx)| / exact

![](images/PercentErrorIntegration.png?raw=true)

######(e)Vary the step size h = n where you define three n values for 
######x =< 0.0, 10.0 >.
######Plot the results just for RK4 with 3 different n values (with the exact solution). Plot the error rate.

Stepsizes used were. n = .5; n = 1; n = 2

![](images/VaryingStepsizes.png?raw=true)
![](images/PercentErrorforVaryingSteps.png?raw=true)

######(f)Analyze your results: (1) Describe how varying the integration method changes the accuracy. (2) What happens as you increase the x value to the accuracy. (3) How does varying the step size effect the accuracy. (4) Which method is the most accurate and why (in particular explain what is taken to account in the solution).

The results show that as you increase the number of orders of integration the simulations become more accurate. This is the same result on accuracy when increasing the number of steps sizes (decreasing step size). As you decrease the step size, the simulation becomes more accurate. RK4, also known as fourth-order Runge Kutta method, is the most accurate because the first error term is taken from the 5th derivative term versus Euler’s method (RK1)  which is taken from the 2nd derivative term. In other words, Eulers method’s error is defined as (h/2)^2 giving you ¼ of the error. On the other hand, RK4 gets the first four derivatives correct and therefore the error is defined as (h/2)^5 giving you 1/32 of the error. So as h gets smaller and the order method higher the accuracy is better.

Data sheets can be found here : [Homework 1 Data](IntegrationData.xls)

This is the framework for homework #1. Please first read the [homework writeup](HomeWork%231.pdf).

The assignment is due: Monday, February 27 at 11:59PM (EST)

| undeformed jello  | deformed jello |
| ------------- | ------------- |
| ![](images/undeformed3.png?raw=true)  | ![](images/deformed3.png?raw=true) |

