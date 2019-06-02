/*
	Author: Mohamed Kazma
	Description: Colliders with a convex shape (We can use SAT for collision with these shapes)
*/

#pragma once

#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>

namespace mtrx
{
	class ConvexShapeCollider : public Collider
	{
	public:
		std::vector<glm::vec3*> vertices;

		ConvexShapeCollider(const ColliderType& colliderType = ColliderType::ConvexShape, const glm::vec3& = glm::vec3());
		~ConvexShapeCollider();

		// Used for GJK minkowski sum calculations
		glm::vec3 Support(const ConvexShapeCollider&, const glm::vec3&) const;
		glm::vec3& FarthestPointInDirection(const glm::vec3&) const;

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;
	};
}