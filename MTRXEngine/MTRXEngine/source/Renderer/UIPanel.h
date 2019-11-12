
#pragma once

class UIPanel
{
public:
	UIPanel(const char* panelName, const glm::vec2& dimensions);
	~UIPanel();

	inline void SetDimensions(const glm::vec2& dimensions) { m_dimensions = dimensions; }
	inline void SetPanelName(const char* panelName) { m_panelName = panelName; }
	inline void SetPanelName(const std::string& panelName) { m_panelName = panelName; }

	void Render();
	virtual void SetupPanelContent() = 0;

private:
	std::string m_panelName;
	glm::vec2 m_dimensions;
};

