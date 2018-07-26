/*
	Author: Mohamed Kazma
	Description: Implementation of a box collider
*/

#include "../headers/BoxCollider.h"
#include "../headers/SphereCollider.h"
#include "../headers/CapsuleCollider.h"
//#include "../headers/MeshCollider"

/* Constructor */
BoxCollider::BoxCollider(const glm::vec3& center) : ConvexShapeCollider(center)
{
	type = ColliderType::Box;
	halfExtents = glm::vec3(0.5 , 0.5 , 0.5);	// The width along each axis should be 1 

	// Setup vertices and mins and maxes
	vertices =
	{
		new glm::vec3(-0.5 , 0.5 , 0.5),
		new glm::vec3(0.5 , 0.5 , 0.5),
		new glm::vec3(-0.5 , -0.5 , 0.5),
		new glm::vec3(0.5 , -0.5 , 0.5),
		new glm::vec3(-0.5 , 0.5 , -0.5),
		new glm::vec3(0.5 , 0.5 , -0.5),
		new glm::vec3(-0.5 , -0.5 , -0.5),
		new glm::vec3(0.5 , -0.5 , -0.5),
	};

	min = glm::vec3(-0.5, -0.5, -0.5);	// Minimum positions
	max = glm::vec3(0.5, 0.5, 0.5);		// Maximum positions
}

/* Destructor */
BoxCollider::~BoxCollider() {}

/* Functions */

// Update values of the collider
void BoxCollider::Update(glm::vec3& center)
{
	this->center = center;
	// RecomputeMinsMaxes();
}

// Gives us whether there is a collision occurring
bool BoxCollider::CheckCollision(Collider& col)
{
	bool collision = false;

	switch (col.type)
	{
		case ColliderType::Sphere:
		{
			std::cout << "box sphere collision detection" << std::endl;
			SphereCollider& collider = static_cast<SphereCollider&>(col);
			std::vector<glm::vec3> axes = {sideDirection , upDirection , forwardDirection};
			collision = CollisionUtil::SphereBoxCollision(collider.center , center , collider.radius , min , max , axes , halfExtents);
			break;
		}
		case ColliderType::Box:
		{
			std::cout << "box box collision detection" << std::endl;
			BoxCollider& collider = static_cast<BoxCollider&>(col);
			collision = CollisionUtil::BoxBoxCollision(*this , collider);
			break;
		}
		case ColliderType::Capsule:
		{
			std::cout << "box capsule collision detection" << std::endl;
			CapsuleCollider& collider = static_cast<CapsuleCollider&>(col);
			std::vector<glm::vec3> axes = { sideDirection , upDirection , forwardDirection };
			collision = CollisionUtil::BoxCapsuleCollision(center, collider.center, collider.A, collider.B, collider.radii, min, max, axes, halfExtents); 
			break;
		}
		case ColliderType::Mesh:
		{
			std::cout << "box mesh collision detection" << std::endl;
			//SphereCollider& collider = static_cast<SphereCollider&>(col);
			//std::vector<glm::vec3> axes = { sideDirection , upDirection , forwardDirection };
			//collision = CollisionUtil::SphereBoxCollision(collider.center, center, collider.radius, min, max, axes, halfExtents);
			break;
		}
		default:
		{
			std::cout << "HOUSTON WE HAVE A PROBLEM" << std::endl;
			collision = false;
		}
	}

	UpdateCollisionInfo();
	return collision;
}

// Recalculate the mins and maxes again
void BoxCollider::RecomputeMinsMaxes()
{
	// Minimum and maximum float values
	float maximum = std::numeric_limits<float>::infinity();
	float minimum = -std::numeric_limits<float>::infinity();

	min = glm::vec3(maximum , maximum, maximum);
	max = glm::vec3(minimum , minimum, minimum);

	for (int i = 0; i < vertices.size(); i++)
	{
		min.x = min.x > vertices[i]->x ? vertices[i]->x : min.x;
		min.y = min.y > vertices[i]->y ? vertices[i]->y : min.y;
		min.z = min.z > vertices[i]->z ? vertices[i]->z : min.z;

		max.x = max.x < vertices[i]->x ? vertices[i]->x : max.x;
		max.y = max.y < vertices[i]->y ? vertices[i]->y : max.y;
		max.x = max.z < vertices[i]->z ? vertices[i]->z : max.z;
	}

	halfExtents = (max - center) * 0.5f;	// Recalculate half extents
}

// Print the values of the box collider
std::ostream& operator<<(std::ostream& os, const BoxCollider& box)
{
	os << "Box Collider:" << std::endl
		<< "-------------" << std::endl
		<< "Center: " << box.center << std::endl
		<< "Mins: " << box.min << std::endl
		<< "Maxes: " << box.max << std::endl;

	return os;
}