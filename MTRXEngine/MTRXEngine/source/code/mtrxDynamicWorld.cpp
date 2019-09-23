#include <PrecompiledHeader.h>
#include <mtrxDynamicWorld.h>

namespace mtrx
{
	mtrxDynamicWorld::mtrxDynamicWorld()
	{}

	mtrxDynamicWorld::~mtrxDynamicWorld()
	{}

	void mtrxDynamicWorld::Update()
	{
		// Update deltaTime
		GameTime::Update();

		// Update the rigidbody manager
		m_rbManager.Integrate(GameTime::deltaTime);
	}
}