/*
	Author: Mohamed Kazma
	Description: A general implementation of a collider
*/

#ifndef COLLIDER_H
#define COLLIDER_H

#include "Rigidbody.h"

class Collider
{
public:
	bool enabled;							// For deciding whether to do a collision detection check
	bool isColliding;						// For checking if the collider is colliding with another collider

	Rigidbody* physicalValues;				// Values that might be needed are here
	Collider();								// Constructor
	~Collider();							// Destructor

	virtual void Update() = 0;				// Update the values of the collider
	virtual bool CheckCollision() = 0;		// Checks for a collision (there will be multiple ones of these for each of the colliders)

private:
protected:
};
#endif // COLLIDER_H