#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../LevelRenderer/GridObject.h"

class AssetGroup
{

public:
	AssetGroup(std::string comboTitle_, int amountOfObjects_);

	std::string getComboTitle() { return comboTitle; }
	std::vector<GridObject> getAssets() { return assets; }
	int getAmountOfObjects() { return amountOfObjects; }

	void setAssets(std::vector<GridObject> assets_) { assets = assets_; }
protected:

private:

	std::vector<GridObject> assets = {};
	std::string comboTitle;
	int amountOfObjects;

};

