/*
	Author: Mohamed Kazma
	Description: Capsule colliders
*/

#pragma once

#include <Defs.h>
#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>
#include <IBoundingVolume.h>

namespace mtrx
{
	class CapsuleCollider : public Collider, IBoundingVolume
	{
	public:
		float radii;
		glm::vec3 A;												
		glm::vec3 B;
		float height;

		CapsuleCollider(const glm::vec3& = glm::vec3(), float radii = 0.25f, float height = 0.5f);
		CapsuleCollider(const CapsuleCollider& collider1, const CapsuleCollider& collider2);
		~CapsuleCollider();

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;
		virtual float GetSize() override;
		float GetGrowth(const CapsuleCollider& capsuleCollider);
	};
}