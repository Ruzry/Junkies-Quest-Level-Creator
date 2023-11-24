#pragma once

#include "imgui.h"
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>

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

	std::vector<std::string> assetTypeComboNames;
	int selectedIndex = 0;

	const std::string COMBO_TITLE = "Asset Types";
};
