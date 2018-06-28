/*
	Author: Mohamed Kazma
	Description: An implementation of a box collider
*/

#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"

class BoxCollider : Collider
{
public:
	BoxCollider();
	~BoxCollider();

	void Update();
	bool CheckCollision();
	
	void CollisionEnter();
	void CollisionStay();
	void CollisionExit();

private:
protected:
};
#endif // BOXCOLLIDER_H
