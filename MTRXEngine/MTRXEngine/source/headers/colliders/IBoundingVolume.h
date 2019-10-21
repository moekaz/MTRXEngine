#pragma once

// TBD: Look at this infrastructure when architecting BVH
class IBoundingVolume
{
public:
	virtual float GetSize() = 0;
};