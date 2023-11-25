#pragma once

#include "imgui.h"
#include "imgui-SFML.h"
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include <SFML/Graphics.hpp>

class Toolbar
{
public:
	Toolbar();
	void update(float deltaTime);

	void fileMenu(bool* isActive);
	void AssetMenu();
protected:

private:
	void newFile();
	void open();
	void save();
	void exportLevel();
	void assetTypeCombo();
	void assetGrid();

	sf::Texture bushTexture;
	sf::Texture grassTexture;
	sf::Texture grass2Texture;
	sf::Texture blackTexture;
	sf::Texture redTexture;
	sf::Texture whiteTexture;

	std::vector<sf::Texture> textures;

	std::vector<std::string> assetTypeComboNames;
	int selectedIndex = 0;

	const std::string COMBO_TITLE = "Asset Types";
};
