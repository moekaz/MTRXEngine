/*
	Author: Mohamed Kazma
	Description: Implementation of rigidbodies
*/

#include <PrecompiledHeader.h>
#include <Rigidbody.h>

// MIGHT WANT TO READ UP ON SOME TORQUE AND ROTATIONAL FORCES
// MIGHT WANT TO ADD SOME FRICTIONAL FORCES

namespace MTRX
{
	// Set the value of gravity that will be used for gravity calculations 
	float Rigidbody::gravity = 9.81f;

	// Constructor
	Rigidbody::Rigidbody(float mass, bool isKinematic, const glm::vec3& position, float maxSpeed) : mass(mass), isKinematic(isKinematic), position(position), maxSpeed(maxSpeed),
		previousPosition(glm::vec3()), velocity(glm::vec3()), acceleration(glm::vec3()), orientation(glm::quat()), forward(glm::vec3(0, 0, -1)), side(glm::vec3(1, 0, 0)),
		up(glm::vec3(0, 1, 0))
	{
	}

	// Destructor
	Rigidbody::~Rigidbody() {}

	// Get Position 
	glm::vec3& Rigidbody::GetPosition() { return position; }

	// Set position
	void Rigidbody::SetPosition(const glm::vec3& position) { this->position = position; }

	// Update the values of the rigid body
	void Rigidbody::PhysicsUpdate()
	{
		// Check for gravity (Weight = mg so we don't need to divide by mass when we add that force)
		if (isKinematic) acceleration.y -= gravity;

		// A = V / T => V = A * T
		//velocity = acceleration * GameTime::deltaTime;

		// Store temporary position
		glm::vec3& temp = position;

		// Move the position of the rigidbody (verlet integeration)
		position += (position - previousPosition) + acceleration * GameTime::deltaTime * GameTime::deltaTime;

		// Store Previous position
		previousPosition = temp;

		// Reset the velocity values
		//velocity.x = 0;
		//velocity.y = 0;
		//velocity.z = 0;

		// Reset acceleration values
		acceleration.x = 0;
		acceleration.y = 0;
		acceleration.z = 0;
	}

	// Apply a force on an rigidbody (Newtonian force application)
	void Rigidbody::ApplyForce(const glm::vec3& force)
	{
		acceleration += force / mass;	// Newtonian physics (SUM OF FORCES = MASS * ACCELERATION)
		// Check for torsional and torque forces induced
	}

	// Rotate a rigidbody with a certain rotation quaternion
	void Rigidbody::Rotate(const glm::quat& rotation)
	{
		orientation = rotation * orientation;
	}

	// Look at a certain position
	void Rigidbody::LookAt(const glm::vec3& lookPosition)
	{
	}
}