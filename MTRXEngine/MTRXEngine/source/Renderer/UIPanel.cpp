#include <PrecompiledHeader.h>
#include <UIPanel.h>

UIPanel::UIPanel(const char* panelName, const glm::vec2& dimensions) :
	m_panelName(panelName), m_dimensions(dimensions)
{}

UIPanel::~UIPanel()
{}

void UIPanel::Render()
{
	ImGui::Begin(m_panelName.c_str(), nullptr, ImVec2(m_dimensions.x, m_dimensions.y));
	SetupPanelContent();
	ImGui::End();
}
