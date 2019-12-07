#pragma once

#include <entities/IIntegratable.h>
#include <math/GameTime.h>
#include <entities/Body.h>

namespace mtrx
{
	/**
	 * @brief Implementation of rigidbodies with rigidbody dynamics newtonian force integration and 
	 * rotational forces
	 * 
	 */
	class Rigidbody : public Body
	{
	public:
		/**
		 * @brief Construct a new Rigidbody object
		 * 
		 * @param mass The mass of the rigidbody
		 * @param iskinematic Whether the rigidbody is kinematic. A kinematic object does not affect other rigidbodies in the simulation
		 * @param position The position of the rigidbody
		 * @param orientation The orientation of the rigidbody
		 * @param scale The scale of the rigidbody
		 * @param inertiaTensor The inertia tensor of the rigidbody
		 */
		Rigidbody(float mass = MAX_MASS, bool iskinematic = false, const glm::vec3& position = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, glm::vec3(0, 1, 0)), const glm::vec3& scale = glm::vec3(1, 1, 1), const glm::mat3& inertiaTensor = glm::mat3(1.0f));
		
		/**
		 * @brief Destroy the Rigidbody object
		 * 
		 */
		~Rigidbody() = default;
		
		// Setters

		/**
		 * @brief Set the Inverse Inertia Tensor of the body
		 * 
		 * @param inertiaTensor The inertia tensor that we will calculate the inverse of
		 */
		void SetInverseInertiaTensor(const glm::mat3& inertiaTensor);
		
		/**
		 * @brief Set the Angular Damping of the rigidbody
		 * Angular damping allows us to dampen torque forces applied
		 * to the body as a function of time
		 * 
		 * @param angularDamping The new value of angular damping 
		 */
		inline void SetAngularDamping(float angularDamping) { this->angularDamping = angularDamping; }
		
		/**
		 * @brief Set the Orientation of the body
		 * 
		 * @param orientation The new orientation of the body
		 */
		inline void SetOrientation(glm::quat& orientation) { transform.SetOrientation(orientation); }
		
		/**
		 * @brief Set the Rotation value of the rigidbody
		 * This rotation value is used to generate torque forces
		 * 
		 * @param rotation The new value of the rotation
		 */
		inline void SetRotation(glm::vec3& rotation) { this->rotation = rotation; }
		
		/**
		 * @brief Set the kinematic value
		 * 
		 * @param kinematic the new value of whether the body is kinematic
		 */
		inline void SetIsKinematic(bool kinematic) { isKinematic = kinematic; }

		// Getters

		/**
		 * @brief Get the Inverse Inertia Tensor of the body
		 * 
		 * @return glm::mat3& The inver inertia tensor
		 */
		inline glm::mat3& GetInverseInertiaTensor() { return inverseInertiaTensor; }

		/**
		 * @brief Get the Angular Damping of the body
		 * 
		 * @return float The value of the angular damping
		 */
		inline float GetAngularDamping() const { return angularDamping; }
		
		/**
		 * @brief Get the Obj To World Mat 
		 * 
		 * @return glm::mat3x4 The object space to world matrix
		 */
		inline glm::mat3x4 GetObjToWorldMat() { return objToWorldMat; }
		
		/**
		 * @brief Get the Rotation of the body
		 * 
		 * @return glm::vec3& The rotation of the body
		 */
		inline glm::vec3& GetRotation() { return rotation; }
		
		/**
		 * @brief Get whether the body is kinematic
		 * 
		 * @return true The body is kinematic
		 * @return false The body is not kinematic
		 */
		inline bool GetIsKinematic() { return isKinematic; }
		
		// Calculate inverse inertia tensor in world space instead of object space  
		
		/**
		 * @brief Calculating the inverse inertia tensor in world space 
		 * 
		 * @return glm::mat3 Inverse inertia tensor in world space
		 */
		inline glm::mat3 CalculateIITWorld() { return objToWorldMat * inverseInertiaTensor; }
		
		// Add Torque force
		
		/**
		 * @brief Add a torque force
		 * 
		 * @param torque The torque force that we want to add
		 */
		inline void AddTorque(const glm::vec3& torque) { accumTorque += torque; }

		// Clear accumulators

		/**
		 * @brief Clear acculmulators of rigidbody
		 * 
		 */
		void ClearAccumulators() override;
	
		// Update the values of the rigidbody
		
		/**
		 * @brief Integrate the values of the rigidbody
		 * 
		 * @param deltaTime The time elapsed by previous frame
		 */
		void Integrate(float deltaTime) override;

		// Calculate the transformation matrix
		
		/**
		 * @brief Calculate object space to world space matrix
		 * 
		 */
		void CalculateObjToWorldMat();

		// Add a force at a certain point of the rigidbody (helps in calculating torque forces) PS: point is assumed in world space
		
		/**
		 * @brief Add a force at a certain point in space
		 * 
		 * @param force The force that we want to add 
		 * @param point The point upon which to apply the force
		 */
		void AddForceAtPoint(const glm::vec3& force, const glm::vec3& point);

		// Calculate intrinsic rigidbody data
		
		/**
		 * @brief Update some of the information of the rigidbody
		 * 
		 */
		void CalculateBodyData();

	private:
		glm::vec3 rotation; // Not sure
		// The inverse inertia tensor is used since it is more useful to calculating the torque generated
		// Based in object's space and not in world space
		glm::mat3 inverseInertiaTensor;
		// From this object's space to world space
		glm::mat3x4 objToWorldMat;
		glm::vec3 accumTorque; // Accumulated torque
		float angularDamping; // Between 0-1
		bool isKinematic;

		// Space vectors 
		ObjectAxes axes;
	};
}