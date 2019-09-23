#include <PrecompiledHeader.h>
#include <ProjectileDemoUI.h>

ProjectileDemoUI::ProjectileDemoUI(const char* panelName, const glm::vec2& dimensions, int* projectile) : UIPanel(panelName, dimensions), projectile(projectile)
{}

ProjectileDemoUI::~ProjectileDemoUI()
{}

void ProjectileDemoUI::SetupPanelContent()
{
	const char* text = R"(Projectiles:

SPACE: To Fire Projectile
)";
	ImGui::Text(text);

	ImGui::RadioButton("Regular Projectile", projectile, 1);
	ImGui::RadioButton("Bullet projectile", projectile, 2);
	ImGui::RadioButton("Fireball projectile", projectile, 3);
	ImGui::RadioButton("Laser projectile", projectile, 4);
}
