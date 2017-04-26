# Homework 3 : Agent based Simulation Assignment 

## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

[University of Central Florida](http://www.ist.ucf.edu/grad/)
This is the framework for homework #3. 

Using 2 grace days, New due date: **Wednesday, April 26 at 11:59PM (EST)**


# Introduction
The goal of this assignment is to enable the behavioral animation of vehicle-like walking agents. 

You will be expected to compose a *final report* which demonstrates your understanding on the material in each section of the assignment. Be visual! - Pictures say a thousand words so you do not have to. Show off your different configurations and really explore the assignment.


### Part 1: Behaviors

The goal of this assignment is to enable the steering behavioral animation of agents.

We represent an agent as a two-dimensional disk with mass (**m**) and moment-of-inertia (**I**) that is capable of generating a force **F** along body x-axis with a torque about the z-axis. For this assignment assume that the agent only translates in the world x-y plane and rotates about the body z-axis.

![](images/behavior.png?raw=true)

**(a) - 10 points** : Compute derivative vector given input and state vectors. Implement the function *SIMAgent::FindDeriv()*. This function sets derive vector to appropriate values after being called.

You will need to set deriv[0], deriv[1], deriv[2], deriv[3]. Compute derivative vector given input and state vectors. This function sets derive vector to appropriate values after being called. 

*  deriv[0] is the force in local body coordinates divided by the mass.
```deriv[0] = state[2];```

* deriv[1] is the torque in local body coordinates divided by the inertia.
```deriv[1] = state[3];```

* deriv[2] is the velocity of the agent  in local body coordinates
```deriv[2] = input[0] / Mass; ```

* deriv[3] is the angular velocity of the agent in world coordinates
```deriv[3] = input[1] / Inertia;```


You also must implement *SIMAgent::InitValues()*: Try to figure out appropriate values for control and behavior settings. You need to find out appropriate values for: *SIMAgent::Kv0, SIMAgent::Kp1, SIMAgent::Kv1, SIMAgent::KArrival, SIMAgent::KDeparture,
SIMAgent::KNoise,	SIMAgent::KWander, SIMAgent::KAvoid, SIMAgent::TAvoid, SIMAgent::RNeighborhood, SIMAgent::KSeparate, SIMAgent::KAlign, SIMAgent::KCohesion.*
```
	Kv0 = 10.0;
	Kp1 = -50.0;
	Kv1 = 10.0;
	KArrival = 0.02;
	KDeparture = 1000.0;
	KNoise = 10.0;
	KWander = 10.0;
	KAvoid = 350;
	TAvoid = .75;
	RNeighborhood = 500.0;
	KSeparate = 500.0;
	KAlign = 6.0;
	KCohesion = 6.0;
```


**(b) - 20 points**: In this part of the assignment you will need to implement 6 types of individual behaviors and 5 types of group behaviors. Create the following behaviors through appropriate computation of V<sub> d</sub>  and θ<sub>d</sub>  commands:
* Seek

```cpp
vec2 SIMAgent::Seek()
{
vec2 tmp; 			  
	tmp = goal - GPos; 
	vd = SIMAgent::MaxVelocity;

	thetad = atan2(tmp[1], tmp[0]);

	return vec2(cos(thetad)*vd, sin(thetad) * vd);
}
```

* Flee

```cpp
vec2 SIMAgent::Flee()
{
	vec2 tmp;
	
	tmp = goal - GPos;
	vd = MaxVelocity;
	
	thetad = atan2(tmp[1], tmp[0]) + M_PI;
	
	
	return vec2(cos(thetad)* vd, sin(thetad) * vd);
}
```

* Arrival

```cpp
vec2 SIMAgent::Arrival()
{
	vec2 tmp;


	tmp = goal - GPos;
	vd = tmp.Length()*KArrival;
	
	Truncate(vd, 0, MaxVelocity);
	
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);

	return vec2(cos(thetad)* vd, sin(thetad) * vd);
}
```

* Departure

```cpp
vec2 SIMAgent::Departure()
{
	vec2 tmp;


	tmp = goal - GPos; 
	vd = (KDeparture - tmp.Length()) * KArrival;
	
	Truncate(vd, 0, MaxVelocity); 
	
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]) + M_PI; 		


	return vec2(cos(thetad)* vd, sin(thetad) * vd); 
}
```

* Wander

```cpp
vec2 SIMAgent::Wander()
{
	float center = (GPos + v0).Length();
	float angle = float(rand() % 360) / 180.0 * M_PI;
	vWander[0] = cos(angle) * KWander;
	vWander[1] = sin(angle) * KWander;
	
	thetad = atan2(vWander[1], vWander[0]);
	vd = center * KNoise;
	
	return vec2((cos(thetad)*vd), (sin(thetad)*vd));
}
```

* Obstacle Avoidance

```cpp
vec2 SIMAgent::Avoid()
{
	//Ref: https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-collision-avoidance--gamedev-7777
	//Ref:http://www.futuredatalab.com/steeringbehaviors/
	
	//Normal seek movement (Can be replaced with Wandering Code)
	vec2 tmp;
	tmp = goal - GPos;
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	vd = MaxVelocity / 2;


	for (int i = 0; i < env->obstaclesNum; i++)
	{

		//convert object coordinates to vector
		vec2 obsPos;
		obsPos[1] = env->obstacles[i][1];
		obsPos[0] = env->obstacles[i][0];

		//Sight vectors for collision check
		vec2 sight = GPos + v0.Normalize() * KAvoid;
		vec2 sight2 = GPos + v0.Normalize() * KAvoid * .5;

		//Check collision
		vec2 check = (obsPos - sight);
		vec2 check2 = (obsPos - sight2);

		//Radius length additions
		float rad = env->obstacles[i][2] + radius;

		if (check.Length() <= rad + KAvoid || check2.Length() <= rad + KAvoid)
		{
			//Updating theta and vd
			thetad = thetad + TAvoid;
			vd = (rad - tmp.Length()) * rad;
			ClampAngle(thetad);

			return vec2(cos(thetad)*vd, sin(thetad)*vd);
		}
	}
	return vec2(cos(thetad)*vd, sin(thetad)*vd);
}
```

**(c) - 20 points**: Implement the functions for the following group behaviors: 
* Seperation

```cpp
vec2 SIMAgent::Separation()
{
	vec2 tmp;
	vec2 sum(0.0, 0.0);


	for (int i = 0; i < agents.size(); i++)
	{
		tmp = agents[i]->GPos - GPos;
		
		if (tmp.Length() < RNeighborhood)
		{
			tmp = goal - agents[i]->GPos;
			sum += (tmp / tmp.Length()) * KSeparate;
		}
	}
	thetad = atan2(sum[1], sum[0]);
	vd = MaxVelocity;
	
	return vec2(cos(thetad)*vd, sin(thetad)*vd);
}
```
* Cohesion

```cpp
vec2 SIMAgent::Cohesion()
{
	vec2 tmp;
	vec2 sum(0.0, 0.0);
	int neighbors = 0;

	for (int i = 0; i < agents.size(); i++) 
	{
		tmp = agents[i]->GPos - GPos;
		if (tmp.Length() < RNeighborhood) 
		{
			sum += tmp;
			neighbors++;
		}

	}

	sum = (sum / neighbors);
	tmp = goal - GPos + sum;
	vd = tmp.Length() * KAvoid;
	
	Truncate(vd, 0, MaxVelocity);

	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);

	return vec2(cos(thetad)*vd, sin(thetad)*vd);
}
```
* Alignment

```cpp
vec2 SIMAgent::Alignment()
{
	vec2 tmp;
	vec2 sum(0.0, 0.0);

	for (int i = 0; i < agents.size(); i++)
	{
		tmp = agents[i]->GPos - GPos;

		if (tmp.Length() < RNeighborhood)
		{
			sum = agents[i]->v0.Normalize();
		}
	}

	tmp = goal - GPos + sum;
	thetad = atan2(tmp[1], tmp[0]);
	vd = tmp.Length() * KAvoid;
	
	Truncate(vd, 0, MaxVelocity);
	
	return vec2(cos(thetad)*vd, sin(thetad)*vd);
}
```
* Flocking

```cpp
vec2 SIMAgent::Flocking()
{
	vec2 tmp;

	tmp = (KSeparate * Separation()) + (KAlign * Alignment()) + (KCohesion * Cohesion());

	return tmp;
}
```
* Leader Following

```cpp
vec2 SIMAgent::Leader()
{
	vec2 tmp;
	if (agents[0] == this) 
	{
		return Seek();
	}
	else
	tmp = (KSeparate * Separation()) + (KArrival * Arrival());
	
	return tmp;
}
```

# Part 2 - Simulating a simple pedestrian flow

The goal of this part of the assigment is to simulate the pedestrain flow for various configurations. Pedestrian traffic simulation is an important, sometimes required, stage for certain construction projects such as shopping centers, airports, railway stations, or stadiums. hese analyses can be used by architects in the design stage, by facilities owners contemplating changes, by city planners to evaluate rush hours, or even by civil authorities to simulate evacuations or other emergencies. 




**(a) - 20 points**: Create a maze. Generate the pdm, stats, and animations like before. Vary [parameters in your agents](https://help.anylogic.com/index.jsp?topic=/com.xj.anylogic.help/html/_PL/reference/Attributes.html) to give them different behaviors and show the pedistrians change how they navigate the maze.

My initial step was to find maze and upload the image to AnyLogic. I then began to create the boundaries(walls) of the maze using the "Wall" drawing tool within the pedestrian pallet.

After the general mapping of the maze boundaries was completed, I implemented targetLines at "dead ends" that were not imediately obvious when trying to solve the maze. These lines represnt possible target locations where the agents could arrive.

![](images/MazeWalls.PNG?raw=true)

Following the placement of the "dead ends" I created the decision logic for the agents. By default, the agents find the most direct route to the ped sink unless decision trees (pedSelectOutputs) are implemented. Most of the decisions trees (pedSelectOutputs) involve a .5 probability of the agent going to a dead end and a .5 probability of moving to the next decision tree. This is represented by the following image.

![](images/MazeLogicMapping1.PNG?raw=true)

The only time this changes is when a a specific route can lead to more than 1(one)"dead end" targetLine(Complex Route). This happens exactly twice within my maze setup with two Complex Routes having 2 seperate "dead ends" within the route. The probability tree becomes slightly more complicated at this point. I created the decision tree logic so that the agents have a .25 probability of selecting either deadend within the complex route as well as a .25 probability of selecting the folowing "dead end" after the route and a .25 probability of moving on to the subsequent decision tree. For increased realism, I made subtrees to these complex routes to allow the agents to have a probability of selecting the other dead end within the same route after the first dead end was encountered and eventually moving to the next decision on the correct route. The logic map makes the assumption that the agents are intelligent and will not select or return to a dead end they have already selected.Therefore, this simulation does not account for disorientation.

The following image shows the complete logic tree for the tringular maze with the complex route logic located at the end of the first and second row.

![](images/MazeLogic.PNG?raw=true)

The following image displays the variation parameters set on the custom agents within the simulation. These parameters are Walking Speed (velocity), Acceleration, and gender. 

![](images/MazeRunnerParameters.PNG?raw=true)

For custom agent "MazeRunner", The Velocity was set to a uniform distribution between  1.0 and 2.5 meters per second. The velocity of a walking human is 1.4 meters per second but can be as fast as 2.5 meters per second.(source: Pachi, Ikaterini, and Tianjian Ji. "Frequency and velocity of people walking." The Structural Engineer 83.3 (2005) Web. 24 Apr. 2017.)
The following image shows this being represented in the default value field.

![](images/MazeRunnerVelocity.PNG?raw=true)

The acceleration or "step frequency" is dependant of many factors including gait and height. I chose a relatively small distribution to simulate the difference in acceleration without know the height and gait of the individual agents. The acceleratioin is uniformly distributed between .68 and 1.45 as shown in the following image.

![](images/MazeRunnerAcceleration.PNG?raw=true)

The final parameter implemented was intended to pull statistics relating to the gender of the agent by assigning each agent an integer value of 0 or 1. Unfortunately I was unsuccessful in my attempts to pull statistics from customized agent parameters such as gender.

![](images/MazeRunnerGender.PNG?raw=true)

Lastly, I generated intensity(.intensity()) and pedestrian count (countPeds()) statistics over time and displayed them in a line graph as well as bar chart. The line graph is useful in displaying the decaying traffic at dead ends over time as the agents pass that part of the Logic Tree. The bar chart shows the pedestrian count at the dead ends at any given time as a percentage of the entire traffic.
The following iteration of the simulation shows that Dead End 2 was the most visited and Dead End 4 was the least visited.

![](images/MazeBarGraph.PNG?raw=true)

![](images/MAZEMapping.PNG?raw=true)

A density heatmap was implemented to the final simulation to give a visual representation of the most visited "dead ends" and routes traveled over time. 

The simulation can be viewed in 2d and 3d through the following link.

[Maze Simulation Video](https://youtu.be/XrlICHCPMYA)

**(b) - 30 points**: Model and analyze a building (or floor/outdoor space/stadium) on campus. (There is help on piazza how to find rough building plans - we expect something plausible). Create a senario: evacuation, daily office routine, special event, normal egress.... etc., and model and design your own experiment to determine if the building design suits the needs of its users. Start with photographs of your site, describe your site, describe your senario and hypothesis. Then use an agent-based pedistrian simulation to visualize your experiment's results.

![](images/CREOLphoto.PNG?raw=true)

For my experiment I chose to map out the CREOL building on UCF's main campus. This building houses the College of Optics and Photonics.

For my experiment I have chosen to simulate a firedrill to understand pedestrian flow pertaining to the use of the exits in an emergency building evacuation. This simulation is useful to pull information and statistics for risk mitigation and possible contingency plans for exits that tend to have a higher traffic density

#####The Problem

Which of the exits has the heaviest flow of traffic in the instance of a fire or firedrill. 

#####The Hypothesis

I hypothesize the main entrance will have the highest traffic flow due to its its location.

#####Simulation Setup

######Mapping

The first step in the setup process was to map out the walls using "Wall" drawing tool in the pedestrian palette. The building was then seperated in to 5 areas with attractor set within classrooms, labs, bathrooms etc. I then proceeded to mark each exit with pedFlowStatistic targetLines to pull the traffic statistics of each exit at the time of the fire drill. The last part of the mapping phase was to draw safe zone areas outside of the building as target locations for the agents during the fire drill.

![](images/CREOLMapping.PNG?raw=true)

######Logic Diagram

![](images/CREOLLogicmap.PNG?raw=true)

The logic map starts with pedestrians having an equal probability(.2) of choosing 1 of the 5 building areas and then moving toward any of the implemented attactors within that area. At this point the are place in a pedestrian wait until the "FireDrill" event releases them. The following image displays the parameters of the FireDrill which is ran after 20 min allowing for students to be situated in there destination.

![](images/CREOLFireDrillParameters.PNG?raw=true)

After the release of the students (FireDrill implementation), they are given a 1/3 probability of selecting 1 safezone of the 3 nearest to them located outside of the building. This eventually leads to a pedestrian sink so that in the case of a real emergency they cannot reenter the building.
######Statistics
The traffic statistics are were visualized using a bar chart and a time plot. The time plot shows the flow of traffic through each exit over time as the fire drill comences. The bar chart represents the percentage of students that used each exit to reach their safe zone area goal. Lastly, a density heatmap  was implented to show the agent density throughout the simulation.
The following image is a representation of the exit traffic percentages.

![](images/CREOLStatistics.PNG?raw=true)

######Conclusion

After running the simulation I have to reject my hypothesis. The most populated building exit was not the main entrance but rather Exit 4 which is located in the opposite corner. This tends to be where the majority of classrooms are located. The reason for this could also be due to its proximity to two of the safezones which were assigned to it.

The following is a link to the running simulation video in 2d and 3d.

[UCF CREOL Building Fire Drill Simulation](https://youtu.be/TufNjkZB6Zg)

References:
(1) Piazza Forum
(2) Webcourses
(3)https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-collision-avoidance--gamedev-7777
(4) http://www.futuredatalab.com/steeringbehaviors/
(5)Spoke with multiple students in the class including but not limited to Charlie, Roberto, Mac, and Corey

