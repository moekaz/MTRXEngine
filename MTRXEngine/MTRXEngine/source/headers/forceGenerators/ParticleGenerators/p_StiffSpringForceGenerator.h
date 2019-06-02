/*
	Author: Mohamed Kazma
	Description: A very inaccurate implementation of a stiff spring using force averages 
	(This is not accurate and to be used in very limited positions velocity simulation can be incorrect and doesn't take other forces into consideration
	and there is no rest length for the spring and is also to be used on one particle instead of 2)
*/

#pragma once

#include <forceGenerators/ParticleGenerators/IParticleForceGenerator.h>
#include <entities/Particle.h>

namespace mtrx
{
	class p_StiffSpringForceGenerator : public IParticleForceGenerator
	{
	public:
		float springStiffness; // Stiffness constant of the spring
		glm::vec3* anchorPoint; // Anchor point that the spring is hung from
		float springDamping; // Damping caused by by the spring forces

		virtual void UpdateForces(Particle* particle) override;

		p_StiffSpringForceGenerator(glm::vec3* anchorPoint, float springStiffness, float springDamping);
		~p_StiffSpringForceGenerator();

		inline void SetAnchorPoint(glm::vec3* point) { anchorPoint = point; }
	};
}