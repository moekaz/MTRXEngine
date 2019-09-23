/*
	Author: Mohamed Kazma
	Description: Rigidbody physics implementation
*/

#pragma once

#include <IIntegratable.h>
#include <GameTime.h>
#include <entities/Body.h>

namespace mtrx
{
	class Rigidbody : public Body
	{
	public:
		Rigidbody(float mass = MAX_MASS, bool iskinematic = false, const glm::vec3& position = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, glm::vec3(0, 1, 0)), const glm::vec3& scale = glm::vec3(1, 1, 1), const glm::mat3& inertiaTensor = glm::mat3(1.0f));
		~Rigidbody();
		
		// Setters
		void SetInverseInertiaTensor(const glm::mat3& inertiaTensor);
		inline void SetAngularDamping(float angularDamping) { this->angularDamping = angularDamping; }
		inline void SetOrientation(glm::quat& orientation) { transform.SetOrientation(orientation); }
		inline void SetRotation(glm::vec3& rotation) { this->rotation = rotation; }
		inline void SetIsKinematic(bool kinematic) { this->isKinematic = kinematic; }

		// Getters
		inline glm::mat3& GetInverseInertiaTensor() { return inverseInertiaTensor; }
		inline float GetAngularDamping() const { return angularDamping; }
		inline glm::mat3x4 GetObjToWorldMat() { return objToWorldMat; }
		inline glm::vec3& GetRotation() { return rotation; }
		inline bool GetIsKinematic() { return isKinematic; }
		
		// Calculate inverse inertia tensor in world space instead of object space  
		inline glm::mat3 CalculateIITWorld() { return objToWorldMat * inverseInertiaTensor; }
		
		// Clear accumulators
		void ClearAccumulators() override;

		// Add Torque force
		inline void AddTorque(const glm::vec3& torque) { accumTorque += torque; }

		// Update the values of the rigidbody
		void Integrate(float deltaTime) override;
		// IntegrateRotation
		void IntegrateRotation();
		// Calculate the transformation matrix
		void CalculateObjToWorldMat();
		// Add a force at a certain point of the rigidbody (helps in calculating torque forces) PS: point is assumed in world space
		void AddForceAtPoint(const glm::vec3& force, const glm::vec3& point);
		// Calculate intrinsic rigidbody data
		void CalculateBodyData();

	private:
		//glm::quat orientation;	// The orientation of a rigidbody
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