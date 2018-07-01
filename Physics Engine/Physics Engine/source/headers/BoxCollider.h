/*
	Author: Mohamed Kazma
	Description: An implementation of a box collider
*/

#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <iostream>

#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(const Vector3D& = Vector3D::zero);
	~BoxCollider();

	void Update();
	bool CheckCollision();

private:
protected:
};
#endif // BOXCOLLIDER_H
