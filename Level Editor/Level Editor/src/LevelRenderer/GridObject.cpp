#include "GridObject.h"

GridObject::GridObject(std::string name_, std::string filePath_, bool isIntangible_, int size_)
{
	name = name_;
	filePath = filePath_;
	isIntangible = isIntangible_;
	size = size_;

	texture = new sf::Texture;

	texture->loadFromFile(filePath, sf::IntRect(0, 0, 16, 16));
	setTexture(*texture);

	//scale(sf::Vector2f(2.25f, 2.25f));//TEMP
}
