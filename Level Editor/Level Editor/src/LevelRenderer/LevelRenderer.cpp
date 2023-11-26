#include "LevelRenderer.h"

LevelRenderer::LevelRenderer()
{
}

void LevelRenderer::update(float deltaTime)
{
}

void LevelRenderer::render(sf::RenderWindow* window, WindowInfo* windowInfo)
{
	renderGrid(window, windowInfo);
}

void LevelRenderer::renderGrid(sf::RenderWindow* window, WindowInfo* windowInfo)
{
	for (int i = 0; i < windowInfo->getRows() + 1; i++)
	{
		float xPos = (windowInfo->getToolbarWidth() + (i * windowInfo->getCellSize()));
		sf::Vertex verticalLine[] = { {{xPos, 0}, sf::Color::Cyan}, {{xPos, windowInfo->getWindowHeight()}, sf::Color::Cyan} };
		window->draw(verticalLine, 2, sf::Lines);
	}

	for (int j = 0; j < windowInfo->getColumns() + 1; j++)
	{
		float yPos = (j * windowInfo->getCellSize());
		sf::Vertex horizontalLine[] = { {{windowInfo->getToolbarWidth(), yPos}, sf::Color::Cyan}, {{windowInfo->getWindowWidth(), yPos}, sf::Color::Cyan} };
		window->draw(horizontalLine, 2, sf::Lines);
	}
}
