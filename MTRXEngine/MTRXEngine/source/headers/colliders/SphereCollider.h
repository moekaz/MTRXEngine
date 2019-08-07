/*
	Author: mohamed kazma
	Description: Header file for a sphere collider
*/

#pragma once

#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>
#include <IBoundingVolume.h>
#include <math/Transform.h>

namespace mtrx
{
	// Forward declarations
	class BoxCollider;
	class CapsulesCollider;
	class MeshCollider;

	class SphereCollider : public Collider, public IBoundingVolume
	{
	public:
		float radius;

		SphereCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1), float radius = 0.5);
		SphereCollider(const Transform& transform = Transform(), float radius = 0.5);
		SphereCollider(const SphereCollider& collider1, const SphereCollider& collider2);
		~SphereCollider();

		float GetGrowth(const SphereCollider&);

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;
		virtual float GetSize() override;

		virtual inline void SetScale(const glm::vec3& scale) override
		{
			// NOTE: ONLY THE X VALUE OF THE SCALE IS USED FOR UPDATING THE SPHERE COLLIDER
			Collider::SetScale(scale);
			radius = 0.5f * scale.x;
		}
	};
}