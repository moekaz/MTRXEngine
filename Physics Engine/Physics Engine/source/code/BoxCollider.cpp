/*
	Author: Mohamed Kazma
	Description: Implementation of a box collider
*/

#include "../headers/BoxCollider.h"

/* Constructor */
BoxCollider::BoxCollider() 
{
	type = ColliderType::Box;
}

/* Destructor */
BoxCollider::~BoxCollider() {}

/* Functions */

// Update values of the collider
void BoxCollider::Update()
{
}

// Gives us whether there is a collision occurring
bool BoxCollider::CheckCollision()
{
}

// Checks whether we have entered collision
void BoxCollider::CollisionEnter()
{
	if (!isColliding && CheckCollision()) isColliding = true; // We have entered collision
}

// Checks whether we are still in collision
void BoxCollider::CollisionStay()
{
	if (isColliding && CheckCollision()) isColliding = true; // We are still in collision
}

// Checks for whether we have exited collision
void BoxCollider::CollisionExit()
{
	if (isColliding && !CheckCollision()) isColliding = false; // We are no longer in collision
}