#pragma once

#include "imgui.h"
#include <../imgui/misc/cpp/imgui_stdlib.h>
#include <SFML/Graphics.hpp>
#include "../Menus/Toolbar.h"
#include "../LevelRenderer/LevelRenderer.h"
#include "WindowInfo.hpp"
#include "../LevelRenderer/GridObject.h"
#include <fstream>
#include <../nlohmann/json.hpp>

class LevelEditor
{
public:
	LevelEditor(sf::RenderWindow* window);

	void update(float deltaTime, sf::Vector2f mousePos);
	void render();
	void input(sf::Event* event, float dt);

protected:

private:
	sf::RenderWindow* window_;

	void loadConfig();
	void loadLevelFile(std::string levelFilepath);
	void setupLayout();
	void manageMenus();
	void fileMenu(bool* isActive);
	void newFile();
	void closeFilePopup();
	void save();

	LevelRenderer levelRenderer;
	Toolbar toolbar = Toolbar();
	bool isActive = true;

	sf::View levelView;
	sf::View menuView;

	WindowInfo windowInfo;

	bool isSelected = false;
	GridObject* selectedAsset;

	std::string lastLoadedLevel;

	bool newFilePopup = false;


};
