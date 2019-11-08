#pragma once

#include <../Demos/Demo.h>
#include <math/Transform.h>
#include <colliders/Collider.h>
#include <colliders/SphereCollider.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>

struct particle
{
	float density;
	float pressure;
	mtrx::Rigidbody* rb;

	particle(float density, float pressure, mtrx::Rigidbody* body) : density(density), pressure(pressure), rb(body) 
	{}
};

class FluidSimulationDemo : public Demo
{
public:
	bool startSim;
	std::vector<particle*> particles;
	std::vector<mtrx::Collider*> colliders;
	int numParticles;

	FluidSimulationDemo();
	~FluidSimulationDemo() = default;

	void UpdateParticles();
	void ApplyDensity();
	void ApplyForces();
	void UpdatePositions();
	void RemoveStuckParticles();
	void UpdateGrid();
	void UpdateNeighbors(); // Currently do not use that
	void UpdateObstacleVelocity(); // Not sure about this
	void CollisionPositionCorrection(particle* p); 
	
	void PrintPositions();
	
	double calculateTimeStep();

	glm::vec3 BarrierCollisionCorrection(particle* p);


	inline double evaluateSpeedOfSoundSquared(particle* sp) 
	{
		if (sp->density < 0.00001) 
			return 0.0;
		
		float ratioOfSpecificHeats = 1.0f;
		return ratioOfSpecificHeats * (sp->pressure) / sp->density;
	}

	// linear interpolation with t in [0,1]
	inline float lerp(float x1, float x2, float t) 
	{
		return x1 + t * (x2 - x1);
	}

	virtual void Update() override;
	virtual void InputCheck() override;
};

