// Simulation.h: interface for the CSimulation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SIMULATION_H)
#define SIMULATION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Agent.h"
#include "Environment.h"

class CSimulation  
{
public:
	void SetV0();
	void Display();
	void SimulationStep(float deltaT);
	void CreateAgents(int num);
	void SetGoal(vec2& goal);
	CSimulation();
	virtual ~CSimulation();

	CEnvironment env;
	int type;
};

#endif // !defined(SIMULATION_H)
