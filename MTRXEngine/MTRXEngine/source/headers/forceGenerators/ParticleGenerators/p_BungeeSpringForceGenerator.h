#pragma once

#include <entities/Particle.h>
#include <forceGenerators/ParticleGenerators/p_AnchoredSpringForceGenerator.h>

namespace mtrx
{
	class p_BungeeSpringForceGenerator : public p_AnchoredSpringForceGenerator
	{
	public:
		virtual void UpdateForces(Particle* particle) override;

		p_BungeeSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength);
		~p_BungeeSpringForceGenerator();
	};
}
