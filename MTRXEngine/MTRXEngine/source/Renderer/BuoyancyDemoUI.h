#pragma once

#include <UIPanel.h>
#include <imgui/imgui.h>

class BuoyancyDemoUI : public UIPanel
{
public:
	float* linearDamping;
	float* liquidLevel;
	float* gravitationalAcceleration;
	float* liquidDensity;

	BuoyancyDemoUI(const char* panelName, const glm::vec2& dimensions, float* linearDamping, float* gravitationalAcceleration, float* liquidLevel, float* liquidDensity);
	~BuoyancyDemoUI() = default;

	void SetupPanelContent() override;
};