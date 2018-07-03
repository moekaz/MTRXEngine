/*
	Author: Mohamed Kazma
	Description: A general implementation of a collider
	PS: Calls for collision detection should be done b4 calling the updating functions
*/

#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>

#include "Rigidbody.h"
#include "Vector3D.h"
#include "Defs.h"

// Should we use a union for the values of the bounds 
class Collider
{
public:
	ColliderType type;														// Collider type
	bool enabled;															// For deciding whether to do a collision detection check
	bool trigger;															// Is it a trigger collider?
	bool stillColliding;													// Still in collision
	bool enteredCollision;													// Entered collision
	bool exitedCollision;													// Exited collision	
	Vector3D center;														// The center position of the collider

	Rigidbody* physicalValues;												// Values that might be needed are here
	
	Collider(const Vector3D& vec = Vector3D::zero);							// Constructor
	~Collider();															// Destructor

	virtual void Update(const Vector3D&) = 0;								// Update the values of the collider
	virtual void UpdateCollisionInfo();										// Updates info on entering exiting staying in collision etc...
	virtual bool CheckCollision(Collider&) = 0;								// Checks for a collision (there will be multiple ones of these for each of the colliders)

	virtual bool CollisionEnter();											// When the collider enters collision
	virtual bool CollisionStay();											// When the collider stays in collision
	virtual bool CollisionExit();											// When the collider exits collision

	friend std::ostream& operator<<(std::ostream& , const Collider&);		// Print values of the collider

private:
protected:
	bool isColliding;														// For checking if the collider is colliding with another collider
};
#endif // COLLIDER_H