#pragma once

//Libraries
#include <SFML/Graphics.hpp>
#include <vector>

//Classes
#include "GridObject.h"
#include "GridSpace.h"
#include "../Level Editor/WindowInfo.hpp"

class LevelRenderer
{
public:
	LevelRenderer();

	void update(float deltaTime);
	void render(sf::RenderWindow *window, WindowInfo* windowInfo);

protected:

private:
	void renderGrid(sf::RenderWindow* window, WindowInfo* windowInfo);
	std::vector<std::vector<GridObject>> levelGrid = {};


};
