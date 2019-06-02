#include "PrecompiledHeader.h"
#include "ParticleRodCoupling.h"

namespace mtrx
{
	ParticleRodCoupling::ParticleRodCoupling(float lengthSqr) : lengthSqr(lengthSqr)
	{}

	ParticleRodCoupling::~ParticleRodCoupling()
	{}

	void ParticleRodCoupling::GenerateContact(std::list<ParticleCollision>& collisions, unsigned int limit)
	{
		// THIS SHOULD GENERATE 2 CONTACTS AS TO NOT MAKE THE ROD VIBRATE

		// Check the length of the rod
		float currentLengthSqr = GetCurrentLengthSqr();
		if (currentLengthSqr == lengthSqr)
			return;

		// Calculate the collision normal
		glm::vec3 normal = glm::normalize(particles[1]->GetPosition() - particles[0]->GetPosition());

		// Check which direction we need to generate the particle contact collision
		if (currentLengthSqr < lengthSqr)
			normal = -normal;

		ParticleCollision collision = ParticleCollision(particles[0], particles[1], 0, normal);
		collision.penetration = sqrt(abs(currentLengthSqr - lengthSqr));

		// THIS IS STILL A PROBLEM
		collisions.push_back(collision);
	}
}