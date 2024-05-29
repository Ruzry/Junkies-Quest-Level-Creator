#include "LevelEditor.h"

LevelEditor::LevelEditor(sf::RenderWindow* window)
{
	window_ = window;

	levelRenderer = LevelRenderer(window_, &windowInfo, toolbar.getTextureMap());

	loadLevelFile(loadConfig());
	setupLayout();
}

void LevelEditor::update(float deltaTime, sf::Vector2f mousePos)
{
	manageMenus();

	levelRenderer.update(deltaTime, mousePos, isSelected, selectedAsset);
}

/*
* Method to group render functionality.
* Called every frame.
*/
void LevelEditor::render()
{
	window_->setView(levelView);
	levelRenderer.render();
}

/*
* Manages input for the LevelRenderer
* TODO Look at moving LevelRenderer functionality into the LevelRenderer class.
*/
void LevelEditor::input(sf::Event* event, float dt)
{
	if (event->type == sf::Event::MouseWheelScrolled)
	{
		if (event->mouseWheelScroll.delta == 1)
			levelView.zoom(0.9);
		else if (event->mouseWheelScroll.delta == -1)
			levelView.zoom(1.1);
	}

	levelRenderer.input(event, dt);
}

std::string LevelEditor::loadConfig()
{
	std::ifstream f("src/config.json");
	json configData = json::parse(f);

	for (int i = 0; i < configData["recent_files"].size(); i++)
	{
		std::string filePath = configData["recent_files"][i];

		recentFiles.push_back(filePath);
	}

	return configData["last_opened_file"];
}

/*
* Saves changes to the local config information to file.
*/
void LevelEditor::saveConfig()
{
	std::ifstream f("src/config.json");
	json configData = json::parse(f);
	f.close();

	configData["last_opened_file"] = lastLoadedLevel;
	configData["recent_files"].clear();

	for (int i = 0; i < recentFiles.size(); i++)
		configData["recent_files"].push_back(recentFiles[i]);

	std::ofstream ofile("src/config.json");
	ofile << std::setw(4) << configData << std::endl;
	ofile.close();

}

/*
* Updates the RecentFiles vector, adding the previous loaded filepath and 
* removing the currently loaded one from the container.
* Does checks to ensure filepath to be removed exists.
* Does checks to ensure filepath to be added doesnt already exist.
* @param stf::string for the previous loaded file path, "" on load.
* @param std::string for the new filepath being loaded.
*/
void LevelEditor::updateRecentFiles(std::string oldFilepath, std::string newFilepath)
{
	bool pathNeedsRemoved = false;
	bool pathExists = false;

	std::vector<std::string>::iterator removalIndex;

	for (std::vector<std::string>::iterator path = recentFiles.begin(); path != recentFiles.end(); ++path)
	{
		if (*path == oldFilepath)
			pathExists = true;

		if (*path == newFilepath)
		{
			pathNeedsRemoved = true;
			removalIndex = path;
		}
	}

	if (pathNeedsRemoved)
		recentFiles.erase(removalIndex);

	if (!pathExists && oldFilepath != "")
		recentFiles.push_back(oldFilepath);

}

/*
* Loads a level into the Level Renderer from file.
* @param std::string containing the filepath of the level to be loaded.
*/
void LevelEditor::loadLevelFile(std::string levelFilepath)
{
	std::ifstream f(levelFilepath);
	json data = json::parse(f);

	std::string levelName = data["level_name"];
	int rows = data["level_cell_width"];
	int columns = data["level_cell_height"];

	windowInfo.calculateLevelInfo(rows, columns);
	levelRenderer.setupNewLevelGrid(rows, columns);

	GridObject object;

	if (data["objects"] != NULL) {
		for (int i = 0; i < data["objects"].size(); i++)
		{
			object = GridObject(data["objects"].at(i)["name"],
				data["objects"].at(i)["filepath"], data["objects"].at(i)["intangible"],
				data["objects"].at(i)["size"]);
			levelRenderer.setGridSpace(object, data["objects"].at(i)["x_cell_position"],
				data["objects"].at(i)["y_cell_position"]);
		}
	}

	updateRecentFiles(lastLoadedLevel, levelFilepath);
	lastLoadedLevel = levelFilepath;
	saveConfig();
	levelView.setCenter(sf::Vector2f(windowInfo.getLevelXCenter(), (windowInfo.getLevelHeight() / 2)));

}

/*
* Sets up SFML Views for Toolbar and Level Renderer.
*/
void LevelEditor::setupLayout()
{
	menuView.setCenter(sf::Vector2f((windowInfo.getToolbarWidth() / 2), (windowInfo.getWindowHeight() / 2)));
	menuView.setSize(sf::Vector2f(windowInfo.getToolbarWidth(), windowInfo.getWindowHeight()));
	menuView.setViewport(sf::FloatRect(0.f, 0.f, 0.2f, 1.f));

	levelView.setSize(sf::Vector2f(windowInfo.getRendererWidth(), windowInfo.getWindowHeight()));
	levelView.setViewport(sf::FloatRect(0.2f, 0.f, 0.8f, 1.f));
	levelView.zoom(1.2f);
}

/*
* Called on update to display Asset Toolbar and its components.
*/
void LevelEditor::manageMenus()
{	
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(windowInfo.getToolbarWidth(), windowInfo.getWindowHeight()), ImGuiCond_FirstUseEver);

	ImGui::Begin("Asset Toolbar", &isActive, ImGuiWindowFlags_MenuBar);

	fileMenu(&isActive);
	toolbar.AssetMenu(windowInfo.getToolbarWidth());

	isSelected = toolbar.isAssetSelected();
	if (isSelected)
		selectedAsset = toolbar.getSelectedAsset();

	ImGui::End();
}

/*
* Displays the file menu with selectable options.
*/
void LevelEditor::fileMenu(bool* isActive)
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "Ctrl+N")) 
				newFilePopup = true;

			//if (ImGui::MenuItem("Open..", "Ctrl+O")) { //open(); }
				
			if (ImGui::BeginMenu("Recent"))
				showRecentFileMenu();

			if (ImGui::MenuItem("Save", "Ctrl+S"))
				save();

			if (ImGui::MenuItem("Close", "Ctrl+W"))
				*isActive = false;

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();		
	}

	if (newFilePopup)
		newFile();
}

/*
* Opens a popup window with input boxes requiring the information needed to create a new level.
* Height/Width: how many cells tall/wide the grid should be.
* FileName: Name of the file. Filepath: Location of the file.
* A new level file is created and loaded into the Level Renderer.
* It also opens the config file and updates relavent loaded level variables
* TODO Input Validation/CleanUp.
*/
void LevelEditor::newFile()
{
	ImGui::OpenPopup("New File Input");

	ImGui::SetNextWindowSize(ImVec2(250, 275));

	if (ImGui::BeginPopupModal("New File Input"))
	{
		bool closePopup = false;

		ImGui::Text("Height:");
		static std::string heightInput = "50";
		ImGui::InputText("Cells##1", &heightInput, ImGuiInputTextFlags_CharsDecimal);

		ImGui::Text("Width:");
		static std::string widthInput = "50";
		ImGui::InputText("Cells##2", &widthInput, ImGuiInputTextFlags_CharsDecimal);

		ImGui::Text("Level name:");
		static char nameInput[32] = "TestNewX";
		ImGui::InputText("##3", nameInput, 32, ImGuiInputTextFlags_None);

		ImGui::Text("Filepath:");
		static char pathInput[32] = "Levels/TestNewX.json";
		ImGui::InputText("##4", pathInput, 32, ImGuiInputTextFlags_None);

		if (ImGui::Button("New"))
		{
			json newLevel;
			
			newLevel["level_cell_height"] = std::stoi(heightInput);
			newLevel["level_cell_width"] = std::stoi(widthInput);
			newLevel["level_name"] = nameInput;
			newLevel["objects"] = json::array();

			std::ofstream ofile_newLevel(pathInput);
			ofile_newLevel << std::setw(4) << newLevel << std::endl;
			ofile_newLevel.close();

			loadLevelFile(pathInput);

			closePopup = true;
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel"))
			closePopup = true;

		if (closePopup)
		{
			ImGui::CloseCurrentPopup();
			newFilePopup = false;
		}

		ImGui::EndPopup();
	}
}

/*
* Shows the File Menu Recent Files tab
* Loops through the recentFiles vector and lists the contents
* as buttons.
*/
void LevelEditor::showRecentFileMenu()
{
	for (int i = 0; i < recentFiles.size(); i++) 
		if (ImGui::MenuItem(recentFiles[i].c_str()))
			loadLevelFile(recentFiles[i]);

	ImGui::EndMenu();
}

/*
* Saves LevelGrid changes to the opened file and saves config information to config file.
* Clears the json container for game objects and saves the contents of the LevelGrid into its place.
*/
void LevelEditor::save()
{
	std::vector<std::vector<GridObject>>* levelGrid = levelRenderer.getLevelGrid();

	std::ifstream f(lastLoadedLevel);
	json data = json::parse(f);

	data["objects"].clear();

	std::vector<std::vector<GridObject>>::iterator rowIterator;
	std::vector<GridObject>::iterator columnIterator;

	for (rowIterator = levelGrid->begin(); rowIterator != levelGrid->end(); rowIterator++) {
		for (columnIterator = rowIterator->begin(); columnIterator != rowIterator->end(); columnIterator++) {

			if (!columnIterator->isObjectEmpty()) {

				int xCell = (int)((columnIterator->getPosition().x - windowInfo.getToolbarWidth())
					/ windowInfo.getCellSize());
				int yCell = (int)(columnIterator->getPosition().y / windowInfo.getCellSize());

				data["objects"].push_back({
					{"name", columnIterator->getName()},
					{"filepath",columnIterator->getFilePath()},
					{"intangible", columnIterator->getIsIntangible()},
					{"size", columnIterator->getSize()},
					{"x_cell_position", xCell},
					{"y_cell_position", yCell}});
			}
		}
	}

	std::ofstream ofile(lastLoadedLevel);
	ofile << std::setw(4) << data << std::endl;

	saveConfig();
}
