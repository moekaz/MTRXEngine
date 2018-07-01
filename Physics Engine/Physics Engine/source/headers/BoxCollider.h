/*
	Author: Mohamed Kazma
	Description: An implementation of a box collider
*/

#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider();
	~BoxCollider();

	void Update();
	bool CheckCollision();

private:
protected:
};
#endif // BOXCOLLIDER_H
