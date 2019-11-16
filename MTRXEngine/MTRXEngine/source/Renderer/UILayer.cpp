#include "PrecompiledHeader.h"
#include "UILayer.h"

std::vector<UIPanel*> UILayer::panels;

void UILayer::Init(const Window* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), false);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();
	UpdateFrame(); // Create a frame
}

void UILayer::UpdateFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UILayer::Render()
{
	// Call the render setup on all the UIPanels
	for (auto iter = panels.begin(); iter != panels.end(); ++iter)
	{
		(*iter)->Render();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UILayer::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
