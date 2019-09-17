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
		m_rbManager.PhysicsUpdate();
		m_pManager.PhysicsUpdate();
	}
}