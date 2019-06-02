#include "PrecompiledHeader.h"
#include "colliders/BVHNode.h"

namespace mtrx
{
	template<class BoundingVolume>
	BVHNode<BoundingVolume>::BVHNode() : parent(nullptr), body(nullptr), volume(BoundingVolume())
	{}

	template<class BoundingVolume>
	BVHNode<BoundingVolume>::BVHNode(BVHNode* parent, BoundingVolume& collider, Body* body) : parent(parent), volume(collider), body(body)
	{}

	template<class BoundingVolume>
	BVHNode<BoundingVolume>::~BVHNode()
	{
		// CREATE A KILL FUNCTION AS WE DO NOT WANT TO RECURSE!!
		if (parent)
		{
			BVHNode<BoundingVolume>* sibling;
			if (parent->children[0] == this)
				sibling = parent->children[1];
			else
				sibling = parent->children[0];

			// Make the sibling the parent
			parent->boundingVolume = sibling->boundingVolume;
			parent->body = sibling->body;
			parent->children = sibling->children;
			
			// Delete the sibling
			sibling->boundingVolume = nullptr;
			sibling->body = nullptr;
			sibling->children = nullptr;
			delete sibling;

			// Recalculate the bounding volume of the parent
			parent->RecalculateBoundingVolume();
		}

		// This is recursive unfortunately as deletes will call children's destructors
		for (int i = 0; i < 2; ++i)
		{
			if (!children[i])
				continue;

			children[i]->parent = nullptr;
			delete children[i];
		}
	}

	template<class BoundingVolume>
	void BVHNode<BoundingVolume>::GetPotentialContacts(std::list<PotentialCollision>& potentialCollisions)
	{
		if (IsLeaf())
			return;

		std::stack<std::pair<BVHNode<BoundingVolume>*, BVHNode<BoundingVolume>*>> stack;
		BVHNode<BoundingVolume>* a = children[0];
		BVHNode<BoundingVolume>* b = children[1];

		while (true)
		{
			if (a && b && a->IsCollision(b))
			{
				if (a->IsLeaf() && b->IsLeaf())
				{
					// We have a potential contact add it as a potential contact
					PotentialCollision potentialCollision;
					potentialCollision.bodies = { a->body, b->body };
					potentialCollisions.push_back(potentialCollision);
				}
				else
				{
					// Check in which direction we want to traverse
					if (DescendA(*a, *b))
					{
						stack.push(std::pair<BVHNode<BoundingVolume>*, BVHNode<BoundingVolume>*>(a->children[1], b));
						a = a->children[0];
						continue;
					}
					else
					{
						stack.push(std::pair<BVHNode<BoundingVolume>*, BVHNode<BoundingVolume>*>(a, b->children[1]));
						b = b->children[0];
						continue;
					}
				}
			}

			if (stack.isEmpty())
				break;

			auto pair = stack.peek();
			a = pair.first;
			b = pair.second;
			stack.pop();
		}
	}

	template<class BoundingVolume>
	void BVHNode<BoundingVolume>::Insert(Body* body, Collider& collider)
	{
		// Inserting a new BVH into the hierarchy
		BVHNode* currentNode = this;
		while (!currentNode->IsLeaf())
		{
			// we would go in the direction with the least growth
			if (children[0]->boundingVolume->GetGrowth(collider) < children[1]->boundingVolume->GetGrowth(collider))
				currentNode = children[0];
			else
				currentNode = children[1];
		}

		currentNode->children[0] = new BVHNode(currentNode, volume, currentNode->body);
		currentNode->children[1] = new BVHNode(currentNode, &collider, body);
		currentNode->body = nullptr;
		
		// Recalculate bounding volume
		RecalculateBoundingVolume();
	}

	template<class BoundingVolume>
	void BVHNode<BoundingVolume>::RecalculateBoundingVolume()
	{
		// Rebuild the bounding volume
		if (IsLeaf())
			return;

		BVHNode* currentNode = this;
		while (currentNode)
		{
			currentNode->boundingVolume = BoundingVolume(currentNode->children[0]->boundingVolume, currentNode->children[1]->boundingVolume);
			currentNode = currentNode->parent; // Go up the tree
		}
	}
}