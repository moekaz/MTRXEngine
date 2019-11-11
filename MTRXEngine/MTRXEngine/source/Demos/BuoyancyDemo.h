#pragma once

#include <../Demos/Demo.h>
#include <forceGenerators/RigidbodyGenerators/rb_BuoyancyForceGenerator.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>
#include <BuoyancyDemoUI.h>

class BuoyancyDemo : public Demo
{
public:
	mtrx::Rigidbody body;
	
	BuoyancyDemo();
	~BuoyancyDemo() = default;

	void Update() override;
	void InputCheck() override;
private:

};