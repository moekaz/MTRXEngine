/*
	Author: Mohamed Kazma
	Description: A drag force generator
*/

#pragma once

#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>

namespace mtrx
{
	class rb_DragForceGenerator : public IRigidbodyForceGenerator
	{
	public:
		float k1; // Velocity drag coefficient
		float k2; // Velocity squared drag coefficient

		// Implementation of drag forces on a particle
		virtual void UpdateForces(Rigidbody* rb, float deltaTime) override;
		
		rb_DragForceGenerator(float k1, float k2);
		~rb_DragForceGenerator();

		inline void setK1(float k1) { this->k1 = k1; }
		inline void setK2(float k2) { this->k2 = k2; }
	};
}

