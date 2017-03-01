#Homework 1 : The Jello Cube (Continuous Simulation Assignment
## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

####Alexander Almodovar

#####Extra Features:
--(5 points) Support collisions with other shapes, such as an inclined plane, cubes, and spheres
(Implement JelloMesh::CubeCollision() , Implement JelloMesh::SphereCollision()). Make a
new, interesting scene. 
######Implemented spherical object ```JelloMesh::SphereCollision()```


--(5 points) Create a movie of your jello cube environment, upload the video to youtube and
link it in your assignment writeup.
######A video of the simulaion running in different evironments is linked at the bottom of this document.

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

The results show that as you increase the number of orders of integration the simulations become more accurate. This is the same result on accuracy when increasing the number of steps (decreasing step size). In other words, as you decrease the step size, the simulation becomes more accurate. RK4, also known as fourth-order Runge Kutta method, is the most accurate integration method because the first error term is taken from the 5th derivative term versus Euler’s method (RK1)  which is taken from the 2nd derivative term. In other words, Eulers method’s error is defined as (h/2)^2 giving you ¼ of the error. On the other hand, RK4 gets the first four derivatives correct and therefore the error is defined as (h/2)^5 giving you 1/32 of the error. So as h gets smaller and the order method gets higher the simulation becomes more accurate.

The following chart shows the first 4 integration values for RK1, RK2, RK4, and exact. The full data sheets are provided in the link below.

| RK1  | RK2 | RK4 | Exact |
| ------------- | ------------- | ------------- | ------------- |
| 0.0  | 0.0 | 0.0 | 0.0 |
| 0.5  | 0.509036927  | 0.50401476| 0.504006212 | 
| 0.98608828  | 0.941891755 | 0.929983374 | 0.929969261 | 
| 1.336761843  | 1.178280127 | 1.158938591 | 1.158923832 | 
Data sheets can be found here : [Homework 1 Data](IntegrationData.xls)

####Part 2 - Programming a Jello Cube

As hypothesized in Part 1, RK4 was the integration method that produced the best results. RK1 and RK2 required me to do some intersting things to the spring constants for the system to stabilize. I also found the need to modify the threshold values when using RK1 and RK2. Even then, the jello cube did not simulate accurately. RK4 or higher order methods are recommended for these types of collision system simulations. 

#####Particle forces
After updating ```JelloMesh::EulerIntegration()``` and ```JelloMesh::MidpointIntegration()``` I began to implement additional forces to the particles besides gravity. The following is the is the block of code used to implement spring forces within ```JelloMesh::ComputeForces(ParticleGrid& grid)```
```cpp
 for(unsigned int i = 0; i < m_vsprings.size(); i++)
    {
        Spring& spring = m_vsprings[i];
        Particle& a = GetParticle(grid, spring.m_p1);
        Particle& b = GetParticle(grid, spring.m_p2);
		
		vec3 pdiff = a.position - b.position;
		vec3 vdiff = b.velocity - a.velocity;
		double dist = pdiff.Length();

		vec3 force = a.force + b.force;
		
		if (dist != 0) {
			force = -(spring.m_Ks *(dist - spring.m_restLen) + spring.m_Kd * ((vdiff * pdiff)/dist)) * (pdiff/dist);
			a.force += force;
			b.force += -force;
		}
```
######Spring Constants
I chose my Ks values to be very high to allow for the springs to have the proper "give". This allowed for the cube to squish and pull appropiately and similar to an actual cube of jello. My Kd values were set low so as to give the cube a sufficient "jiggly" look after a force had been applied. It took alot of experimentation to find the values that wouldnt destabilize the entire system but after a few tries these are the constants that worked for me:
```cpp
double JelloMesh::g_structuralKs = 2800.0; 
double JelloMesh::g_structuralKd = 6.0; 
double JelloMesh::g_attachmentKs = 2000;
double JelloMesh::g_attachmentKd = 6.0;
double JelloMesh::g_shearKs = 2500.0;
double JelloMesh::g_shearKd = 5.0;
double JelloMesh::g_bendKs = 2500.0;
double JelloMesh::g_bendKd = 6.0;
double JelloMesh::g_penaltyKs = 100000.0;
double JelloMesh::g_penaltyKd = 6.0;
```
#####Collision Detection and Response
The particles needed to be tested for collisions and contact. For ```JelloMesh::FloorCollision()```a threshold was created under the collisions block to detect the particles moving towards the object before contact. My collision delta in this case is 0.05. 
To check against cylinders I used ```vec3 normal = p.position - point``` to account for the position of the particles at a certain time which I defined as:
```cpp
vec3 cylinderAxis = cylinderEnd - cylinderStart;
vec3 cylinderDiff = cylinderStart - p.position;
double time = -(cylinderDiff * cylinderAxis)/(cylinderAxis.Length()*cylinderAxis.Length());
vec3 point = cylinderStart + time * cylinderAxis;
```
Likewise, I applied a check for spheres after modifying ground.xml, jelloMesh.h and jelloMesh.cpp to include spheres when checking for collisions.
```cpp
	vec3 ptMid = sphere->pos;
	vec3 normal = p.position - ptMid;
```
Below is the final code implementing ```JelloMesh::FloorIntersection```,```JelloMesh::CylinderIntersection```and```JelloMesh::SphereIntersection```
```cpp
bool JelloMesh::FloorIntersection(Particle& p, Intersection& intersection)
{
	if (p.position.n[1] <= 0.0)
	{
		intersection.m_p = p.index;
		intersection.m_distance = -p.position[1];
		intersection.m_type = CONTACT;   
		intersection.m_normal = vec3(0.0, 1.0, 0.0);
		return true;
	}
	else if (p.position[1] < 0.0 + 0.05)
	{
		intersection.m_p = p.index;
		intersection.m_distance = 0.05 - p.position[1];
		intersection.m_type = COLLISION;
		intersection.m_normal = vec3(0.0, 1.0, 0.0);
		return true;
	}
	else
		return false;
}

bool JelloMesh::CylinderIntersection(Particle& p, World::Cylinder* cylinder, JelloMesh::Intersection& result)

{
    vec3 cylinderStart = cylinder->start;
    vec3 cylinderEnd = cylinder->end;
    vec3 cylinderAxis = cylinderEnd - cylinderStart;
	vec3 cylinderDiff = cylinderStart - p.position;
	double time = -(cylinderDiff * cylinderAxis)/(cylinderAxis.Length()*cylinderAxis.Length());
	double cylinderRadius = cylinder->r;
	vec3 point = cylinderStart + time * cylinderAxis;
	vec3 normal = p.position - point;
	double dist = normal.Length();
	normal = normal.Normalize();
	

	if (dist < cylinderRadius)
	{
		result.m_p = p.index;
		result.m_distance = cylinderRadius - dist;
		result.m_type = CONTACT;
		result.m_normal = normal.Normalize();
		return true;
	}

	else if (dist < cylinderRadius)
	{
		result.m_p = p.index;
		result.m_distance = dist - cylinderRadius;
		result.m_type = COLLISION;
		result.m_normal = normal.Normalize();
		return true;
	}
	return false;
}

bool JelloMesh::SphereIntersection(Particle& p, World::Sphere* sphere,
							JelloMesh::Intersection& result)
{
	vec3 ptMid = sphere->pos;
	double sphereRadius = sphere->r;
	vec3 normal = p.position - ptMid;
	double dist = normal.Length();

	if (dist < sphereRadius)
	{
		result.m_distance = sphereRadius - dist;
		result.m_p = p.index;
		result.m_normal = normal.Normalize();
		result.m_type = CONTACT;
		return true;

	}
	if (dist < sphereRadius)
	{
		result.m_distance = dist - sphereRadius;
		result.m_p = p.index;
		result.m_normal = normal.Normalize();
		result.m_type = COLLISION;
		return true;

	}
	return false;
}
```
Moving onto collision and penetration response you can see that the system calls for ```JelloMesh::ResolveCollisions(ParticleGrid& grid)``` to be when the particles are close but not inside the object. This allows for a change in velocity to be applied to the particles. Penetration represents a particle moving into an object. This is found in ```JelloMesh::ResolveContacts(ParticleGrid& grid)```. In this case, a stiff spring force is applied onto the particles outwards from the surface of the object.
```cpp
void JelloMesh::ResolveContacts(ParticleGrid& grid)
{
    for (unsigned int i = 0; i < m_vcontacts.size(); i++)
    {
       const Intersection& contact = m_vcontacts[i];
       Particle& p = GetParticle(grid, contact.m_p);
	   double dist = contact.m_distance;
	   vec3 normal = contact.m_normal; 
	   vec3 diff = -dist * normal;

	   p.force = g_penaltyKs * (dist * normal) + g_penaltyKd * (diff/dist);
    } 
}

void JelloMesh::ResolveCollisions(ParticleGrid& grid)
{
    for(unsigned int i = 0; i < m_vcollisions.size(); i++)
    {
        Intersection result = m_vcollisions[i];
        Particle& pt = GetParticle(grid, result.m_p);
        vec3 normal = result.m_normal;
        float dist = result.m_distance;
		double r = 0.75;

		//pt.position += dist * normal;
	pt.velocity += pt.velocity - 2 * (pt.velocity * normal) * normal * r;
	}
}
```
##### Extra Springs
Lastly, I applied shear and bend springs to the particles to give the cube the realism of "Jello". I had a little fun with it set my shear and bend springs in a manner that my my jello cube extra "jiggly". (The particles were already initiated as part of the given framwork)
```cpp
	ParticleGrid& g = m_vparticles;
 //Shear Springs   
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				if (j < m_cols && i < m_rows) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j + 1, k));
				if (j > 0 && i < m_rows) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j - 1, k));				
				
				if (j < m_cols && k < m_stacks) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 1, k + 1));
				if (j > 0 && k < m_stacks) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i, j - 1, k + 1));
				
				if (i < m_rows && k < m_stacks) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j, k + 1));
				if (i > 0 && k < m_stacks) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i - 1, j, k + 1));
			}
		}
	}

// Bend Springs
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
			if (i < m_rows - 3) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i + 4, j, k));
			if (j < m_cols - 3) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 4, k));
			if (k < m_stacks - 3) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 4));
			}
		}
	}
```
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
I would essentially create a collection of boxes similar to the jello cube simulation but at a much smaller scale. These boxes would affect each others velocity and density. Since water in incompressible it is slightly easier to model than other fluids. Incompressible fluids have a constant density and pressure. The mathematical model I would use incorporate the Navier-Stokes Equations which are used to model fluid flow. 

[JelloCube Simulation Video](https://youtu.be/yh3nWMel7ts)


