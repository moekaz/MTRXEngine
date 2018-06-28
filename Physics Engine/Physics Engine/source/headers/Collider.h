/*
	Author: Mohamed Kazma
	Description: A general implementation of a collider
*/

#ifndef COLLIDER_H
#define COLLIDER_H

#include "Rigidbody.h"
#include "Vector3D.h"

// Should we use a union for the values of the bounds 
class Collider
{
public:
	bool enabled;							// For deciding whether to do a collision detection check
	bool trigger;							// Is it a trigger collider?
	bool stillColliding;					// Still in collision
	bool enteredCollision;					// Entered collision
	bool exitedCollision;					// Exited collision	
	
	Rigidbody* physicalValues;				// Values that might be needed are here
	Collider();								// Constructor
	~Collider();							// Destructor

	virtual void Update() = 0;				// Update the values of the collider
	virtual bool CheckCollision() = 0;		// Checks for a collision (there will be multiple ones of these for each of the colliders)

	virtual void CollisionEnter() = 0;		// When the collider enters collision
	virtual void CollisitonStay() = 0;		// When the collider stays in collision
	virtual void CollisionExit() = 0;		// When the collider exits collision

private:
protected:
	bool isColliding;						// For checking if the collider is colliding with another collider
	Vector3D center;						// The center position of the collider
};
#endif // COLLIDER_H