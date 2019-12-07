#include "PrecompiledHeader.h"
#include "BuoyancyDemoUI.h"

BuoyancyDemoUI::BuoyancyDemoUI(const char* panelName, const glm::vec2& dimensions, float* linearDamping, float* gravitationalAcceleration, float* liquidLevel, float* liquidDensity) :
	UIPanel(panelName, dimensions), linearDamping(linearDamping), gravitationalAcceleration(gravitationalAcceleration), 
	liquidLevel(liquidLevel), liquidDensity(liquidDensity)
{}

void BuoyancyDemoUI::SetupPanelContent()
{
	const char* text = R"(Press SPACE To restart simulation
PS: Most Effects require restarting 
the simulation to work properly by pressing space

)";

	ImGui::Text(text);

	ImGui::Text("Linear Damping Body"); ImGui::SliderFloat("", linearDamping, 0.f, 1.f);
	ImGui::Text("Gravitational Acceleration"); ImGui::SliderFloat(" ", gravitationalAcceleration, -5.f, -15.f);
	ImGui::Text("Liquid Level"); ImGui::SliderFloat("  ", liquidLevel, -2.f, 2.f);
	ImGui::Text("Liquid Density"); ImGui::SliderFloat("   ", liquidDensity, 800.f, 1200.f);
}
