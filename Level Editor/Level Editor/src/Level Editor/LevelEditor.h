#pragma once

#include "imgui.h"
#include <SFML/Graphics.hpp>
#include "../Menus/Toolbar.h"
#include "../LevelRenderer/LevelRenderer.h"
#include "WindowInfo.hpp"
#include "../LevelRenderer/GridObject.h"

class LevelEditor
{
public:
	LevelEditor(sf::RenderWindow* window);

	void update(float deltaTime);
	void render();

protected:

private:
	sf::RenderWindow* window_;

	void setupLayout();
	void manageMenus();

	LevelRenderer levelRenderer = LevelRenderer();
	Toolbar toolbar = Toolbar();
	bool isActive = true;

	sf::View levelView;
	sf::View menuView;

	WindowInfo windowInfo;

	bool isSelected = false;
	GridObject* selectedAsset;
};
