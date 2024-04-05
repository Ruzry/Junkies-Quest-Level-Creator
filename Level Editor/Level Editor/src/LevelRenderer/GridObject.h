#pragma once

#include <string>
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
    GridObject(std::string name_, std::string filePath_, bool isIntangible_, int size_);

    std::string getName() { return name; }
    std::string getFilePath() { return filePath; }
    bool getIsIntangible() { return isIntangible; }
    int getSize() { return size; }
    sf::Texture getTexture() { return *texture; }

protected:

private:

    std::string name;
    std::string filePath;
    bool isIntangible;
    int size;

    sf::Texture *texture;
    //std::vector<GridSpace> occupiedSpaces = {}; Not calculated til map placement

};
