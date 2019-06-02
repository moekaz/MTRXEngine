/*
	Setting up a bounding volume hierarchy for broad phase collision detection
*/

#pragma once

#include <entities/Body.h>
#include <colliders/Collider.h>

namespace mtrx
{
	// Potential collision with bodies (dunno if we do this with bodies(particles and rigidbodies or just rigidbodies))
	struct PotentialCollision
	{
		Body* bodies[2];
	};

	template<class BoundingVolume>
	class BVHNode
	{
	public:
		BVHNode<BoundingVolume>* parent; // Parent node
		BVHNode<BoundingVolume>* children[2]; // Left and right children
		BoundingVolume volume; // The bounding volume used 
		Body* body; // Only leaves will have rigidbodies (we can use an unordered_map to get corresponding rigidbodies if we want)

		BVHNode();
		BVHNode(BVHNode<BoundingVolume>* parent, BoundingVolume& volume, Body* body = nullptr);
		~BVHNode();

		inline bool IsLeaf() { return !children[0] && !children[1]; }
		inline bool IsCollision(BVHNode<BoundingVolume>& other) { other.boundingVolume->CheckCollision(*other.volume); }
		inline bool DescendA(BVHNode<BoundingVolume>& a, BVHNode<BoundingVolume>& b) { return b.IsLeaf() || (!a.IsLeaf() && (a.volume.GetSize() >= b.volume.GetSize())); }

		void GetPotentialContacts(std::list<PotentialCollision>& potentialCollisions);
		void Insert(Body* body, Collider& collider);
		void RecalculateBoundingVolume();
	};
}
