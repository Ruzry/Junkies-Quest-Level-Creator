#include "LevelRenderer.h"

LevelRenderer::LevelRenderer()
{
	window_ = nullptr;
	windowInfo_ = nullptr;
}

LevelRenderer::LevelRenderer(sf::RenderWindow* window, WindowInfo* windowInfo, std::map<std::string, sf::Texture>* map)
:	window_(window),
	windowInfo_(windowInfo),
	textureMap(map)
{
	initGrid();

	object = GridObject("Grass", "Assets/Basic/16x16 Grass Square.png", true, 16);
	object.setPosition(sf::Vector2f(0 + windowInfo_->getToolbarWidth(),0));

	selectionHighlight = sf::RectangleShape(sf::Vector2f(windowInfo_->getCellSize(), windowInfo_->getCellSize()));
	selectionHighlight.setFillColor(sf::Color::Transparent);
	selectionHighlight.setOutlineColor(sf::Color::White);
	selectionHighlight.setOutlineThickness(1.5f);
}

void LevelRenderer::update(float deltaTime, sf::Vector2f mousePos, bool selected, GridObject* asset)
{
	mousePosition = mousePos;

	bool xBound = ((mousePosition.x) < (windowInfo_->getLevelWidth() + windowInfo_->getToolbarWidth()) && mousePosition.x > (0 + windowInfo_->getToolbarWidth())) ? true : false;
	bool yBound = (mousePosition.y < windowInfo_->getWindowHeight() && mousePosition.y > 0) ? true : false;

	isSelected = (selected && xBound && yBound);

	float x_cellPos = floor(mousePosition.x - ((int)mousePosition.x % (int)windowInfo_->getCellSize()));
	float y_cellPos = floor(mousePosition.y - ((int)mousePosition.y % (int)windowInfo_->getCellSize()));

	int x_coord = (x_cellPos - windowInfo_->getToolbarWidth()) / (int)windowInfo_->getCellSize();
	int y_coord = y_cellPos / (int)windowInfo_->getCellSize();

	if (isSelected)
	{

		bool mousePressed = false;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << "Mouse Button Pressed ";
			mousePressed = true;
		}

		selectedAsset = GridObject(asset->getName(), asset->getFilePath(), asset->getIsIntangible(), asset->getSize());
		selectedAsset.setTexture(textureMap->at(asset->getName()));
		selectedAsset.setPosition(sf::Vector2f(mousePosition.x + 15, mousePosition.y + 15));

		selectionHighlight.setSize(sf::Vector2f(selectedAsset.getSize(), selectedAsset.getSize()));
		selectionHighlight.setPosition(sf::Vector2f(x_cellPos, y_cellPos));

		if (mousePressed)
		{
			GridObject levelAsset = GridObject(asset->getName(), asset->getFilePath(), asset->getIsIntangible(), asset->getSize());
			levelAsset.setPosition(sf::Vector2f(x_cellPos, y_cellPos));
			levelAsset.setTexture(textureMap->at(levelAsset.getName()));

			levelGrid[x_coord][y_coord] = levelAsset;
		}
	}
}

void LevelRenderer::render()
{
	renderGridAssets();
	renderGrid();

	if (isSelected)
		renderSelection();
}

void LevelRenderer::renderGrid()
{
	for (int i = 0; i < windowInfo_->getRows() + 1; i++)
	{
		float xPos = (windowInfo_->getToolbarWidth() + (i * windowInfo_->getCellSize()));
		sf::Vertex verticalLine[] = { {{xPos, 0}, sf::Color::Cyan}, {{xPos, windowInfo_->getWindowHeight()}, sf::Color::Cyan} };
		window_->draw(verticalLine, 2, sf::Lines);
	}

	for (int j = 0; j < windowInfo_->getColumns() + 1; j++)
	{
		float yPos = (j * windowInfo_->getCellSize());
		sf::Vertex horizontalLine[] = { {{windowInfo_->getToolbarWidth(), yPos}, sf::Color::Cyan}, {{windowInfo_->getWindowWidth(), yPos}, sf::Color::Cyan} };
		window_->draw(horizontalLine, 2, sf::Lines);
	}

	window_->draw(object);
}

void LevelRenderer::renderGridAssets()
{
	for (int i = 0; i < windowInfo_->getRows() + 1; i++)
	{
		for (int j = 0; j < windowInfo_->getColumns() + 1; j++)
		{
			window_->draw(levelGrid[i][j]);
		}
	}
}

void LevelRenderer::renderSelection()
{
	window_->draw(selectedAsset);
	window_->draw(selectionHighlight);
}

void LevelRenderer::initGrid()
{
	for (int i = 0; i < windowInfo_->getRows() + 1; i++)
	{
		std::vector<GridObject> assets = {};

		for (int j = 0; j < windowInfo_->getColumns() + 1; j++)
		{
			GridObject asset;
			assets.push_back(asset);
		}

		levelGrid.push_back(assets);
	}
}
