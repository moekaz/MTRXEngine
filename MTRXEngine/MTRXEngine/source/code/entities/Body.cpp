#include "PrecompiledHeader.h"
#include "entities/Body.h"

namespace mtrx
{
	Body::Body(const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scale, float mass) : transform(position, orientation, scale), 
		velocity(glm::vec3()), acceleration(glm::vec3()), accumForces(glm::vec3()), linearDamping(1.f)
	{
		SetMass(mass);
	}

	void Body::SetMass(const float mass)
	{
		if (mass == 0)
			inverseMass = 0;
		else
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
