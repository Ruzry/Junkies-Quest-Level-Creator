#include "LevelEditor.h"

LevelEditor::LevelEditor(sf::RenderWindow* window)
{
	window_ = window;

	loadConfig();
	loadLevelFile();
	levelRenderer = LevelRenderer(window, &windowInfo, toolbar.getTextureMap());
	setupLayout();
}

void LevelEditor::update(float deltaTime, sf::Vector2f mousePos)
{
	manageMenus();

	levelRenderer.update(deltaTime, mousePos, isSelected, selectedAsset);
}

void LevelEditor::render()
{
	window_->setView(levelView);
	levelRenderer.render();
}

void LevelEditor::input(sf::Event* event, float dt)
{
	if (event->type == sf::Event::MouseWheelScrolled)
	{
		if (event->mouseWheelScroll.delta == 1)
			levelView.zoom(0.9);
		else if (event->mouseWheelScroll.delta == -1)
			levelView.zoom(1.1);
	}

	levelRenderer.input(event, dt);
}

void LevelEditor::loadConfig()
{
	std::ifstream f("src/config.json");
	json data = json::parse(f);

	lastLoadedLevel = data["last_opened_file"];
}

void LevelEditor::loadLevelFile()
{
	std::ifstream f(lastLoadedLevel);
	json data = json::parse(f);

	std::string levelName = data["level_name"];
	int rows = data["level_cell_width"];
	int columns = data["level_cell_height"];

	windowInfo.calculateLevelInfo(rows, columns);
}

void LevelEditor::setupLayout()
{
	menuView.setCenter(sf::Vector2f((windowInfo.getToolbarWidth() / 2), (windowInfo.getWindowHeight() / 2)));
	menuView.setSize(sf::Vector2f(windowInfo.getToolbarWidth(), windowInfo.getWindowHeight()));
	menuView.setViewport(sf::FloatRect(0.f, 0.f, 0.2f, 1.f));

	levelView.setCenter(sf::Vector2f(windowInfo.getLevelXCenter(), (windowInfo.getLevelHeight() / 2)));
	levelView.setSize(sf::Vector2f(windowInfo.getRendererWidth(), windowInfo.getWindowHeight()));
	levelView.setViewport(sf::FloatRect(0.2f, 0.f, 0.8f, 1.f));
	levelView.zoom(1.2f);
}

void LevelEditor::manageMenus()
{	
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(windowInfo.getToolbarWidth(), windowInfo.getWindowHeight()), ImGuiCond_FirstUseEver);

	ImGui::Begin("Asset Toolbar", &isActive, ImGuiWindowFlags_MenuBar);

	fileMenu(&isActive);
	toolbar.AssetMenu(windowInfo.getToolbarWidth());

	isSelected = toolbar.isAssetSelected();
	if (isSelected)
		selectedAsset = toolbar.getSelectedAsset();

	ImGui::End();
}

void LevelEditor::fileMenu(bool* isActive)
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "Ctrl+N")){}
				//newFile();

			if (ImGui::MenuItem("Open..", "Ctrl+O")){}
				//open();

			if (ImGui::MenuItem("Save", "Ctrl+S")){}
				//save();

			if (ImGui::MenuItem("Export", "Ctrl+E")){}
				//exportLevel();

			if (ImGui::MenuItem("Close", "Ctrl+W"))
				*isActive = false;

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}
