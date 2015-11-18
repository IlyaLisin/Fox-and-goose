#include "CApp.h"

void CApp::Reset()
	{
		Game_Mode = GAME_MODE_NONE;
		Game_Status = GAME_STATUS_MENU;
		
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (((i < 2) || (i>4)) && ((j < 2) || (j>4)))
				{
					Cell_Grid[i][j] = GRID_TYPE_NULL;
					continue;
				}
				Cell_Grid[i][j] = GRID_TYPE_NONE;

				X = (670 / 7)*j;
				Y = (670 / 7) *i;
				if (Cell_Grid[i][j] == GRID_TYPE_NONE) CSurface::OnDraw(Surf_Grid, Surf_None, X, Y);

				for (int m = 3; m < 7; m++)
				{
					for (int n = 0; n < 7; n++)
					{
						if (((m == 3) && ((n > 1) && (n < 5))) || (( m>4) && ((n <2)||(n>4)))) continue;
						Cell_Grid[m][n] = GRID_TYPE_GOOSE;
					}
				}
				Count_Goose = 17;
				Count_Goose_MM = 17;
			}
		}

	}
