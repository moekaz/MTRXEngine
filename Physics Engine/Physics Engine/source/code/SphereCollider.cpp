/*
	Author: Mohamed Kazma
	Description: implementation of a sphere collider
*/

#include "../headers/SphereCollider.h"

/* Constructor */
SphereCollider::SphereCollider() 
{
	type = ColliderType::Sphere;
}

/* Destructor */
SphereCollider::~SphereCollider() {}

/* Functions */

void SphereCollider::Update() 
{
}

bool SphereCollider::SphereCollision(Collider&) 
{
}

bool SphereCollider::BoxCollision(Collider&) 
{
}

bool SphereCollider::CapsuleCollision(Collider&) 
{
}

bool SphereCollider::MeshCollision(Collider&) 
{
}

