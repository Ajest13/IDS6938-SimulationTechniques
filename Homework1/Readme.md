#Homework 1 : The Jello Cube (Continuous Simulation Assignment
## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

#####Alexander Almodovar

####Part 1
######(a) Solve for the exact symbolic (analytical) solution. (Hint: take the integral.)
~~~
Exact: y(x) = e^(x/2) sin(5 x) = 2.71828^(0.5 x) sin(5 x)
~~~
######(b) After step (a) you have the values for the df and exact functions. Translate the mathematical formulas you now have into the df and exact functions.

Funtions: 
~~~
df:  y - (1.0 / 2.0) * exp(x / 2.0) * sin(5.0 * x) + 5.0 * exp(x / 2.0) * cos(5.0 * x)
~~~
~~~
exact: y(x) = exp(x / 2.0)* sin(5.0 * x) = 2.71828 * exp(0.5 * x) sin(5.0 * x)
~~~
######(c) Run three numerical integration solutions: RK1, RK2, and RK4 to generate the numerical and exact values. To start use h = 0.1, for x =< 0.0, 10.0 >. (Hint: this produces 100 values for each solution.) Graph the results of RK1, RK2, and RK4 and the exact solution. (Use whatever approach you like to graph this data: R, Python, Matlab, Excel - you should produce a graph with 4 curves.)
![](images/NumericalIntegrationValues.PNG?raw=true)

######(d)Plot the error percentages for RK1, RK2, and RK4 in another graph. Remeber the error is defined as : |(exact - approx)| / exact

![](images/PercentErrorIntegration.PNG?raw=true)

######(e)Vary the step size h = n where you define three n values for 
######x =< 0.0, 10.0 >.
######Plot the results just for RK4 with 3 different n values (with the exact solution). Plot the error rate.

Stepsizes used were. n = .5; n = 1; n = 2

![](images/VaryingStepsizes.PNG?raw=true)
![](images/PercentErrorforVaryingSteps.PNG?raw=true)

######(f)Analyze your results: (1) Describe how varying the integration method changes the accuracy. (2) What happens as you increase the x value to the accuracy. (3) How does varying the step size effect the accuracy. (4) Which method is the most accurate and why (in particular explain what is taken to account in the solution).

The results show that as you increase the number of orders of integration the simulations become more accurate. This is the same result on accuracy when increasing the number of steps (decreasing step size). As you decrease the step size, the simulation becomes more accurate. RK4, also known as fourth-order Runge Kutta method, is the most accurate because the first error term is taken from the 5th derivative term versus Euler’s method (RK1)  which is taken from the 2nd derivative term. In other words, Eulers method’s error is defined as (h/2)^2 giving you ¼ of the error. On the other hand, RK4 gets the first four derivatives correct and therefore the error is defined as (h/2)^5 giving you 1/32 of the error. So as h gets smaller and the order method higher the accuracy is better.

The following chart shows the first 4 integration values for RK1, RK2, RK4, and exact. The full data shees are provided in the link below.

| RK1  | RK2 | RK4 | Exact |
| ------------- | ------------- | ------------- | ------------- |
| 0.0  | 0.0 | 0.0 | 0.0 |
| 0.5  | 0.509036927  | 0.50401476| 0.504006212 | 
| 0.98608828  | 0.941891755 | 0.929983374 | 0.929969261 | 
| 1.336761843  | 1.178280127 | 1.158938591 | 1.158923832 | 
Data sheets can be found here : [Homework 1 Data](IntegrationData.xls)

####Part 2 - Programming a Jello Cube

As hypothesized in Part 1, RK4 was the integration method that produced the best results. RK1 and RK2 required me to do some intersting things to the spring constants for the system to stabilize. I also found the need to modify the threshold values when using RK1 and RK2. Even then, the jello cube did not simulate accurately. RK4 or higher order methods are recommended for these types of collision system simulations. 

#####Spring Constants
I chose my Ks values to be very high to allow for the springs to have more "give". This allowed for the cube to squish and pull appropiately and similar to an actual cube of jello. My Kd values were set low so as to give the cube a sufficient "jiggly" look after a force had been applied. It took alot of experimentation to find the values that wouldnt destabilize the entire system but after a few tries these are the constants that worked for me:

![](images/SpringConstants.PNG?raw=true)

####Part 3 - Written Questions
######1) What is the effect of the Ks and Kd parameters on the jello?.

Ks represents the stiffness of the spring. Kd is the dampening of forces over time on those springs. Increasing stiffness shortens the stretch of the springs. As you increase dampening you increase the rate at which the spring reaches its rest length. In other words,  the higher the dampening the faster it loses the spring force and returns to its resting point.

######2)What are the benefits and the drawbacks of the collision system used here? What are some different ways in which it could be improved? .

The main drawback of the collision system here would be in the case of large scale simulations. The amount of interactions would be too large for a computer to handle and you would have to compromise some accuracy to make a working system with a reasonable number of computations.

######3)What are some example systems you could model with Mass-spring simulations? Explain how you would you construct the model.

I imediately relate Mass-spring systems to sports. Mass-spring simulations can be used to model the effect of running on different types of surfaces. This would be extremely useful in basketball to determine the best type of floor that would allow for springy-ness without giving an advantage but at the same time reducing pressure and damage to joints over a period of time.

######4)Does the jello behave realistically? What integration method did you choose to make the Jello stable?

My jello cube behaves realistically as possible using RK4 integration. This could be improved by using other, more complex or higher level, integration methods such as Verlet.

######5)How would you model and simulate water (in terms of a continuous simulation)? 
I would essentially create a collection of boxes similar to the jello cube simulation but at a much smaller scale. These boxes would affect each others velocity and density. Since water in incompressible it is slightly easier to model than other fluids. Incompressible fluids have a constant density and pressure. The mathematical model I would use are the Navier-Stokes Equations which are used to model fluid flow. 

[JelloCube Video Upload](https://youtu.be/3DZxEv-z7JM)




Something

| RK1  | RK2 | RK4 | Exact |
| ------------- | ------------- | ------------- | ------------- |
| 0.1  | 0.2 | 0.3 | 0.4 |
| 0.1  | 0.2 | 0.3 | 0.4 | 
| 0.1  | 0.2 | 0.3 | 0.4 | 
| 0.1  | 0.2 | 0.3 | 0.4 | 
