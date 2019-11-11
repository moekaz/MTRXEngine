#pragma once

#include <UIPanel.h>
#include <imgui/imgui.h>

class CollisionDemoUI : public UIPanel
{
public:
	CollisionDemoUI(const char* panelName, const glm::vec2& dimensions);
	~CollisionDemoUI() = default;

	void SetupPanelContent() override;
};