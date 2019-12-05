#pragma once

#include <entities/Body.h>
#include <colliders/Collider.h>

namespace mtrx
{
	// Potential collision with bodies (dunno if we do this with bodies(particles and rigidbodies or just rigidbodies))
	/**
	 * @brief 
	 * 
	 */
	struct PotentialCollision
	{
		Body* bodies[2];
	};

	/**
	 * @brief 
	 * 
	 * @tparam BoundingVolume 
	 */
	template<class BoundingVolume>
	class BVHNode
	{
	public:
		BVHNode<BoundingVolume>* parent; // Parent node
		BVHNode<BoundingVolume>* children[2]; // Left and right children
		BoundingVolume volume; // The bounding volume used 
		Body* body; // Only leaves will have rigidbodies (we can use an unordered_map to get corresponding rigidbodies if we want)

		/**
		 * @brief Construct a new BVHNode object
		 * 
		 */
		BVHNode();

		/**
		 * @brief Construct a new BVHNode object
		 * 
		 * @param parent Parent of this node
		 * @param volume The bounding volume/collider used
		 * @param body The body that the BVHNode represents @see mtrx::Body 
		 */
		BVHNode(BVHNode<BoundingVolume>* parent, BoundingVolume& volume, Body* body = nullptr);
		
		/**
		 * @brief Destroy the BVHNode object
		 * 
		 */
		~BVHNode();

		/**
		 * @brief Check whether this node is a leaf
		 * 
		 * @return true This node is a leaf
		 * @return false This node is not a leaf and has at least one child
		 */
		inline bool IsLeaf() { return !children[0] && !children[1]; }
		
		/**
		 * @brief Check whether 2 nodes collide by checking that the bounding volumes collide
		 * 
		 * @param other The BVHNode that we want to check collision with
		 * @return true The 2 nodes collide
		 * @return false The 2 nodes do not collide
		 */
		inline bool IsCollision(BVHNode<BoundingVolume>& other) { other.boundingVolume->CheckCollision(*other.volume); }
		
		/**
		 * @brief Utility function that allows that helps with figuring out which direction
		 * in the structure we want to go down when trying to find potential contacts
		 * 
		 * @param a 
		 * @param b 
		 * @return true 
		 * @return false 
		 */
		inline bool DescendA(BVHNode<BoundingVolume>& a, BVHNode<BoundingVolume>& b) { return b.IsLeaf() || (!a.IsLeaf() && (a.volume.GetSize() >= b.volume.GetSize())); }

		/**
		 * @brief Get the Potential Contacts that could occur from the hierarchy
		 * 
		 * @param potentialCollisions Structure to store the potential collsions @see mtrx::PotentialCollision
		 */
		void GetPotentialContacts(std::list<PotentialCollision>& potentialCollisions);
		
		/**
		 * @brief Insert collider as a leaf of the stucture.
		 * We attempt to add it in a position in the tree where we would get the least amount of growth
		 * 
		 * @param body The body that we want to add
		 * @param collider The bounding volume that we want to add
		 */
		void Insert(Body* body, Collider& collider);

		/**
		 * @brief Recalculate the bounding volumes after the structure has been modified
		 * 
		 */
		void RecalculateBoundingVolume();
	};
}
