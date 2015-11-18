#include "GameLogic.h"
#include "CApp.h"

GameLogic::GameLogic()
{
}

short GridNull[16] = { 0, 1, 5, 6, 7, 8, 12, 13, 35, 36, 40, 41, 42, 43, 47, 48 };

CSurface::OnDraw(Surf_Display, Surf_Grid, 0, 0);
CSurface::OnDraw(Surf_Display, Surf_Menu, 655, 0);

for (int i = 0; i < 49; i++)
{
	for (int j = 0; j < 16; j++)
	{
		if (i == GridNull[j])
		{
			Cell_Grid[i] == GRID_TYPE_NULL;
			i++;
		}
	}
	int X = (i % 7) * 100 - 10;
	int Y = (i / 7) * 100 - 10;
	CSurface::OnDraw(Surf_Grid, Surf_None, X, Y);

}

GameLogic::~GameLogic()
{
}
