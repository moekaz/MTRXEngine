/*
	Author: Mohamed Kazma
	Description: A general implementation of a collider
	PS: Calls for collision detection should be done b4 calling the updating functions
*/

#pragma once

#include <IUpdateable.h>
#include <Rigidbody.h>
#include <Defs.h>
#include <Ray.h>

namespace MTRX
{
	class Collider : public IUpdateable
	{
	public:
		int colliderId;															// Collider id
		ColliderType type;														// Collider type
		bool enabled;															// For deciding whether to do a collision detection check
		bool trigger;															// Is it a trigger collider?
		bool stillColliding;													// Still in collision
		bool enteredCollision;													// Entered collision
		bool exitedCollision;													// Exited collision	
		bool isConvexShape;														// Is the collider a convex shape

		// MAKE DIRECTION VECTORS A UNION OF vec3s and an array of size 3 of them 
		glm::vec3 forwardDirection;												// The forward direction of the collider
		glm::vec3 upDirection;													// The Upwards direction of the collider
		glm::vec3 sideDirection;												// The Side direction of the collider
		Rigidbody* rigidbody;												    // Values that might be needed are here
		std::vector<glm::vec3*> vertices;										// Store the vertices of the collider

		Collider(const ColliderType&, const glm::vec3& vec = glm::vec3(), bool isConvex = false);							// Constructor
		virtual ~Collider();															// Destructor

		virtual void PhysicsUpdate() = 0;										// Physics update
		virtual void UpdateCollisionInfo();										// Updates info on entering exiting staying in collision etc...

		// MIGHT NEED TO ADD A REFERENCE TO A REBOUND VECTOR THAT MIGHT HELP IN THE RESPONSE
		virtual bool CheckCollision(const Collider&) = 0;								// Checks for a collision (there will be multiple ones of these for each of the colliders)
		virtual bool CollisionEnter();											// When the collider enters collision
		virtual bool CollisionStay();											// When the collider stays in collision
		virtual bool CollisionExit();											// When the collider exits collision
		virtual bool RaycastCollision(const Ray&) = 0;								// Ray colliders collision detection

		const glm::vec3& GetForward() const;												// Get the forward direction according to our transformation matrix
		const glm::vec3& GetSide() const;													// Get the side direction according to our transformation matrix
		const glm::vec3& GetUp() const;														// Get the up direction according to our transformation matrix
		const glm::vec3& GetPosition() const;												// Get the position of the collider
		void SetPosition(const glm::vec3& center);								// Set a new position for the collider

		friend std::ostream& operator<<(std::ostream&, const Collider&);		// Print values of the collider

	private:
		static int id;

	protected:
		bool isColliding;														// For checking if the collider is colliding with another collider
		glm::vec3 center;														// The center position of the collider
	};
}