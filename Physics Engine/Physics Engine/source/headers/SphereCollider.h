/*
	Author: mohamed kazma
	Description: Header file for a sphere collider
*/

#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Collider.h"

class SphereCollider : Collider
{
public:
	SphereCollider();			// Constructor 
	~SphereCollider();			// Destructor

	void Update();				// Update collider values
	bool CheckCollision();		// Check for collision

	// These might need to be virtual functions as they could have the same implementation
	void CollisionEnter();		// Check whether we entered collsiion
	void CollisionStay();		// Check whether we are still in collision	
	void CollisionExit();		// Check whether we have exited collision
private:
protected:
};
#endif // SPHERECOLLIDER_H