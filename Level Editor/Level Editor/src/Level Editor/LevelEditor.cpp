#include "LevelEditor.h"

LevelEditor::LevelEditor(sf::RenderWindow* window)
{
	window_ = window;

	setupLayout();
}

void LevelEditor::update(float deltaTime)
{
	manageMenus();
}

void LevelEditor::render()
{
	window_->setView(levelView);

	//levelRenderer.render(window_);
	renderGrid();
}

void LevelEditor::setupLayout()
{
	menuView.setCenter(sf::Vector2f((TOOLBAR_WIDTH / 2), (WINDOW_HEIGHT / 2)));
	menuView.setSize(sf::Vector2f(TOOLBAR_WIDTH, WINDOW_HEIGHT));
	menuView.setViewport(sf::FloatRect(0.f, 0.f, 0.2f, 1.f));

	levelView.setCenter(sf::Vector2f(LEVEL_X_CENTER, (WINDOW_HEIGHT / 2)));
	levelView.setSize(sf::Vector2f(LEVEL_WIDTH, WINDOW_HEIGHT));
	levelView.setViewport(sf::FloatRect(0.2f, 0.f, 0.8f, 1.f));
	levelView.zoom(1.2f);

	leftToolbarSpace.setFillColor(sf::Color(210, 215, 211));
	leftToolbarSpace.setSize(sf::Vector2f(TOOLBAR_WIDTH, WINDOW_HEIGHT));
	leftToolbarSpace.setPosition(0, 0);

}

void LevelEditor::manageMenus()
{	
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(TOOLBAR_WIDTH, WINDOW_HEIGHT), ImGuiCond_FirstUseEver);

	ImGui::Begin("Asset Toolbar", &isActive, ImGuiWindowFlags_MenuBar);

	toolbar.fileMenu(&isActive);
	toolbar.AssetMenu(TOOLBAR_WIDTH);

	ImGui::End();
}

void LevelEditor::renderGrid()
{
	for (int i = 0; i < ROWS + 1; i++)
	{
		float xPos = (TOOLBAR_WIDTH + (i * CELL_SIZE));
		sf::Vertex verticalLine[] = { {{xPos, 0}, sf::Color::Cyan}, {{xPos, WINDOW_HEIGHT}, sf::Color::Cyan} };
		window_->draw(verticalLine, 2, sf::Lines);
	}

	for (int j = 0; j < COLUMNS + 1; j++)
	{
		float yPos = (j * CELL_SIZE);
		sf::Vertex horizontalLine[] = { {{TOOLBAR_WIDTH, yPos}, sf::Color::Cyan}, {{WINDOW_WIDTH, yPos}, sf::Color::Cyan} };
		window_->draw(horizontalLine, 2, sf::Lines);
	}
}
