#pragma once

//Libraries
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
//Classes
#include "GridObject.h"
#include "GridSpace.h"
#include "../Level Editor/WindowInfo.hpp"

class LevelRenderer
{
public:
	LevelRenderer();
	LevelRenderer(sf::RenderWindow* window, WindowInfo* windowInfo, std::map<std::string, sf::Texture>* map);

	void update(float deltaTime, sf::Vector2f mousePos, bool selected, GridObject* asset);
	void render();

protected:

private:
	void renderGrid();
	void renderGridAssets();
	void renderSelection();
	void initGrid();
	std::vector<std::vector<GridObject>> levelGrid = {};

	sf::RenderWindow* window_;
	WindowInfo* windowInfo_;
	std::map<std::string, sf::Texture>* textureMap = {};

	GridObject object;

	sf::Vector2f mousePosition;

	GridObject selectedAsset;
	bool isSelected = false;

	sf::RectangleShape selectionHighlight;
};
