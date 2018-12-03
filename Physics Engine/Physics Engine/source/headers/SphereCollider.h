/*
	Author: mohamed kazma
	Description: Header file for a sphere collider
*/

#pragma once

#include <Collider.h>
#include <CollisionUtil.h>

namespace MTRX
{
	// Forward declarations
	class BoxCollider;
	class CapsulesCollider;
	class MeshCollider;

	class SphereCollider : public Collider
	{
	public:
		float radius;																	// Radius of a sphere collider

		SphereCollider(const glm::vec3& vec = glm::vec3(), float radius = 0.5);			// Constructor 
		~SphereCollider();																// Destructor

		void PhysicsUpdate();
		bool CheckCollision(const Collider&);													// Sphere collision detection
		bool RaycastCollision(const Ray&);													// Raycast collision

		friend std::ostream& operator<<(std::ostream&, const SphereCollider&);			// Print out values of the collider

	private:
	protected:
	};
}