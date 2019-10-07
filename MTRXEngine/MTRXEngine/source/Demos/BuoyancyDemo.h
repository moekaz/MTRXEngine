#pragma once

#include <../Demos/Demo.h>
#include <forceGenerators/RigidbodyGenerators/rb_BuoyancyForceGenerator.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>

class BuoyancyDemo : public Demo
{
public:
	mtrx::Rigidbody body;
	
	BuoyancyDemo();
	~BuoyancyDemo();

	void Update() override;
	void InputCheck() override;
private:

};