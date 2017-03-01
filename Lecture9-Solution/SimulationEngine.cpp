#include "SimulationEngine.h"


Simulator::SimulationEngine::SimulationEngine() { }
Simulator::SimulationEngine::~SimulationEngine() { }


void Simulator::SimulationEngine::intialize(Geometry::Scene *pScene)
{
	mScene = pScene;
}

void Simulator::SimulationEngine::update()
{  UnaryForces(); 
Integrate_RK1(0.0007);
}

void Simulator::SimulationEngine::UnaryForces()
{
	Eigen::Vector3f new_force;

	for (int i=0; i< mScene->GetParticleSystem()->get_mGeometry().cols();i++)
	{

new_force = mScene->GetParticleSystem()->GetForces().col(i);
new_force(2) = new_force(2) - 9.8;

mScene->GetParticleSystem()->UpdateForceAtCol(i, new_force);
	}

}

void Simulator::SimulationEngine::Integrate_RK1(float h)
{
	Eigen::Vector3f new_pos;
	Eigen::Vector3f new_vel;

	Eigen::Vector3f force;
	float mass;

	for (unsigned int i = 0; i < mScene->GetParticleSystem()->get_mGeometry().cols(); i++)
	{
		new_pos = mScene->GetParticleSystem()->get_mGeometry().col(i);
		new_vel = mScene->GetParticleSystem()->GetVelocities().col(i);
		force = mScene->GetParticleSystem()->GetForces().col(i);
		mass = mScene->GetParticleSystem()->GetMasses().col(i)(0);

		if (new_pos(2) > -0.001f)
		{

			new_pos = new_pos + new_vel * h;
			new_vel = new_vel + (force / mass) * h;



			mScene->GetParticleSystem()->UpdatePositionAtCol(i, new_pos);
			mScene->GetParticleSystem()->UpdateVelocityAtCol(i, new_vel);
		}
		



	}
	



}