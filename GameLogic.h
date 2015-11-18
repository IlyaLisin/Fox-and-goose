#pragma once
#include "CApp.h"
#include "CSurface.h"
#include "CEvent.h"
#include <SDL.h>

class GameLogic
{
private:
	int Cell_Grid[49];
	int X, Y;
	short Game_Status;
	short Game_Mode;
	int Count_Goose;

	enum {
		GRID_TYPE_NONE = 0,
		GRID_TYPE_FOX,
		GRID_TYPE_GOOSE,
		GRID_TYPE_NULL,

		GAME_STATUS_MENU,
		GAME_STATUS_OVER,
		GAME_STATUS_SET_FOX,
		GAME_STATUS_FOX,
		GAME_STATUS_GOOSE,

		GAME_MODE_NONE,
		GAME_MODE_PVP,
		GAME_MODE_PVC,

		WIN_FOX,
		WIN_GOOSE
	};
public:

	void Init();

	bool SetPosition(int mX, int mY);

	//int Select(int mX, int mY);

	int Get_i(int mX, int mY);

	bool Move(int mX, int mY);

	bool Check_Goose_On_Way(int old_i, int new_i);

	int CheckWin();

	GameLogic();
	~GameLogic();
};

