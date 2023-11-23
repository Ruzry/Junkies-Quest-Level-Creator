#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GridObject.h"

class GridObject;

/*
    Represents a space on the grid, wall collision will be 
*/
class GridSpace : 
    public sf::Sprite
{
public:
    GridSpace();
    GridSpace(const GridSpace& obj);

    

private:
    bool isAccessible = true;
    GridObject *objectInSpace;

protected:

};
