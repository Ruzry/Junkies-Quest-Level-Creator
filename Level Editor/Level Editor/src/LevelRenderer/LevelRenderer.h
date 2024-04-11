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
	void input(sf::Event* event, float dt);
	
protected:

private:
	void renderGrid();
	void renderGridAssets();
	void renderSelection();
	void initGridAssets();
	std::vector<std::vector<GridObject>> levelGrid = {};

	sf::RenderWindow* window_;
	WindowInfo* windowInfo_;
	std::map<std::string, sf::Texture>* textureMap = {};

	sf::Vector2f mousePosition;

	GridObject selectedAsset;
	bool isSelected = false;
	bool mousePressed = false;
	int xOffset;

	sf::RectangleShape selectionHighlight;
};
