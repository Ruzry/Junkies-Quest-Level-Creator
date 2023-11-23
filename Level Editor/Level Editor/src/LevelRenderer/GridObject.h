#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GridSpace.h"

class GridSpace;

/*
    Grid Object represents a textured sprite that can be drawn, can take up multiple GridSpaces
*/
class GridObject : 
    public sf::Sprite
{
public:
    GridObject();
protected:

private:
    std::vector<GridSpace> occupiedSpaces = {};

};
