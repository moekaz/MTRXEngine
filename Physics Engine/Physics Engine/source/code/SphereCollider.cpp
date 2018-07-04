/*
	Author: Mohamed Kazma
	Description: implementation of a sphere collider
*/

#include "../headers/SphereCollider.h"
#include "../headers/BoxCollider.h"
//#include "../headers/CapsuleCollider.h"
//#include "../headers/MeshCollider"

/* Constructor */
SphereCollider::SphereCollider(const Vector3D& center , float radius) : Collider(center)
{
	type = ColliderType::Sphere;
	this->radius = radius;
}

/* Destructor */
SphereCollider::~SphereCollider() {}

/* Functions */

// Update the values of the collider
void SphereCollider::Update(const Vector3D& newCenter) 
{
	center = newCenter;
}

// Checking for collision since this is going to be polymorphic it would make sense to use a general collider and work from there
bool SphereCollider::CheckCollision(Collider& col)
{
	switch (col.type)
	{
		case ColliderType::Sphere:
		{
			std::cout << "SPHERE SPHERE COLLISON DETECTION" << std::endl;
			SphereCollider& collider = static_cast<SphereCollider&>(col);
			isColliding = CollisionUtil::SphereSphereCollision(*this , collider);
			break;
		}
		case ColliderType::Box:
		{
			std::cout << "SPHERE BOX COLLISION DETECTION" << std::endl;
			BoxCollider& collider = static_cast<BoxCollider&>(col);
			isColliding = CollisionUtil::SphereBoxCollision(*this , collider);
			break;
		}
		case ColliderType::Capsule:
		{
			std::cout << "SPHERE CAPSULE COLLISION DETECTION" << std::endl;
			isColliding = CollisionUtil::SphereCapsuleCollision();
			break;
		}
		case ColliderType::Mesh:
		{
			std::cout << "SPHERE MESH COLLISION DETECTION" << std::endl;
			isColliding = CollisionUtil::SphereMeshCollision();
			break;
		}
		default:
		{
			std::cout << "SHIT HIT THE FAN" << std::endl;
			isColliding = false;
		}
	}

	UpdateCollisionInfo();	// Update info about when the collision started etc...

	return isColliding;
}

// Print out values of the collider
std::ostream& operator<<(std::ostream& os , const SphereCollider& sphCollider)
{
	os << "Sphere Collider:" << std::endl
		<< "---------------" << std::endl
		<< "Center: " << sphCollider.center << std::endl
		<< "Radius: " << sphCollider.radius;

	return os;
}
