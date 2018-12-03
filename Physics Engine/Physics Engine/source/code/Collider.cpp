/*
	Author: Mohamed Kazma
	Description: Some general implementation of all colliders
*/

#include <PrecompiledHeader.h>

#include <Collider.h>

namespace MTRX
{
	int Collider::id = 0;	// Set the value of the static int id 

	/* Constructor */
	Collider::Collider(const ColliderType& colliderType, const glm::vec3& vec, bool isConvex)
		: colliderId(id), center(vec), enabled(true), trigger(false), isColliding(false), exitedCollision(false), enteredCollision(false), stillColliding(false),
		forwardDirection(glm::vec3(0, 0, -1)), upDirection(glm::vec3(0, 1, 0)), type(colliderType), isConvexShape(isConvex)
	{
		++id;
		sideDirection = glm::normalize(glm::cross(-forwardDirection, upDirection));	// Calculate directions of the collider
	}

	/* Destructor */
	Collider::~Collider()
	{
		// Delete the vertices
		for (unsigned int i = 0; i < vertices.size(); ++i)
		{
			delete vertices[i];
		}
	}

	/* Functions */

	// Direction vectors
	const glm::vec3& Collider::GetForward() const { return forwardDirection; }
	const glm::vec3& Collider::GetSide() const { return sideDirection; }
	const glm::vec3& Collider::GetUp() const { return upDirection; }
	const glm::vec3& Collider::GetPosition() const { return this->center; }

	void Collider::SetPosition(const glm::vec3& center) { this->center = center; }

	// Update collision info 
	void Collider::UpdateCollisionInfo()
	{
		// Do some checks on what is the state of the collision
		if (isColliding)
		{
			if (enteredCollision)
			{
				enteredCollision = false;	// Entering collision only happens on one frame
				stillColliding = true;		// Still in collision
			}
			else if (!stillColliding)
			{
				enteredCollision = true;
			}
		}
		else
		{
			if (exitedCollision) exitedCollision = false;	// exiting collision only occurs once
			else if (stillColliding || enteredCollision) exitedCollision = true;

			// reset the values
			enteredCollision = false;
			stillColliding = false;
		}
	}

	// Checking for whether we just entered collision
	bool Collider::CollisionEnter()
	{
		return false;
	}

	// Checking for whether we just exited collision
	bool Collider::CollisionExit()
	{
		return false;
	}

	// Checking for whether we are staying in collision
	bool Collider::CollisionStay()
	{
		return false;
	}

	// Print the general values of a collider
	std::ostream& operator<<(std::ostream& os, const Collider& col)
	{
		os << "Collider:" << std::endl
			<< "---------" << std::endl
			<< "Center: " << std::endl
			<< "x: " << col.center.x << std::endl
			<< "y: " << col.center.y << std::endl
			<< "z: " << col.center.z;

		return os;
	}
}