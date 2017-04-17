// Environment.h: interface for the CEnvironment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ENVIRONMENT_H)
#define ENVIRONMENT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Transformation.h"

class CEnvironment  
{
public:
	void Display();
	void GenerateObstacles(int n);
	CEnvironment();
	virtual ~CEnvironment();
	
	vec2 goal;
	float groundSize;
	vec3* obstacles;
	float* colors;
	int obstaclesNum;
};

#endif // !defined(ENVIRONMENT_H)
