/*
*/

#pragma once

#include <colliders/BVHNode.h>
#include <../code/colliders/BVHNode.cpp>
#include <colliders/SphereCollider.h>

namespace mtrx
{
	/**
	 * @brief The collision detection system of the engine
	 * 
	 */
	class CollisionSystem
	{
	public:
		std::unordered_set<Collider*> colliders;

		/**
		 * @brief Construct a new Collision System object
		 * 
		 */
		CollisionSystem();
		~CollisionSystem();
	};
}
