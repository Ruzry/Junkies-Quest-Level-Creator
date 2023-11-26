#pragma once

class WindowInfo {

private:
	const float WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;
	const float CELL_SIZE = 16.0;

	const float TOOLBAR_WIDTH = WINDOW_WIDTH * 20.0 / 100;
	const float LEVEL_WIDTH = WINDOW_WIDTH - TOOLBAR_WIDTH;
	const float LEVEL_X_CENTER = TOOLBAR_WIDTH + (LEVEL_WIDTH / 2);

	const float ROWS = (WINDOW_WIDTH - TOOLBAR_WIDTH) / CELL_SIZE;
	const float COLUMNS = WINDOW_HEIGHT / CELL_SIZE;

public:

	float getWindowWidth() { return WINDOW_WIDTH; }
	float getWindowHeight() { return WINDOW_HEIGHT; }
	float getToolbarWidth() { return TOOLBAR_WIDTH; }
	float getCellSize() { return CELL_SIZE; }

	float getLevelWidth() { return LEVEL_WIDTH; }
	float getLevelXCenter() { return LEVEL_X_CENTER; }

	float getRows() { return ROWS; }
	float getColumns() { return COLUMNS; }
};