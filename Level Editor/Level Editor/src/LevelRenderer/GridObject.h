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
    GridObject();
    GridObject(std::string name_, std::string filePath_, bool isIntangible_, int size_);

    std::string getName() { return name; }
    std::string getFilePath() { return filePath; }
    bool getIsIntangible() { return isIntangible; }
    int getSize() { return size; }
    bool isObjectEmpty() { return isEmpty; }
    void erase() { isEmpty = true; }

    void resetSize() {}

protected:

private:

    std::string name;
    std::string filePath;
    bool isIntangible;
    int size;
    bool isEmpty;
};
