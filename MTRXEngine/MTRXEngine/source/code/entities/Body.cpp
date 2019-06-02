#include "PrecompiledHeader.h"
#include "entities/Body.h"

namespace mtrx
{
	Body::Body(const glm::vec3& position, const float inverseMass) : position(position), velocity(glm::vec3()), acceleration(glm::vec3()),
		inverseMass(inverseMass), accumForces(glm::vec3()), linearDamping(1.f)
	{}

	Body::~Body()
	{}

	void Body::SetMass(const float mass)
	{
		assert(mass != 0); // We are not supposed to have a 0 mass 
		inverseMass = 1.f / mass;
	}

	float Body::GetMass() const
	{
		if (inverseMass == 0)
			return MAX_MASS;
		else
			return 1.f / inverseMass;
	}
}
