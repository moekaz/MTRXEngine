#pragma once

#include <../Demos/Demo.h>

class FluidSimulationDemo : public Demo
{
public:
	
	FluidSimulationDemo();
	~FluidSimulationDemo() = default;

	virtual void Update() override;
	virtual void InputCheck() override;
};

