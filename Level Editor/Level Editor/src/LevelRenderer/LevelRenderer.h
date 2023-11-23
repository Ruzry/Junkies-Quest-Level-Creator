#pragma once

//Libraries
#include <SFML/Graphics.hpp>
#include <vector>

//Classes
#include "GridObject.h"
#include "GridSpace.h"

class LevelRenderer
{
public:
	LevelRenderer();

	void update(float deltaTime);
	void render(sf::RenderWindow *window);

protected:

private:
	void renderGrid(sf::RenderWindow* window);
	std::vector<std::vector<GridObject>> levelGrid = {};


};
