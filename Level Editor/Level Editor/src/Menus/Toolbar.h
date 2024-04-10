#pragma once

#include "imgui.h"
#include "imgui-SFML.h"
#include <fstream>
#include <../nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <SFML/Graphics.hpp>

#include "../Level Editor/AssetGroup.h"
#include "../LevelRenderer/GridObject.h"

using json = nlohmann::json;

class Toolbar
{
public:
	Toolbar();
	void update(float deltaTime);

	void fileMenu(bool* isActive);
	void AssetMenu(const float TOOLBAR_WIDTH);

	bool isAssetSelected() { return assetSelected; }
	std::map<std::string, sf::Texture>* getTextureMap() { return &textureMap; }
	GridObject* getSelectedAsset();

protected:

private:
	void newFile();
	void open();
	void save();
	void exportLevel();

	void loadAssetComboGroups();

	void assetTypeCombo();
	void assetList(const float TOOLBAR_WIDTH);
	void assetProperties(const float TOOLBAR_WIDTH);
	void selectAsset(int ID);

	GridObject *selectedAsset;
	std::vector<GridObject>* selectedGroup;
	std::vector<AssetGroup> assetGroups = {};

	int selectedGroupIndex = 0;
	bool assetSelected = false;

	const std::string COMBO_TITLE = "Asset Types";
	const float LIST_BOX_HEIGHT = 500.f;
	const float LIST_BOX_X_OFFSET = 15.f;
	const float PROPERTIES_HEIGHT = 195.f;

	std::map<std::string, sf::Texture> textureMap;
};
