#pragma once

#include "imgui.h"
#include <SFML/Graphics.hpp>
#include "../Menus/Toolbar.h"
#include "../LevelRenderer/LevelRenderer.h"

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
	void renderGrid();

	LevelRenderer levelRenderer = LevelRenderer();
	Toolbar toolbar = Toolbar();
	bool isActive = true;

	sf::RectangleShape leftToolbarSpace;
	sf::RectangleShape rightToolbarSpace;

	sf::View levelView;
	sf::View menuView;

	const float WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;
	const float CELL_SIZE = 16.0;
	
	const float TOOLBAR_WIDTH = WINDOW_WIDTH * 20.0 / 100;
	const float LEVEL_WIDTH = WINDOW_WIDTH - TOOLBAR_WIDTH;
	const float LEVEL_X_CENTER = TOOLBAR_WIDTH + (LEVEL_WIDTH / 2);

	const float ROWS = (WINDOW_WIDTH - TOOLBAR_WIDTH) / CELL_SIZE;
	const float COLUMNS = WINDOW_HEIGHT / CELL_SIZE;

};
