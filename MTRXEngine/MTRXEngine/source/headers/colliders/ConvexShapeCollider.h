/*
	Author: Mohamed Kazma
	Description: Colliders with a convex shape (GJK is what is being used for collision detection)
*/

#pragma once

#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>
#include <math/Transform.h>

namespace mtrx
{
	class ConvexShapeCollider : public Collider
	{
	public:
		std::vector<glm::vec3*> vertices;

		ConvexShapeCollider(const ColliderType& colliderType = ColliderType::ConvexShape, const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1));
		ConvexShapeCollider(const ColliderType& colliderType = ColliderType::ConvexShape, const Transform& transform = Transform());
		virtual ~ConvexShapeCollider();

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;

		// Vertices and model matrices
		std::vector<glm::vec3*>* GetVertices() const;
		glm::mat4 GetModelMatrix() const;

		// Used for GJK minkowski sum calculations
		glm::vec3 Support(const ConvexShapeCollider&, const glm::vec3&) const;
		glm::vec3& FarthestPointInDirection(const glm::vec3&) const;

		virtual inline void SetPosition(const glm::vec3& pos) override { Collider::SetPosition(pos); transformModified = true; }
		virtual inline void SetScale(const glm::vec3& scale) override { Collider::SetScale(scale); transformModified = true; }
		virtual inline void SetOrientation(const glm::quat& quat) override { Collider::SetOrientation(quat); transformModified = true; }

	protected:
		mutable std::vector<glm::vec3*> transformedVertices;
		mutable bool transformModified;
	};
}