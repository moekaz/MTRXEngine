/*
	Author: Mohamed Kazma
	Description: implementation of a sphere collider
*/

#include "../headers/SphereCollider.h"

/* Constructor */
SphereCollider::SphereCollider(Vector3D center) : Collider(center)
{
	type = ColliderType::Sphere;
}

/* Destructor */
SphereCollider::~SphereCollider() {}

/* Functions */

// Update the values of the collider
void SphereCollider::Update(const Vector3D& newCenter) 
{
	center = newCenter;
}

// Sphere Sphere collision detection
bool SphereCollider::SphereCollision(Collider& col) 
{	
	SphereCollider& sph = static_cast<SphereCollider&>(col);
	Vector3D diff = center - sph.center;
	return diff.x + diff.y + diff.z < (radius + sph.radius) * (radius + sph.radius);	// diff between centers is less than the radii of the 2 colliders
}

// Sphere Box collision detection
bool SphereCollider::BoxCollision(Collider&) 
{
}

// Sphere capsule collision detection
bool SphereCollider::CapsuleCollision(Collider&) 
{
}

// Sphere mesh collision detection 
bool SphereCollider::MeshCollision(Collider&) 
{
}

// Print out values of the collider
std::ostream& operator<<(std::ostream& os , const SphereCollider& sphCollider)
{
	os << "Sphere Collider:" << std::endl
		<< "---------------" << std::endl
		<< "Center: " << sphCollider.center << std::endl
		<< "Radius: " << sphCollider.radius << std::endl;

	return os;
}
