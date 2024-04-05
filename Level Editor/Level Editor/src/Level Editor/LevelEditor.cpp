#include "LevelEditor.h"

LevelEditor::LevelEditor(sf::RenderWindow* window)
{
	window_ = window;

	setupLayout();
}

void LevelEditor::update(float deltaTime)
{
	manageMenus();
}

void LevelEditor::render()
{
	window_->setView(levelView);

	levelRenderer.render(window_, &windowInfo);
}

void LevelEditor::setupLayout()
{
	menuView.setCenter(sf::Vector2f((windowInfo.getToolbarWidth() / 2), (windowInfo.getWindowHeight() / 2)));
	menuView.setSize(sf::Vector2f(windowInfo.getToolbarWidth(), windowInfo.getWindowHeight()));
	menuView.setViewport(sf::FloatRect(0.f, 0.f, 0.2f, 1.f));

	levelView.setCenter(sf::Vector2f(windowInfo.getLevelXCenter(), (windowInfo.getWindowHeight() / 2)));
	levelView.setSize(sf::Vector2f(windowInfo.getLevelWidth(), windowInfo.getWindowHeight()));
	levelView.setViewport(sf::FloatRect(0.2f, 0.f, 0.8f, 1.f));
	levelView.zoom(1.2f);
}

void LevelEditor::manageMenus()
{	
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(windowInfo.getToolbarWidth(), windowInfo.getWindowHeight()), ImGuiCond_FirstUseEver);

	ImGui::Begin("Asset Toolbar", &isActive, ImGuiWindowFlags_MenuBar);

	toolbar.fileMenu(&isActive);
	toolbar.AssetMenu(windowInfo.getToolbarWidth());

	isSelected = toolbar.isAssetSelected();
	if (isSelected)
		selectedAsset = toolbar.getSelectedAsset();

	ImGui::End();
}
