/*
	Author: mohamed kazma
	Description: Header file for a sphere collider
*/

#pragma once

#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>
#include <IBoundingVolume.h>

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

		SphereCollider(const glm::vec3& vec = glm::vec3(), float radius = 0.5);
		SphereCollider(const SphereCollider& collider1, const SphereCollider& collider2);
		~SphereCollider();

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;
		virtual float GetSize() override;
		float GetGrowth(const SphereCollider&);
	};
}