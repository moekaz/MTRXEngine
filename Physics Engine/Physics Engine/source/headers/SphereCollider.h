/*
	Author: mohamed kazma
	Description: Header file for a sphere collider
*/

#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include <iostream>

#include "Vector3D.h"
#include "Collider.h"
#include "BoxCollider.h"
//#include "CapsuleCollider.h"
//#include "MeshCollider.h"

class SphereCollider : public Collider
{
public:
	float radius;				// Radius of a sphere collider

	SphereCollider(Vector3D vec = Vector3D());			// Constructor 
	~SphereCollider();			// Destructor

	void Update(const Vector3D&);				// Update collider values
	friend std::ostream& operator<<(std::ostream& , const SphereCollider&);

private:
protected:
	bool SphereCollision(Collider&);
	bool BoxCollision(Collider&);
	bool CapsuleCollision(Collider&);
	bool MeshCollision(Collider&);
};
#endif // SPHERECOLLIDER_H