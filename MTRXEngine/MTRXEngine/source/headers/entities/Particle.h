#pragma once

#include <entities/IIntegratable.h>
#include <GameTime.h>
#include <entities/Body.h>

namespace mtrx
{
	class Particle : public Body
	{
	public:
		Particle(const glm::vec3& position = glm::vec3(), const float inverseMass = 0);
		~Particle();
		
		// Update values
		virtual void Integrate(float deltaTime) override;
		// Clear the accumulators
		virtual void ClearAccumulators() override;
	
	protected:
	};
}
