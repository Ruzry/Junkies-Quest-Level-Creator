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
	
	void setGridSpace(GridObject object, int xCoord, int yCoord);
	std::vector<std::vector<GridObject>>* getLevelGrid(){ return &levelGrid; }
	void setupNewLevelGrid(int columns, int rows); //{ levelGrid.clear(); }
protected:

private:
	void renderGrid();
	void renderGridAssets();
	void populateLevelGrid(int rows, int columns);
	std::vector<std::vector<GridObject>> levelGrid = {};

	sf::RenderWindow* window_;
	WindowInfo* windowInfo_;
	std::map<std::string, sf::Texture>* textureMap = {};

	sf::Vector2f mousePosition;

	GridObject selectedAsset;
	bool isSelected = false;
	bool leftMousePressed = false;
	bool rightMousePressed = false;
	bool inGridBounds = false;

	int xOffset = 0;

	sf::RectangleShape selectionHighlight;
};
