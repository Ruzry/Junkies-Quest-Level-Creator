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
	std::vector<GridObject>* getAssets_() { return &assets;  }
	GridObject* getAsset_(int index) { return &assets[index]; }
	void setAssets(std::vector<GridObject> assets_) { assets = assets_; }

	int getAmountOfObjects() { return amountOfObjects; }

protected:

private:

	std::vector<GridObject> assets = {};
	std::string comboTitle;
	int amountOfObjects;

};

