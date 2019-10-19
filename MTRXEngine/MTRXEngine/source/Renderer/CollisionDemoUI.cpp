#include "PrecompiledHeader.h"
#include "CollisionDemoUI.h"

CollisionDemoUI::CollisionDemoUI(const char* panelName, const glm::vec2& dimensions) : UIPanel(panelName, dimensions)
{}

void CollisionDemoUI::SetupPanelContent()
{
	const char* text = R"(This is a mini demo for a first person shooter
that allows us to shoot mini bullets at 
some boxes that have been randomly placed.
The box have physics box colliders and react
to collisions by applying a force on the
box at a the position of collision which
will result in an acceleration and torque

PRESS SPACE TO SHOOT SOME BULLETS...
)";

	ImGui::Text(text);
}
