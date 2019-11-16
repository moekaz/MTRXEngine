#include <PrecompiledHeader.h>
#include <colliders/SphereCollider.h>

namespace mtrx
{
	SphereCollider::SphereCollider(const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale, float radius) :
		Collider(ColliderType::Sphere, center, orientation, scale), radius(radius)
	{}

	SphereCollider::SphereCollider(const Transform& transform, float radius) : 
		Collider(ColliderType::Sphere, transform), radius(radius)
	{}

	SphereCollider::SphereCollider(const SphereCollider& collider1, const SphereCollider& collider2) : Collider(ColliderType::Sphere)
	{
		// Create a sphere encapsulating the 2 sphere colliders
		const glm::vec3& position1 = collider1.GetPosition();
		const glm::vec3& position2 = collider2.GetPosition();

		glm::vec3 difference = position2 - position1;
		float distanceSqr = glm::length2(difference);
		float diffRadius = collider1.radius - collider2.radius;

		if (diffRadius * diffRadius >= distanceSqr)
		{
			// One sphere is inside another one
			if (collider1.radius > collider2.radius)
			{
				SetPosition(position1);
				radius = collider1.radius;
			}
			else
			{
				SetPosition(position2);
				radius = collider2.radius;
			}
		}
		else
		{
			distanceSqr = sqrt(distanceSqr);
			radius = (distanceSqr + collider1.radius + collider2.radius) * 0.5f;

			SetPosition(position1);
			if (distanceSqr > 0)
				SetPosition(GetPosition() + (difference * (radius - collider1.radius) / distanceSqr));
		}

		SetScale(glm::vec3(radius * 2, 0.f, 0.f));
	}
}