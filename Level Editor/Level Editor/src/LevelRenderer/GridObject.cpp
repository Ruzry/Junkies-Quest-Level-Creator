#include "GridObject.h"

GridObject::GridObject()
{
}

GridObject::GridObject(std::string name_, std::string filePath_, bool isIntangible_, int size_)
{
	name = name_;
	filePath = filePath_;
	isIntangible = isIntangible_;
	size = size_;

	isEmpty_ = false;
}
