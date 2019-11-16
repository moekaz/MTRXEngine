
#pragma once

#include <UIPanel.h>
#include <Window.h>

class Window;

class UILayer
{
public:
	inline static void AddUIPanel(UIPanel* panel) { panels.push_back(panel); }

	static void Init(const Window* window);
	static void UpdateFrame();
	static void Render();
	static void Shutdown();

private:
	static std::vector<UIPanel*> panels;
};

