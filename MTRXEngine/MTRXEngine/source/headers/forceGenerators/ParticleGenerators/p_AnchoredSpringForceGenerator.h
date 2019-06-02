/*
	Author: Mohamed Kazma
	Description: A spring force generator that uses anchor points to generate the forces
	This can either be the center of a particle or just some fixed anchor its the same calculation
*/

#pragma once

#include <entities/Particle.h>
#include <forceGenerators/ParticleGenerators/IParticleForceGenerator.h>
#include <Defs.h>

namespace mtrx
{
	class p_AnchoredSpringForceGenerator : public IParticleForceGenerator
	{
	public:
		glm::vec3* anchorPoint;
		SpringData spring;

		virtual void UpdateForces(Particle* particle) override;

		p_AnchoredSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength);
		~p_AnchoredSpringForceGenerator();

		inline void SetAnchorPoint(glm::vec3* point) { anchorPoint = point; }
	};
}

