/*
	Author: Mohamed Kazma
	Description: Capsule colliders
*/

#pragma once

#include <Defs.h>
#include <Collider.h>
#include "CollisionUtil.h"

namespace MTRX
{
	class CapsuleCollider : public Collider
	{
	public:
		// HAVE A POINT AT THE END OF THE CAPSULE TO RECALCULATE THE RADIUS OF THE CAPSULE AFTER SCALING
		float radii;																		// radii of the 2 spheres of the capsule
		glm::vec3 A;																		// Center of the first sphere													
		glm::vec3 B;																		// Center of the second sphere
		float height;																		// Height of the capsule

		CapsuleCollider(const glm::vec3& = glm::vec3(), float = 0.25f, float = 0.5f);		// Constructor
		~CapsuleCollider();																	// Destructor

		bool CheckCollision(const Collider&);														// Function for checking collision
		bool RaycastCollision(const Ray&);														// Raycast collision
		void PhysicsUpdate();

		friend std::ostream& operator<<(std::ostream&, const CapsuleCollider&);				// Print out the values of the collider

	private:
	protected:
	};
}