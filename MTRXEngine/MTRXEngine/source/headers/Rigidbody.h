/*
	Author: Mohamed Kazma
	Description: Rigidbody physics implementation
*/

#pragma once

#include <IUpdateable.h>
#include <GameTime.h>

namespace MTRX
{
	class Rigidbody : IUpdateable
	{
	public:
		static float gravity;	// The value of gravity for the world
		float mass;	// Mass of the rigid body
		float airResistance;	// The value of drag
		float angularDrag;	// Angular drag
		float maxSpeed;	// Maximum speed 
		bool isKinematic;	// Check for whether the body is on the floor or not

		glm::vec3 forward;	// forward vector
		glm::vec3 side;	// Side vector
		glm::vec3 up;	// Up vector
		glm::quat orientation;	// The orientation of a rigidbody

		Rigidbody(float mass = 1.f, bool iskinematic = true, const glm::vec3& position = glm::vec3(), float maxSpeed = 1.f);	// Constructor
		~Rigidbody();	// Destructor

		void PhysicsUpdate();	// Update the values of the rigidbody
		void ApplyForce(const glm::vec3& force);	// Apply a force on a rigidbody
		void Rotate(const glm::quat& rotation);	// rotate the rigidbody
		void LookAt(const glm::vec3& lookPosition);	// Rotate towards a certain point
		glm::vec3& GetPosition();	// Get the position of rigidbody
		void SetPosition(const glm::vec3& position);	// Set the position of the rigidbody

	private:
		glm::vec3 position;	// Position of the rigidbody
		glm::vec3 previousPosition;	// Previous position used for verlet integration
		glm::vec3 velocity; // Velocity of the rigidbody
		glm::vec3 acceleration;	// Acceleration of the rigidbody
	protected:
	};
}