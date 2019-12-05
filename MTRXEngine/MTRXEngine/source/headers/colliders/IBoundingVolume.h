#pragma once

namespace mtrx
{
	// TBD: Look at this infrastructure when architecting BVH
	/**
	 * Interface used to define a bounding volume that can be used in a Bounding volume Hierarchy
	 * @see mtrx::BVHNode
	 * PS: This infrastructure is being reworked
	 * 
	 */
	class IBoundingVolume
	{
	public:
		virtual float GetSize() = 0;
	};
}