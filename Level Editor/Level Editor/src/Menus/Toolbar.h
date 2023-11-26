#pragma once

#include "imgui.h"
#include "imgui-SFML.h"
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include <SFML/Graphics.hpp>

struct Assets
{
	std::string name;
	std::string filePath;
	bool intangible;
	int size;

	sf::Texture texture;
};

class Toolbar
{
public:
	Toolbar();
	void update(float deltaTime);

	void fileMenu(bool* isActive);
	void AssetMenu(const float TOOLBAR_WIDTH);
protected:

private:
	void newFile();
	void open();
	void save();
	void exportLevel();

	void assetTypeCombo();
	void assetList(const float TOOLBAR_WIDTH);
	void assetProperties(const float TOOLBAR_WIDTH);
	void selectAsset(int ID);

	sf::Texture bushTexture;
	sf::Texture grassTexture;
	sf::Texture grass2Texture;
	sf::Texture blackTexture;
	sf::Texture redTexture;
	sf::Texture whiteTexture;

	std::vector<sf::Texture> textures;

	std::vector<std::string> assetTypeComboNames;
	int selectedIndex = 0;

	std::vector<std::vector<Assets>> assetTypes;
	std::vector<Assets> basicAssets;

	const std::string COMBO_TITLE = "Asset Types";
	const float LIST_BOX_HEIGHT = 500.f;
	const float LIST_BOX_X_OFFSET = 15.f;
	const float PROPERTIES_HEIGHT = 195.f;
};
