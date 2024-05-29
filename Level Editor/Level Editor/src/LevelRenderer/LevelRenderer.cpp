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
	xOffset = windowInfo_->getToolbarWidth();

	selectionHighlight = sf::RectangleShape(sf::Vector2f(windowInfo_->getCellSize(), windowInfo_->getCellSize()));
	selectionHighlight.setFillColor(sf::Color::Transparent);
	selectionHighlight.setOutlineColor(sf::Color::White);
	selectionHighlight.setOutlineThickness(1.5f);
}

void LevelRenderer::update(float deltaTime, sf::Vector2f mousePos, bool selected, GridObject* asset)
{
	mousePosition = mousePos;

	bool xBound = ((mousePosition.x) < (windowInfo_->getLevelWidth() + xOffset)
		&& mousePosition.x > xOffset) ? true : false;
	bool yBound = (mousePosition.y < windowInfo_->getLevelHeight() && mousePosition.y > 0)
		? true : false;

	inGridBounds = (xBound && yBound);
	isSelected = (selected && inGridBounds);

	float x_cellPos = floor(mousePosition.x - ((int)mousePosition.x %
		(int)windowInfo_->getCellSize()));
	float y_cellPos = floor(mousePosition.y - ((int)mousePosition.y %
		(int)windowInfo_->getCellSize()));

	int x_coord = (x_cellPos - xOffset) / (int)windowInfo_->getCellSize();
	int y_coord = y_cellPos / (int)windowInfo_->getCellSize();

	if (inGridBounds) 
	{
		int highlighSize = isSelected ? selectedAsset.getSize() : (int)windowInfo_->getCellSize();
		selectionHighlight.setSize(sf::Vector2f(highlighSize, highlighSize));
		selectionHighlight.setPosition(sf::Vector2f(x_cellPos, y_cellPos));
	}

	if (isSelected)
	{
		selectedAsset = GridObject(asset->getName(), asset->getFilePath(),
			asset->getIsIntangible(), asset->getSize());
		selectedAsset.setTexture(textureMap->at(asset->getName()));
		selectedAsset.setPosition(sf::Vector2f(mousePosition.x + 15, mousePosition.y + 15));

		if (leftMousePressed)
		{
			GridObject levelAsset = GridObject(asset->getName(), asset->getFilePath(),
				asset->getIsIntangible(), asset->getSize());
			levelAsset.setPosition(sf::Vector2f(x_cellPos, y_cellPos));
			levelAsset.setTexture(textureMap->at(levelAsset.getName()));

			levelGrid[x_coord][y_coord] = levelAsset;
		}
	}

	if (rightMousePressed)
		if (inGridBounds)
			levelGrid[x_coord][y_coord].erase();
}

void LevelRenderer::render()
{
	renderGrid();
	renderGridAssets();

	if (isSelected)
		window_->draw(selectedAsset);

	window_->draw(selectionHighlight);
}

void LevelRenderer::input(sf::Event* event, float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		leftMousePressed = true;
	else
		leftMousePressed = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		rightMousePressed = true;
	else
		rightMousePressed = false;
}

void LevelRenderer::setGridSpace(GridObject object, int xCoord, int yCoord)
{
	levelGrid[xCoord][yCoord] = object; 
	levelGrid[xCoord][yCoord].setTexture(textureMap->at(object.getName()));
	levelGrid[xCoord][yCoord].setPosition(sf::Vector2f((xOffset + (xCoord * windowInfo_->getCellSize())), (yCoord * windowInfo_->getCellSize())));
}

void LevelRenderer::setupNewLevelGrid(int rows, int columns)
{
	levelGrid.clear();
	populateLevelGrid(rows, columns);
}

void LevelRenderer::renderGrid()
{
	for (int i = 0; i < levelGrid.size() + 1; i++)
	{
		float xPos = (xOffset + (i * windowInfo_->getCellSize()));
		sf::Vertex verticalLine[] = {{{xPos, 0}, sf::Color::Cyan},
			{{xPos, windowInfo_->getLevelHeight()}, sf::Color::Cyan}};

		window_->draw(verticalLine, 2, sf::Lines);
	}

	for (int j = 0; j < levelGrid[0].size() + 1; j++)
	{
		float yPos = (j * windowInfo_->getCellSize());
		sf::Vertex horizontalLine[] = {{{(float)xOffset, yPos}, sf::Color::Cyan},
			{{(windowInfo_->getLevelWidth() + xOffset), yPos}, sf::Color::Cyan}};

		window_->draw(horizontalLine, 2, sf::Lines);
	}
}

void LevelRenderer::renderGridAssets()
{
	for (int i = 0; i < levelGrid.size(); i++)
	{
		for (int j = 0; j < levelGrid[i].size(); j++)
		{
			if (!levelGrid[i][j].isObjectEmpty())
				window_->draw(levelGrid[i][j]);
		}
	}
}

/*
* Populates the levelGrid vector with empty GridObjects 
* (empty as in an initialzed GridObject but empty rendering information)
* IMPORTANT: When looping through the level grid, columns then rows!
*/
void LevelRenderer::populateLevelGrid(int rows, int columns)
{
	for (int i = 0; i < columns; i++)
	{
		std::vector<GridObject> assets = {};

		for (int j = 0; j < rows; j++)
		{
			GridObject emptyAsset;
			assets.push_back(emptyAsset);
		}

		levelGrid.push_back(assets);
	}
}
