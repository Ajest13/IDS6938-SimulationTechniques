// Simulation.cpp: implementation of the CSimulation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Behavior.h"
#include "Simulation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimulation::CSimulation()
{
	env.goal = vec2(0.0, 0.0);
	SIMAgent::InitValues();
}

CSimulation::~CSimulation()
{
	SIMAgent::ClearAgents();
}

void CSimulation::SetGoal(vec2 &goal)
{
	env.goal = goal;
	if (type == WANDER)
		SetV0();
}

void CSimulation::CreateAgents(int num)
{
	SIMAgent* tmp;
	SIMAgent::ClearAgents();
	float color[3];
	float pos[2];
	float angle;
	for (int i = 0; i < num; i++){
		color[0] = float(rand() % 250) / 255.0;
		color[1] = float(rand() % 250) / 255.0;
		color[2] = float(rand() % 250) / 250.0;
		tmp = new SIMAgent(color, &env);
		pos[0] = float(rand() % int(env.groundSize * 2) - env.groundSize);
		pos[1] = float(rand() % int(env.groundSize * 2) - env.groundSize);
		angle = float(rand() % 360 - 180) / 180.0 * M_PI;
		tmp->SetInitState(pos, angle);
	}
}

void CSimulation::SimulationStep(float deltaT)
{
	//Sense:
	int s = SIMAgent::agents.size();
	int i;
	for (i = 0; i < s; i++){
		SIMAgent::agents[i]->Sense(type);
	}

	//Control:
	for (i = 0; i < s; i++){
		SIMAgent::agents[i]->Control();
	}

	//Act:
	for (i = 0; i < s; i++){
		SIMAgent::agents[i]->Act(deltaT);
	}

	//Adjust Positions
	//vec2 distVect;
	//float dist;
	//int j;
	//for (i = 0; i < SIMAgent::agents.size(); i++){
	//	for (j = i + 1; j < SIMAgent::agents.size(); j++){
	//		distVect = SIMAgent::agents[j]->GPos - SIMAgent::agents[i]->GPos;
	//		dist = distVect.Length();
	//		if (dist < CAgent::radius * 2){
	//			SIMAgent::agents[i]->GPos = SIMAgent::agents[i]->GPos + 0.5 * distVect - SIMAgent::radius * distVect / dist;
	//			SIMAgent::agents[j]->GPos = SIMAgent::agents[j]->GPos + 0.5 * distVect + SIMAgent::radius * distVect / dist;
	//		}
	//	}
	//}
}

void CSimulation::Display()
{
	if (type == AVOID)
		env.Display();	
	for(unsigned int i = 0; i < SIMAgent::agents.size(); i++){
		SIMAgent::agents[i]->Display();
	}
}

void CSimulation::SetV0()
{
	for (unsigned int i = 0; i < SIMAgent::agents.size(); i++){
		SIMAgent::agents[i]->SetV0();
	}
}
