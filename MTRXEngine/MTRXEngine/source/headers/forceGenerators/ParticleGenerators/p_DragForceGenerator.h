/*
	Author: Mohamed Kazma
	Description: A drag force generator
*/

#pragma once

#include <entities/Particle.h>
#include <forceGenerators/ParticleGenerators/IParticleForceGenerator.h>

namespace mtrx
{
	class p_DragForceGenerator : public IParticleForceGenerator
	{
	public:
		float k1; // Velocity drag coefficient
		float k2; // Velocity squared drag coefficient

		virtual void UpdateForces(Particle* particle) override;
		
		p_DragForceGenerator(float k1, float k2);
		~p_DragForceGenerator();

		inline void setK1(float k1) { this->k1 = k1; }
		inline void setK2(float k2) { this->k2 = k2; }
	};
}

