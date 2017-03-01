#include <nanogui/nanogui.h>
#include <iostream>
#include <random>
#include <chrono>
#include "Visualizer.h"
#include "Scene.h"
#include "particlesystem.h"


std::string mInputObjFile = "../models/tetrahedron.obj";
std::string mInputObjPath = "";

Geometry::Scene *mScene;
Geometry::ParticleSystem *mParticles;
Eigen::MatrixXf  mGeometry;
Eigen::MatrixXf  mColors;
Eigen::MatrixXf  mVelocities; 
Eigen::MatrixXf  mMasses; 
Eigen::MatrixXf  mForces; 

bool loadGeometry() {
	//Load Geometry.
	int numberOfParticles = 1;  // adjust if you want many

	std::mt19937_64 rng;
	// initialize the random number generator with time-dependent seed
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);
	// initialize a uniform distribution between 0 and 1
	std::uniform_real_distribution<double> unif(-10, 10);
	// ready to generate random numbers


	mGeometry.resize(3, numberOfParticles);
	mColors.resize(4, numberOfParticles);
	mForces.resize(3, numberOfParticles);
	mVelocities.resize(3, numberOfParticles);
	mMasses.resize(1, numberOfParticles);

	for (int i = 0; i < numberOfParticles; i++)
	{
		//mGeometry.col(i) << unif(rng) , unif(rng), 0.0f;   /// activate if you want many
		mGeometry.col(i) << 0.0, -8.0, 0.0f;     /// activate if you only want one
		mColors.col(i) << 1.0f, 1.0f, 0.0f, 1.0f;
		mMasses.col(i) << 1.0f;
		mForces.col(i) << 0.0f, 0.0f, 0.0f;
		mVelocities.col(i) << 0.0f, 10.0f, 100.0f;
	}

	
	mParticles->set_mColors(mColors);
	mParticles->set_mGeometry(mGeometry);
	mParticles->SetMasses(mMasses);
	mParticles->SetForces(mForces);
	mParticles->SetVelocities(mVelocities);
	mScene->SetParticleSystem(mParticles);

	std::cout << "LOADING Geometry ..." << std::endl;
	mScene->get_Geometry()->LoadOBJFile_Triangles(mInputObjFile.c_str(), mInputObjPath.c_str(), true, Eigen::Vector4f(0.4f, 0.4f, 0.4f, 1.0f));


	std::cout << "   There are  " << mScene->get_Geometry()->get_mGeometry().cols() << " vertices" << std::endl;
	std::cout << "   There are  " << mScene->get_Geometry()->get_mColors().cols() << " colors" << std::endl;
	std::cout << "   There are  " << mScene->get_Geometry()->get_mGeometry_indices().cols() << " indexes" << std::endl;
	std::cout << "   There are  " << mScene->get_Geometry()->get_mGeometry_indices().cols() << " triangles" << std::endl;
	std::cout << "LOADING Particles ..." << std::endl;
	std::cout << "   There are  " << numberOfParticles << " Particles" << std::endl << std::endl;

	return true;
}