#include "GridObject.h"

GridObject::GridObject(std::string name_, std::string filePath_, bool isIntangible_, int size_)
{
	name = name_;
	filePath = filePath_;
	isIntangible = isIntangible_;
	size = size_;

	texture.loadFromFile(filePath, sf::IntRect(0, 0, size, size));
}
