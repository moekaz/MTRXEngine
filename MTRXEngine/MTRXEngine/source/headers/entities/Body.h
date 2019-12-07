#pragma once

#include <entities/IIntegratable.h>
#include <Defs.h>
#include <math/Transform.h>

namespace mtrx
{
	#define MAX_MASS 10000000.f // Some large number 

	/**
	 * @brief Implementation of a basic particle body
	 * 
	 */
	class Body : IIntegratable
	{
	public:
		/**
		 * @brief Construct a new Body object
		 * 
		 * @param position The position of the body
		 * @param orientation Orientation of the body
		 * @param scale Scale of the body
		 * @param mass Mass of the body
		 */
		Body(const glm::vec3& position = glm::vec3(), const glm::quat& orientation = glm::quat(), const glm::vec3& scale = glm::vec3(), const float mass = MAX_MASS);

		/**
		 * @brief Destroy the Body object
		 * 
		 */
		virtual ~Body() = default;

		/**
		 * @brief Adding a force vector at the center of gravity of the body
		 * 
		 * @param force The force vector that we will be added to the body's force accumulator 
		 */
		inline void AddForce(const glm::vec3& force) { accumForces += force; }

		/**
		 * @brief Integrating the forces applied to the body
		 * 
		 * @param deltaTime The time elapsed between frames 
		 */
		virtual void Integrate(float deltaTime) = 0;

		/**
		 * @brief Clearing the accumulators of the body 
		 * 
		 */
		virtual void ClearAccumulators() = 0;

		// Setters 
		/**
		 * @brief Set the Inverse Mass of the body
		 * 
		 * @param inverseMass The new value of the inverse mass
		 */
		inline void SetInverseMass(const float inverseMass) { this->inverseMass = inverseMass; }

		/**
		 * @brief Set the Position of the body
		 * 
		 * @param position The new position of the body
		 */
		inline void SetPosition(const glm::vec3& position) { transform.SetPosition(position); }

		/**
		 * @brief Set the Velocity of the body
		 * 
		 * @param velocity The new velocity value of the body
		 */
		inline void SetVelocity(const glm::vec3& velocity) { this->velocity = velocity; }

		/**
		 * @brief Set the Acceleration of the body
		 * 
		 * @param acceleration The new acceleration value of the body
		 */
		inline void SetAcceleration(const glm::vec3& acceleration) { this->acceleration = acceleration; }

		/**
		 * @brief Set the Linear Damping of the body
		 * 
		 * @param damping the new linear damping value
		 */
		inline void SetLinearDamping(const float damping) { linearDamping = damping; }

		/**
		 * @brief Set the mass of the body
		 * 
		 * @param mass The new value of the mass
		 */
		void SetMass(const float mass);

		// Getters

		/**
		 * @brief Get the Orientation of the body
		 * 
		 * @return glm::quat& The quaternion orientation value
		 */
		inline glm::quat& GetOrientation() { return transform.GetOrientation(); }

		/**
		 * @brief Checking whether we this body is of infinite mass 
		 * by checking that the inverse mass is 0
		 * 
		 * @return true The body is of infinite mass
		 * @return false The body is not of infinite mass
		 */
		inline bool GetIsInfiniteMass() { return inverseMass == 0.f; }

		/**
		 * @brief Get the Inverse Mass of the body
		 * 
		 * @return float The value of the inverse mass of the body
		 */
		inline float GetInverseMass() const { return inverseMass; }

		/**
		 * @brief Get the linear damping of the body
		 * 
		 * @return float The value of the linear damping 
		 */
		inline float GetDamping() const { return linearDamping; }

		/**
		 * @brief Get the Position of the body
		 * 
		 * @return glm::vec3& The position value of the body
		 */
		inline glm::vec3& GetPosition() { return transform.GetPosition(); }

		/**
		 * @brief Get the Velocity of the body
		 * 
		 * @return glm::vec3& The value of the velocity
		 */
		inline glm::vec3& GetVelocity() { return velocity; }

		/**
		 * @brief Get the Acceleration of the body
		 * 
		 * @return glm::vec3& The value of the acceleration
		 */
		inline glm::vec3& GetAcceleration() { return acceleration; }

		/**
		 * @brief Get the accumulated forces applied on the body
		 * 
		 * @return glm::vec3& The value of the accumulated forces
		 */
		inline glm::vec3& GetAccumForces() { return accumForces; }

		/**
		 * @brief Get the Transform of the body
		 * 
		 * @return Transform& The transform of the body
		 */
		inline Transform& GetTransform() { return transform; }

		/**
		 * @brief Get the Mass of the body
		 * 
		 * @return float The mass of the body
		 */
		float GetMass() const;

	protected:
		Transform transform; // Transform information
		glm::vec3 velocity; // Velocity of this particle 
		glm::vec3 acceleration; // Acceleration of this particle
		glm::vec3 accumForces; // Accumulated forces 
		float linearDamping; // Simple damping for frictional forces (between 0 and 1)
		float inverseMass; // The mass of the particle (inverse mass is better as we don't want a zero mass and having a value of 0 is easy but infinity is hard)
	};
}
