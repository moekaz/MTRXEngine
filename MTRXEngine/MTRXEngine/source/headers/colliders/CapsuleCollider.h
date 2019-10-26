#pragma once

#include <Defs.h>
#include <colliders/Collider.h>
#include <utils/RaycastCollisionUtil.h>
#include <colliders/IBoundingVolume.h>

namespace mtrx
{
	class CapsuleCollider : public Collider
	{
	public:
		glm::vec3 A;
		glm::vec3 B;

		//  TBD: Phase out the usage of transforms in these types of colliders
		CapsuleCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1), float radii = 0.5f, float height = 1.f);
		CapsuleCollider(const Transform& transform = Transform(), float radii = 0.5f, float height = 1.f);
		virtual ~CapsuleCollider() = default;

		virtual bool RaycastCollision(const Ray& ray) override { return RaycastCollisionUtil::RayCapsuleCollision(ray.startPosition, ray.direction, A, B, radii); }

		inline float GetRadii() const { return radii; }
		inline float GetHeight() const { return height; }		

		inline void SetRadii(float radius) 
		{
			radii = radius;
			transform.GetScale().x = radius * 2.f;
		}

		inline void SetHeight(float height)
		{
			this->height = height;
			transform.GetScale().y = height;
		}

		// WE ARE ONLY USING THE X AND Y VALUES OF THE SCALE FOR SCALING THE COLLIDER
		virtual inline void SetScale(const glm::vec3& scale) override
		{
			Collider::SetScale(scale);
			height = scale.y;
			radii = 0.5f * scale.x;
			A = GetPosition() - GetUp() * (height / 2);
			B = GetPosition() + GetUp() * (height / 2);
		}

		virtual inline void SetPosition(const glm::vec3& position) override
		{
			glm::vec3 difference = position - GetPosition();
			Collider::SetPosition(position);
			A += difference;
			B += difference;
		}

		virtual inline void SetOrientation(const glm::quat& orientation) override
		{
			Collider::SetOrientation(orientation);
			A = GetPosition() - GetUp() * (height / 2);
			B = GetPosition() + GetUp() * (height / 2);
		}

	private:
		float radii;
		float height;
	};
}