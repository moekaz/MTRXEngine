/*
	Author: Mohamed Kazma
	Description: An implementation of a box collider
*/

#pragma once

#include <ConvexShapeCollider.h>
#include <CollisionUtil.h>

namespace MTRX
{
	// Forward declarations
	class SphereCollider;
	class CapsuleCollider;
	class MeshCollider;

	class BoxCollider : public ConvexShapeCollider
	{
	public:
		glm::vec3 min;															// Stores min x,y,z
		glm::vec3 max;															// Stores max x,y,z
		glm::vec3 halfExtents;													// Half widths along each axis

		BoxCollider(const glm::vec3& = glm::vec3());							// Constructor
		~BoxCollider();															// Destrutor

		const std::vector<glm::vec3*>& GetAxes() const; // Get axes
		void PhysicsUpdate();
		bool CheckCollision(const MTRX::Collider&);											// Check collision with box collider 
		bool RaycastCollision(const Ray&);									    // Raycast collision
		void RecomputeMinsMaxes();												// Recalculates the min and max values of the vertices 

		friend std::ostream& operator<<(std::ostream& os, const BoxCollider&);	// Print out the values of th collider

	private:
		std::vector<glm::vec3*> axes;														// Store the axes of the box collider

	protected:
	};
}