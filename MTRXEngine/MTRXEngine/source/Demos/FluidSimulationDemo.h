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
	bool isHalfTimeStepVelocityInitialized = false;
	glm::vec3 velocityAtHalfTimeStep;

	particle(float density, float pressure, mtrx::Rigidbody* body) : density(density), pressure(pressure), rb(body) 
	{}
};

class FluidSimulationDemo : public Demo
{
public:
	std::vector<particle*> particles;
	std::vector<mtrx::Collider*> colliders;

	FluidSimulationDemo();
	~FluidSimulationDemo();

	void UpdateParticles();
	void ApplyDensity();
	void ApplyForces();
	void UpdatePositions(float dt);
	void CollisionPositionCorrection(particle* p); 
	
	void PrintPositions();
	
	double calculateTimeStep();

	glm::vec3 BarrierCollisionCorrection(particle* p);


	inline float evaluateSpeedOfSoundSquared(particle* sp) 
	{
		if (sp->density < 0.00001f) 
			return 0.0f;
		
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

