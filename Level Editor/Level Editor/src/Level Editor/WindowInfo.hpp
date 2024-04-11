#pragma once

class WindowInfo {

private:
	const float WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;
	const float CELL_SIZE = 16.0;
	const float TOOLBAR_WIDTH = WINDOW_WIDTH * 20.0 / 100;
	const float RENDERER_WIDTH = WINDOW_WIDTH - TOOLBAR_WIDTH;
	const float WINDOW_X_CENTER = TOOLBAR_WIDTH + ((WINDOW_WIDTH - TOOLBAR_WIDTH) / 2);

	float levelWidth;
	float levelHeight;
	float LevelXCenter;

	float rows = (WINDOW_WIDTH - TOOLBAR_WIDTH) / CELL_SIZE;
	float columns = WINDOW_HEIGHT / CELL_SIZE;

public:

	float getWindowWidth() { return WINDOW_WIDTH; }
	float getWindowHeight() { return WINDOW_HEIGHT; }
	float getRendererWidth() { return RENDERER_WIDTH; }
	float getToolbarWidth() { return TOOLBAR_WIDTH; }
	float getCellSize() { return CELL_SIZE; }
	float getWindowXCenter() { return WINDOW_X_CENTER; }

	float getLevelWidth() { return levelWidth; }
	float getLevelHeight() { return levelHeight; }
	float getLevelXCenter() { return LevelXCenter; }

	float getRows() { return rows; }
	float getColumns() { return columns; }
	
	void calculateLevelInfo(int rows_, int columns_)
	{
		rows = rows_;
		columns = columns_;

		levelWidth = columns * CELL_SIZE;
		levelHeight = rows * CELL_SIZE;
		LevelXCenter = TOOLBAR_WIDTH + (levelWidth / 2);
	}
};