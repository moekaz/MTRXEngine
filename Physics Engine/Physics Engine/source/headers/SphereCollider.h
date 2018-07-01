/*
	Author: mohamed kazma
	Description: Header file for a sphere collider
*/

#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Collider.h"
#include "BoxCollider.h"
//#include "CapsuleCollider.h"
//#include "MeshCollider.h"

class SphereCollider : Collider
{
public:
	SphereCollider();			// Constructor 
	~SphereCollider();			// Destructor

	void Update();				// Update collider values

private:
protected:
	bool SphereCollision(Collider&);
	bool BoxCollision(Collider&);
	bool CapsuleCollision(Collider&);
	bool MeshCollision(Collider&);
};
#endif // SPHERECOLLIDER_H