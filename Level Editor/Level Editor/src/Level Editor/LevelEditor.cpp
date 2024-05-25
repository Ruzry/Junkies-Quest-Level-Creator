#include "LevelEditor.h"

LevelEditor::LevelEditor(sf::RenderWindow* window)
{
	window_ = window;

	loadConfig();
	loadLevelFile(lastLoadedLevel);
	setupLayout();
}

void LevelEditor::update(float deltaTime, sf::Vector2f mousePos)
{
	manageMenus();

	levelRenderer.update(deltaTime, mousePos, isSelected, selectedAsset);
}

void LevelEditor::render()
{
	window_->setView(levelView);
	levelRenderer.render();
}

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

void LevelEditor::loadConfig()
{
	std::ifstream f("src/config.json");
	json data = json::parse(f);

	lastLoadedLevel = data["last_opened_file"];
}

void LevelEditor::loadLevelFile(std::string levelFilepath)
{
	std::ifstream f(levelFilepath);
	json data = json::parse(f);

	std::string levelName = data["level_name"];
	int rows = data["level_cell_width"];
	int columns = data["level_cell_height"];

	windowInfo.calculateLevelInfo(rows, columns);
	levelRenderer = LevelRenderer(window_, &windowInfo, toolbar.getTextureMap());

	std::vector<GridObject> levelObjects = {};

	GridObject object;

	if (data["objects"] != NULL) {
		for (int i = 0; i < data["objects"].size(); i++)
		{
			object = GridObject(data["objects"].at(i)["name"],
				data["objects"].at(i)["filepath"], data["objects"].at(i)["intangible"],
				data["objects"].at(i)["size"]);
			levelRenderer.addAsset(object, data["objects"].at(i)["x_cell_position"],
				data["objects"].at(i)["y_cell_position"]);
		}
	}
}

void LevelEditor::setupLayout()
{
	menuView.setCenter(sf::Vector2f((windowInfo.getToolbarWidth() / 2), (windowInfo.getWindowHeight() / 2)));
	menuView.setSize(sf::Vector2f(windowInfo.getToolbarWidth(), windowInfo.getWindowHeight()));
	menuView.setViewport(sf::FloatRect(0.f, 0.f, 0.2f, 1.f));

	levelView.setCenter(sf::Vector2f(windowInfo.getLevelXCenter(), (windowInfo.getLevelHeight() / 2)));
	levelView.setSize(sf::Vector2f(windowInfo.getRendererWidth(), windowInfo.getWindowHeight()));
	levelView.setViewport(sf::FloatRect(0.2f, 0.f, 0.8f, 1.f));
	levelView.zoom(1.2f);
}

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

void LevelEditor::fileMenu(bool* isActive)
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "Ctrl+N")) 
				newFilePopup = true;

			if (ImGui::MenuItem("Open..", "Ctrl+O")) {}
				//open();

			if (ImGui::MenuItem("Recent..", "Ctrl+R")){}
				//open();

			if (ImGui::MenuItem("Save", "Ctrl+S"))
				save();

			if (ImGui::MenuItem("Export", "Ctrl+E")){}
				//exportLevel();

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
		ImGui::Text("Height:");
		static std::string bufHeight = "50";
		ImGui::InputText("Cells##1", &bufHeight, ImGuiInputTextFlags_CharsDecimal);

		ImGui::Text("Width:");
		static std::string bufWidth = "50";
		ImGui::InputText("Cells##2", &bufWidth, ImGuiInputTextFlags_CharsDecimal);

		ImGui::Text("Level name:");
		static char bufName[32] = "TestNewX";
		ImGui::InputText("##3", bufName, 32, ImGuiInputTextFlags_None);

		ImGui::Text("Filepath:");
		static char bufPath[32] = "Levels/TestNewX.json";
		ImGui::InputText("##4", bufPath, 32, ImGuiInputTextFlags_None);

		if (ImGui::Button("New"))
		{
			json newLevel;
			
			newLevel["level_cell_height"] = std::stoi(bufHeight);
			newLevel["level_cell_width"] = std::stoi(bufWidth);
			newLevel["level_name"] = bufName;
			newLevel["objects"] = json::array();

			std::ofstream ofile_newLevel(bufPath);
			ofile_newLevel << std::setw(4) << newLevel << std::endl;
			ofile_newLevel.close();

			loadLevelFile(bufPath);

			//Open config file
			std::ifstream f("src/config.json");
			json config = json::parse(f);
			f.close();
			//Alter config file contents
			config["last_opened_file"] = bufPath;
			lastLoadedLevel = bufPath;
			//Save file contents
			std::ofstream ofile_config("src/config.json");
			ofile_config << std::setw(4) << config << std::endl;
			ofile_config.close();

			closeFilePopup();
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel"))
			closeFilePopup();

		ImGui::EndPopup();
	}
}

void LevelEditor::closeFilePopup()
{
	ImGui::CloseCurrentPopup();
	newFilePopup = false;
}

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

			if (!columnIterator->isEmpty()) {

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
}
