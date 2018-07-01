/*
	Author: Mohamed Kazma
	Description: A general implementation of a collider
*/

#ifndef COLLIDER_H
#define COLLIDER_H

#include "Rigidbody.h"
#include "Vector3D.h"
#include "defs.h"

// Should we use a union for the values of the bounds 
class Collider
{
public:
	ColliderType type;									// Collider type
	bool enabled;										// For deciding whether to do a collision detection check
	bool trigger;										// Is it a trigger collider?
	bool stillColliding;								// Still in collision
	bool enteredCollision;								// Entered collision
	bool exitedCollision;								// Exited collision	
	
	Rigidbody* physicalValues;							// Values that might be needed are here
	
	Collider(Vector3D vec = Vector3D());				// Constructor
	~Collider();										// Destructor

	virtual void Update() = 0;							// Update the values of the collider
	virtual bool CheckCollision(Collider&);				// Checks for a collision (there will be multiple ones of these for each of the colliders)

	virtual bool CollisionEnter();						// When the collider enters collision
	virtual bool CollisionStay();						// When the collider stays in collision
	virtual bool CollisionExit();						// When the collider exits collision

private:
protected:
	bool isColliding;									// For checking if the collider is colliding with another collider
	Vector3D center;									// The center position of the collider
	
	virtual bool SphereCollision(Collider&) = 0;		// Collider and sphere collider collision
	virtual bool BoxCollision(Collider&) = 0;			// Collider and box collider collision
	virtual bool CapsuleCollision(Collider&) = 0;		// Collider and capsule collider collision
	virtual bool MeshCollision(Collider&) = 0;			// Collider and mesh collider collision 
};
#endif // COLLIDER_H