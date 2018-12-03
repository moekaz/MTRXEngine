/*
	Author: Mohamed Kazma
	Description: Colliders with a convex shape (We can use SAT for collision with these shapes)
*/

#pragma once

#include <Collider.h>
#include <CollisionUtil.h>

namespace MTRX
{
	class ConvexShapeCollider : public Collider
	{
	public:
		ConvexShapeCollider(const ColliderType& colliderType = ColliderType::ConvexShape, const glm::vec3& = glm::vec3());			// Constructor
		~ConvexShapeCollider();											// Destructor

		glm::vec3 Support(const ConvexShapeCollider&, const glm::vec3&) const;		// Support is used to build a simplex as it will return a point on the minkowski sum (or difference depending on naming) 
		glm::vec3& FarthestPointInDirection(const glm::vec3&) const;				// Farthest point within a certain direction

		bool CheckCollision(const Collider&);								    // Does collision detection checks
		virtual bool RaycastCollision(const Ray&);							// Raycast collision
		virtual void PhysicsUpdate();

	private:
	protected:
	};
}