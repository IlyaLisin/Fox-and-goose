#include "CApp.h"
#include <vector>

int CApp::MinMax(int depth, int status,int alpha, int beta)
{
	// если достигли нижнего уровн€ получаем оценку
	if (depth >= 3)
		return GetEvaluation();

	// если состо€ние выигрышное, получем оценку
	if (CheckWin()) return GetEvaluation();

	int testVal;
	std::vector<int> bestMove;
	int MinMax = (status == GAME_STATUS_GOOSE_MM) ? -iNFINITY : iNFINITY;

	// проверка ходов
	switch (status)
	{
	case GAME_STATUS_GOOSE_MM: // если ход€т гуси		
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{	
				if (Cell_Grid[i][j] == GRID_TYPE_GOOSE) // перебираем гусей и их возможные ходы
				{	
					if (Check_Move_Ai(i, j, i - 1, j,status)) 
					{
						MakeMoveGoose(i, j, i - 1, j); // делаем ход
						testVal = CApp::MinMax(depth+1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM,alpha,beta);
						UndoMoveGoose(i, j, i - 1, j); // отмен€ем ход
						//дл€ компьютера выбираем максимальную оценку, дл€ игрока минимальную
						if ((testVal > MinMax && status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && status == GAME_STATUS_FOX_MM) || bestMove.empty())
						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i - 1, j);
						}
						// альфа-бета отсечение
						alpha = fMax(alpha, testVal);
						if (alpha > beta) break;
					}
					if (Check_Move_Ai(i, j, i, j - 1, status))
					{
						MakeMoveGoose(i, j, i, j - 1);
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						UndoMoveGoose(i, j, i, j - 1);
						if ((testVal > MinMax && status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && status == GAME_STATUS_FOX_MM) || bestMove.empty())
						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i, j - 1);
						}
						alpha = fMax(alpha, testVal);
						if (alpha > beta) break;
					}
					if (Check_Move_Ai(i, j, i, j + 1, status))
					{
						MakeMoveGoose(i, j, i, j + 1);
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						UndoMoveGoose(i, j, i, j + 1);
						if ((testVal > MinMax && status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && status == GAME_STATUS_FOX_MM) || bestMove.empty())
						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i, j + 1);
						}
						alpha = fMax(alpha, testVal);
						if (alpha > beta) break;
					}
					if (Check_Move_Ai(i, j, i + 1, j, status))
					{
						MakeMoveGoose(i, j, i + 1, j);
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						UndoMoveGoose(i, j, i + 1, j);
						if ((testVal > MinMax && status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && status == GAME_STATUS_FOX_MM) || bestMove.empty())
						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i + 1, j);
						}

						alpha = fMax(alpha, testVal);
						if (alpha > beta) break;
					}
				}
			}
		} 
		break;
	case GAME_STATUS_FOX_MM: // если ходит лиса
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (Cell_Grid[i][j] == GRID_TYPE_FOX)  // ищем лису и перебираем ее возможные ходы
				{
					if (Check_Move_Ai(i, j, i + 1, j, status))
					{
						int supCell_Grid_2[7][7];
						Save_Grid(&supCell_Grid_2[0][0], 1); // сохран€ем текущее состо€ние
						supCount = 0; // количество гусей
						MakeMoveFox(i, j, i + 1, j ); // делаем ход
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						Save_Grid(&supCell_Grid_2[0][0], 0); // восстанавливаем состо€ние
						//дл€ компьютера выбираем максимальную оценку, дл€ игрока минимальную
						if ((testVal > MinMax && Game_Status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && Game_Status == GAME_STATUS_FOX_MM) || bestMove.empty())						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i + 1, j);
						}
						//альфа-бета отсечение
						beta = fMin(beta, testVal);
						if (alpha > beta) break;
					}
					if (Check_Move_Ai(i, j, i - 1, j, status))
					{

						int supCell_Grid_2[7][7];
						Save_Grid(&supCell_Grid_2[0][0], 1);
						supCount = 0;
						MakeMoveFox(i, j, i - 1, j);
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						Save_Grid(&supCell_Grid_2[0][0], 0);
						if ((testVal > MinMax && Game_Status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && Game_Status == GAME_STATUS_FOX_MM) || bestMove.empty())						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i - 1, j);
						}
						beta = fMin(beta, testVal);
					    if (alpha > beta) break;
					}
					if (Check_Move_Ai(i, j, i - 1, j + 1, status))
					{
						int supCell_Grid_2[7][7];
						Save_Grid(&supCell_Grid_2[0][0], 1);
						supCount = 0;
						MakeMoveFox(i, j, i - 1, j + 1);
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						Save_Grid(&supCell_Grid_2[0][0], 0);
						if ((testVal > MinMax && Game_Status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && Game_Status == GAME_STATUS_FOX_MM) || bestMove.empty())						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i - 1, j + 1);
						}
						beta = fMin(beta, testVal);
						if (alpha > beta) break;
					}
					if (Check_Move_Ai(i, j, i, j - 1, status))
					{
						int supCell_Grid_2[7][7];
						Save_Grid(&supCell_Grid_2[0][0], 1);
						supCount = 0;
						MakeMoveFox(i, j, i, j - 1);
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						Save_Grid(&supCell_Grid_2[0][0], 0);
						if ((testVal > MinMax && Game_Status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && Game_Status == GAME_STATUS_FOX_MM) || bestMove.empty())
						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i, j - 1);
						}
						beta = fMin(beta, testVal);
						if (alpha > beta) break;
					}
					if (Check_Move_Ai(i, j, i, j + 1, status))
					{
						int supCell_Grid_2[7][7];
						Save_Grid(&supCell_Grid_2[0][0], 1);
						supCount = 0;
						MakeMoveFox(i, j, i, j + 1);
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						Save_Grid(&supCell_Grid_2[0][0], 0);
						if ((testVal > MinMax && Game_Status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && Game_Status == GAME_STATUS_FOX_MM) || bestMove.empty())
						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i, j + 1);
						}
						beta = fMin(beta, testVal);
						if (alpha > beta) break;
					}
					if (Check_Move_Ai(i, j, i + 1, j - 1, status))
					{
						int supCell_Grid_2[7][7];
						Save_Grid(&supCell_Grid_2[0][0], 1);
						supCount = 0;
						MakeMoveFox(i, j, i + 1, j - 1);
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						Save_Grid(&supCell_Grid_2[0][0], 0);
						if ((testVal > MinMax && Game_Status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && Game_Status == GAME_STATUS_FOX_MM) || bestMove.empty())
						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i + 1, j - 1);
						}
						beta = fMin(beta, testVal);
						if (alpha > beta) break;
					}
					if (Check_Move_Ai(i, j, i - 1, j-1, status))
					{
						int supCell_Grid_2[7][7];
						Save_Grid(&supCell_Grid_2[0][0], 1);
						supCount = 0;
						MakeMoveFox(i, j, i - 1, j-1);
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						Save_Grid(&supCell_Grid_2[0][0], 0);
						if ((testVal > MinMax && Game_Status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && Game_Status == GAME_STATUS_FOX_MM) || bestMove.empty())
						{
							MinMax = testVal;
							SaveBestMove(bestMove, i, j, i - 1, j - 1);
						}
						beta = fMin(beta, testVal);
						if (alpha > beta) break;
					}
					if (Check_Move_Ai(i, j, i + 1, j + 1, status))
					{
						int supCell_Grid_2[7][7];
						Save_Grid(&supCell_Grid_2[0][0], 1);
						supCount = 0;
						MakeMoveFox(i, j, i + 1, j + 1);
						testVal = CApp::MinMax(depth + 1, status == GAME_STATUS_GOOSE_MM ? GAME_STATUS_FOX_MM : GAME_STATUS_GOOSE_MM, alpha, beta);
						Save_Grid(&supCell_Grid_2[0][0], 0);
						if ((testVal > MinMax && Game_Status == GAME_STATUS_GOOSE_MM) || (testVal <= MinMax && Game_Status == GAME_STATUS_FOX_MM) || bestMove.empty())
						{
							MinMax = testVal;
							SaveBestMove(bestMove,i, j, i + 1,j + 1);
						}
						beta = fMin(beta, testVal);
						if (alpha > beta) break;
					}
				}
			}
		}
	}
	// если вернулись в корень делаем ход
	if (depth == 0 && !bestMove.empty())
	{
		MakeMove(bestMove[0], bestMove[1], bestMove[2], bestMove[3]);
	}

	return MinMax;
}

void CApp::SaveBestMove(std::vector<int> &bestmove, int old_i, int old_j, int new_i, int new_j)
{
	bestmove.clear();
	bestmove.push_back(old_i);
	bestmove.push_back(old_j);
	bestmove.push_back(new_i);
	bestmove.push_back(new_j);
}

int CApp::Save_Grid(int *supCell_Grid_2, bool state)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (state == 1)
			{
				*(supCell_Grid_2 + i * 7 + j) = Cell_Grid[i][j];
			}
			else
			{
				Cell_Grid[i][j] = *(supCell_Grid_2 + i * 7 + j);

			}
		}
	}
	if (Count_Goose_MM > Count_Goose) Count_Goose=Count_Goose+supCount;
	return 1;
	
}

int CApp::fMax(int x, int y)
{
	if (x > y) return x;
	else return y;
}

int CApp::fMin(int x, int y)
{
	if (x < y) return x;
	else return y;
}

void CApp::MakeMoveGoose(int old_i, int old_j, int new_i, int new_j)
{
	Cell_Grid[old_i][old_j] = GRID_TYPE_NONE;
	Cell_Grid[new_i][new_j] = GRID_TYPE_GOOSE;
}

void CApp::MakeMoveFox_2(int old_i, int old_j, int new_i, int new_j)
{

		Cell_Grid[old_i][old_j] = GRID_TYPE_NONE;
		Cell_Grid[new_i][new_j] = GRID_TYPE_FOX;
		if (new_i - old_i == 2) Cell_Grid[new_i - 1][new_j] = GRID_TYPE_NONE;
		if (new_i - old_i == -2) Cell_Grid[new_i + 1][new_j] = GRID_TYPE_NONE;
		if (new_j - old_j == 2) Cell_Grid[new_i][new_j - 1] = GRID_TYPE_NONE;
		if (new_j - old_j == -2) Cell_Grid[new_i][new_j + 1] = GRID_TYPE_NONE;
		supCount++;
		Count_Goose--;
	if (Check_Goose_Around(new_i, new_j))
	{
		if (Check_Goose_On_Way(new_i, new_j, new_i - 2, new_j)) MakeMoveFox_2(new_i, new_j, new_i - 2, new_j);
		if (Check_Goose_On_Way(new_i, new_j, new_i + 2, new_j)) MakeMoveFox_2(new_i, new_j, new_i + 2, new_j);
		if (Check_Goose_On_Way(new_i, new_j, new_i, new_j - 2)) MakeMoveFox_2(new_i, new_j, new_i, new_j - 2);
		if (Check_Goose_On_Way(new_i, new_j, new_i, new_j + 2)) MakeMoveFox_2(new_i, new_j, new_i, new_j + 2);
	}
	
}

void CApp::MakeMoveFox(int old_i, int old_j, int new_i, int new_j)
{
	if (Check_Goose_Around(old_i, old_j))
	{
		if (Check_Goose_On_Way(old_i, old_j, old_i - 2, old_j)) MakeMoveFox_2(old_i, old_j, old_i - 2, old_j);
		if (Check_Goose_On_Way(old_i, old_j, old_i + 2, old_j)) MakeMoveFox_2(old_i, old_j, old_i + 2, old_j);
		if (Check_Goose_On_Way(old_i, old_j, old_i, old_j - 2)) MakeMoveFox_2(old_i, old_j, old_i, old_j - 2);
		if (Check_Goose_On_Way(old_i, old_j, old_i, old_j + 2)) MakeMoveFox_2(old_i, old_j, old_i, old_j + 2);
	}
	else
	{
		Cell_Grid[old_i][old_j] = GRID_TYPE_NONE;
		Cell_Grid[new_i][new_j] = GRID_TYPE_FOX;
	}
}

void CApp::MakeMove(int old_i, int old_j,int new_i, int new_j)
{
	switch (Game_Status)	
	{
	case GAME_STATUS_GOOSE:
		Cell_Grid[old_i][old_j] = GRID_TYPE_NONE;
		Cell_Grid[new_i][new_j] = GRID_TYPE_GOOSE;
		break;
	case GAME_STATUS_FOX:
		MakeMoveFox(old_i,old_j,new_i,new_j);
		break;
	}
}

int CApp::GetEvaluation()
{
	int i=0, j=0,e=0;
	int winner = 0;
	winner = CheckWin();
	if (winner)
	{
		switch (winner)
		{
		case WIN_GOOSE: return 100;
			break;
		case WIN_FOX: return -100;
			break;
		default: return -50;
			break;
		}
	}

	while (1) // ищем лису
	{
		if (Cell_Grid[i][j] == GRID_TYPE_FOX) break;
		if (j == 6)
		{
			j = 0;
			i++;
			continue;
		}
		j++;
	}

	if (Check_Goose_Around(i, j)) e = e - 10; // если лисе есть кого съесть
	// если у лисы нето доступного хода
	if ((Cell_Grid[i + 1][j] == GRID_TYPE_NULL || Cell_Grid[i + 1][j] == GRID_TYPE_GOOSE) && (Cell_Grid[i + 2][j] == GRID_TYPE_NULL || Cell_Grid[i + 2][j] == GRID_TYPE_GOOSE)) e = e - 5;
	if ((Cell_Grid[i - 1][j] == GRID_TYPE_NULL || Cell_Grid[i - 1][j] == GRID_TYPE_GOOSE) && (Cell_Grid[i - 2][j] == GRID_TYPE_NULL || Cell_Grid[i - 2][j] == GRID_TYPE_GOOSE)) e = e - 5;
	if ((Cell_Grid[i + 1][j + 1] == GRID_TYPE_NULL || Cell_Grid[i + 1][j + 1] == GRID_TYPE_GOOSE) && (Cell_Grid[i + 2][j + 2] == GRID_TYPE_NULL || Cell_Grid[i + 2][j + 2] == GRID_TYPE_GOOSE)) e = e - 5;
	if ((Cell_Grid[i + 1][j - 1] == GRID_TYPE_NULL || Cell_Grid[i + 1][j - 1] == GRID_TYPE_GOOSE) && (Cell_Grid[i + 2][j - 2] == GRID_TYPE_NULL || Cell_Grid[i + 2][j - 2] == GRID_TYPE_GOOSE)) e = e - 5;
	if ((Cell_Grid[i - 1][j + 1] == GRID_TYPE_NULL || Cell_Grid[i - 1][j + 1] == GRID_TYPE_GOOSE) && (Cell_Grid[i - 2][j + 2] == GRID_TYPE_NULL || Cell_Grid[i - 2][j + 2] == GRID_TYPE_GOOSE)) e = e - 5;
	if ((Cell_Grid[i - 1][j - 1] == GRID_TYPE_NULL || Cell_Grid[i - 1][j - 1] == GRID_TYPE_GOOSE) && (Cell_Grid[i - 2][j - 2] == GRID_TYPE_NULL || Cell_Grid[i - 2][j - 2] == GRID_TYPE_GOOSE)) e = e - 5;
	if ((Cell_Grid[i][j + 1] == GRID_TYPE_NULL || Cell_Grid[i][j + 1] == GRID_TYPE_GOOSE) && (Cell_Grid[i][j + 2] == GRID_TYPE_NULL || Cell_Grid[i][j + 2] == GRID_TYPE_GOOSE)) e = e - 5;
	if ((Cell_Grid[i][j - 1] == GRID_TYPE_NULL || Cell_Grid[i][j - 1] == GRID_TYPE_GOOSE) && (Cell_Grid[i][j - 2] == GRID_TYPE_NULL || Cell_Grid[i][j - 2] == GRID_TYPE_GOOSE)) e = e - 5;
	e = e + Count_Goose;
	return e;
}

void CApp::UndoMoveGoose(int old_i, int old_j, int new_i, int new_j)
{
	Cell_Grid[new_i][new_j] = GRID_TYPE_NONE;
	Cell_Grid[old_i][old_j] = GRID_TYPE_GOOSE;
}

int CApp::Check_Move_Ai(int old_i, int old_j, int new_i, int new_j,int status)
{
	if ((new_i < 0) || (new_i>6) || (new_j < 0) ||(new_j>6)) return false;
	switch (status)
	{
	case GAME_STATUS_GOOSE_MM:
		if ((Cell_Grid[new_i][new_j] == GRID_TYPE_NONE)
			&& (((new_j == old_j) && (new_i == old_i - 1))
			|| ((new_j == old_j) && (new_i == old_i + 1)) 
			|| ((new_i == old_i) && (new_j == old_j - 1)) 
			|| ((new_i == old_i) && (new_j == old_j + 1))))
			return true;
		break;
	case GAME_STATUS_FOX_MM:
		if (Check_Goose_Around(old_i, old_j)) return  true;
		if (new_i > 6 || new_i < 0 || new_j>6 || new_j < 0) return false;
		if ((Cell_Grid[new_i][new_j] == GRID_TYPE_NONE) && (((old_i == new_i - 1) && (old_j == new_j)) || ((old_i == new_i + 1) && (old_j == new_j))
			|| ((old_j == new_j - 1) && (old_i == new_i)) || ((old_j == new_j + 1) && (old_i == new_i))
			|| ((old_i == new_i - 1) && (old_j == new_j + 1)) || ((old_i == new_i - 1) && (old_j == new_j - 1))
			|| ((old_i == new_i + 1) && (old_j == new_j - 1)) || ((old_i == new_i + 1) && (old_j == new_j + 1)))) 
		return true;
		break;
	}
	
	return false;
}

int CApp::Get_i(int mY)
{
	int i = 0;
	int sY = 0;
	sY = mY % 100;
	mY = (mY / 100) * 100;
	if (sY > 50) mY += 100;
	i = (mY / 100);
	return i;
}
int CApp::Get_j(int mX)
{
	int j = 0;
	int sX = 0;
	sX = mX % 100; // отклонение
	mX = (mX / 100) * 100; // координаты, куда ставить лису
	if (sX > 60) mX += 100;
	j = (mX / 100);
	return j;
}

bool CApp::Check_Goose_On_Way(int old_i,int old_j, int new_i,int new_j) // есть
{
	//можно ли съесть
	if ((old_i<5) && (Cell_Grid[new_i][new_j]==GRID_TYPE_NONE)&&((new_i - 1 == old_i + 1) && (old_j == new_j)) && ((Cell_Grid[new_i - 1][new_j] == GRID_TYPE_GOOSE)))  return true; 
	if ((old_i>1) && (Cell_Grid[new_i][new_j] == GRID_TYPE_NONE) && ((new_i + 1 == old_i - 1) && (old_j == new_j)) && ((Cell_Grid[new_i + 1][new_j] == GRID_TYPE_GOOSE)))  return true;
	if ((old_j>1) && (Cell_Grid[new_i][new_j] == GRID_TYPE_NONE) && ((new_i == old_i) && (old_j - 1 == new_j + 1)) && ((Cell_Grid[new_i][new_j + 1] == GRID_TYPE_GOOSE)))  return true;
	if ((old_j<5) && (Cell_Grid[new_i][new_j] == GRID_TYPE_NONE) && ((new_i == old_i) && (old_j + 1 == new_j - 1)) && ((Cell_Grid[new_i][new_j - 1] == GRID_TYPE_GOOSE)))  return true;

	return false;
}

bool CApp::Check_Goose_Around(int old_i,int old_j)
{	//можно ли съесть кого вокруг
	if ((old_j < 0) || (old_j > 6) || (old_i<0) || (old_i > 6)) return false;
	if ((old_i>1) && (Cell_Grid[old_i - 1][old_j] == GRID_TYPE_GOOSE) && (Cell_Grid[old_i - 2][old_j] == GRID_TYPE_NONE)) return true;
	if ((old_j>1) && (Cell_Grid[old_i][old_j - 1] == GRID_TYPE_GOOSE) && (Cell_Grid[old_i][old_j - 2] == GRID_TYPE_NONE)) return true;
	if ((old_j<5) && (Cell_Grid[old_i][old_j + 1] == GRID_TYPE_GOOSE) && (Cell_Grid[old_i][old_j + 2] == GRID_TYPE_NONE)) return true;
	if ((old_i<5) && (Cell_Grid[old_i + 1][old_j] == GRID_TYPE_GOOSE) && (Cell_Grid[old_i + 2][old_j] == GRID_TYPE_NONE)) return true;
	return false;
}

bool CApp::SetPosition(int mX, int mY)
{
	
	int i = Get_i(mY);
	int j = Get_j(mX);
	if (Cell_Grid[i][j] == GRID_TYPE_NONE)
	{
		if (Game_Status == GAME_STATUS_SET_FOX) 
		{
			Cell_Grid[i][j] = GRID_TYPE_FOX;
			CSurface::OnDraw(Surf_Grid, Surf_Fox, (670 / 7)*j + 8.5, (670 / 7) *i + 10);
			OnRender();
		} // установка флага лисы в массиве
		return true;
	}
	return false;
}

bool CApp::Check_Move(int old_i,int old_j, int new_i, int new_j) 
{
	switch (Game_Status)
	{
	case GAME_STATUS_GOOSE:
		if ((Cell_Grid[new_i][new_j] == GRID_TYPE_NONE)
			&& (((new_j == old_j) && (new_i == old_i - 1)) || ((new_j == old_j) 
			&& (new_i == old_i + 1)) || ((new_i == old_i) && (new_j == old_j - 1)) || ((new_i == old_i) && (new_j == old_j + 1))))
		{ 
			
			return true; 
		} 
		else return false;
		break;
	case GAME_STATUS_FOX:
		if (Check_Goose_Around(old_i, old_j) != false) return  true;
		if ((Cell_Grid[new_i][new_j] == GRID_TYPE_NONE) && (((old_i == new_i - 1) && (old_j == new_j)) || ((old_i == new_i + 1) && (old_j == new_j))
			|| ((old_j == new_j - 1) && (old_i == new_i)) || ((old_j == new_j + 1) && (old_i == new_i))
			|| ((old_i == new_i - 1) && (old_j == new_j + 1)) || ((old_i == new_i - 1) && (old_j == new_j - 1))
			|| ((old_i == new_i + 1) && (old_j == new_j - 1)) || ((old_i == new_i + 1) && (old_j == new_j + 1))))
			 return true;
		 break;
	}
	return false;
}

bool CApp::Move(int mX, int mY)
{
	int k = 0, new_i = 0, new_j=0, old_i = 0, old_j=0;

	SDL_Event eventmove;

	old_i = Get_i(mY);
	old_j = Get_j(mX);

	while (1) //полчение событи€ 
	{
		SDL_Delay(100);
		SDL_PollEvent(&eventmove);

		if ((Game_Status == GAME_STATUS_FOX) && (k > 0))
		{
			if (!(Check_Goose_Around(new_i, new_j))) break;
		}
		if (eventmove.type == SDL_MOUSEBUTTONDOWN)
		{

			SDL_Delay(100);
			mX = eventmove.button.x;
			mY = eventmove.button.y;
			new_i = Get_i(mY);
			new_j = Get_j(mX);

			if (k > 0) // если лиса съела одного гус€, проверить след ход
			{
				if (Check_Goose_On_Way(old_i, old_j, new_i, new_j))
				{
					Cell_Grid[old_i][old_j] = GRID_TYPE_NONE;
					Cell_Grid[new_i][new_j] = GRID_TYPE_FOX;
					if (new_i - old_i == 2) Cell_Grid[new_i - 1][new_j] = GRID_TYPE_NONE;
					if (new_i - old_i == -2) Cell_Grid[new_i + 1][new_j] = GRID_TYPE_NONE;
					if (new_j - old_j == 2) Cell_Grid[new_i][new_j - 1] = GRID_TYPE_NONE;
					if (new_j - old_j == -2) Cell_Grid[new_i][new_j + 1] = GRID_TYPE_NONE;
					Count_Goose--;
					k++;
					old_i = new_i;
					old_j = new_j;
					if (Check_Goose_Around(new_i, new_j)) continue;
				}
				else
					break;
			}

			if (Check_Move(old_i, old_j, new_i, new_j))
			{
				if (Game_Status == GAME_STATUS_GOOSE)
				{
					Cell_Grid[new_i][new_j] = GRID_TYPE_GOOSE;
					Cell_Grid[old_i][old_j] = GRID_TYPE_NONE;
					break;
				}
				if (Game_Status == GAME_STATUS_FOX)
				{
					if (!(Check_Goose_Around(old_i, old_j)))
					{
						Cell_Grid[old_i][old_j] = GRID_TYPE_NONE;
						Cell_Grid[new_i][new_j] = GRID_TYPE_FOX;
						break;
					}
					else
					{
						if (Check_Goose_On_Way(old_i, old_j, new_i, new_j))
						{
							Cell_Grid[old_i][old_j] = GRID_TYPE_NONE;
							Cell_Grid[new_i][new_j] = GRID_TYPE_FOX;
							if (new_i - old_i == 2)	Cell_Grid[new_i - 1][new_j] = GRID_TYPE_NONE;
							if (new_i - old_i == -2) Cell_Grid[new_i + 1][new_j] = GRID_TYPE_NONE;
							if (new_j - old_j == 2) Cell_Grid[new_i][new_j - 1] = GRID_TYPE_NONE;
							if (new_j - old_j == -2) Cell_Grid[new_i][new_j + 1] = GRID_TYPE_NONE;
							Count_Goose--;
							k++;
							old_i = new_i;
							old_j = new_j;
							if (Check_Goose_Around(new_i, new_j))
							{
								continue;
							}
							else
							{
								break;
							}
						}
						else
							continue;
					}

				}

			}

		}

	}
	OnRender();
	SDL_Delay(100);
	return true;
}

void CApp::GetWinner()
{
	if (CheckWin() == WIN_GOOSE) CSurface::OnDraw(Surf_Menu, Surf_GooseWin, 25, 350);
	else CSurface::OnDraw(Surf_Menu, Surf_FoxWin, 25, 350);
}

int CApp::CheckWin()
{
	if (Count_Goose == 6)
	{
		return WIN_FOX;
	}

	int i = 0, j = 0;

	while (1)
	{
		if (Cell_Grid[i][j] == GRID_TYPE_FOX) break;
		if (j == 6)
		{
			j = 0;
			i++;
			continue;
		}
		j++;
	}


	if (i == 0)
	{
		if (((Cell_Grid[i][j - 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i][j - 1] == GRID_TYPE_NULL))		// лево
			&& ((Cell_Grid[i][j + 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i][j + 1] == GRID_TYPE_NULL))		// право
			&& ((Cell_Grid[i + 1][j - 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i + 1][j - 1] == GRID_TYPE_NULL)) //лево низ
			&& ((Cell_Grid[i + 1][j] == GRID_TYPE_GOOSE) || (Cell_Grid[i + 1][j] == GRID_TYPE_NULL))		// низ цетр
			&& ((Cell_Grid[i + 1][j + 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i + 1][j + 1] == GRID_TYPE_NULL)))
		{
			return WIN_GOOSE;
		}
	}

	if (j == 0)
	{
		if (((Cell_Grid[i - 1][j] == GRID_TYPE_GOOSE) || (Cell_Grid[i - 1][j] == GRID_TYPE_NULL))        // центр верх
			&& ((Cell_Grid[i - 1][j + 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i - 1][j + 1] == GRID_TYPE_NULL))        // право верх
			&& ((Cell_Grid[i][j + 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i][j + 1] == GRID_TYPE_NULL))		// право
			&& ((Cell_Grid[i + 1][j] == GRID_TYPE_GOOSE) || (Cell_Grid[i + 1][j] == GRID_TYPE_NULL))		// низ цетр
			&& ((Cell_Grid[i + 1][j + 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i + 1][j + 1] == GRID_TYPE_NULL))) // право низ
		{
			return WIN_GOOSE;
		}
	}

	if (i == 6)
	{
		if (((Cell_Grid[i - 1][j - 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i - 1][j - 1] == GRID_TYPE_NULL)) // лев верх
			&& ((Cell_Grid[i - 1][j] == GRID_TYPE_GOOSE) || (Cell_Grid[i - 1][j] == GRID_TYPE_NULL))        // центр верх
			&& ((Cell_Grid[i - 1][j + 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i - 1][j + 1] == GRID_TYPE_NULL))        // право верх
			&& ((Cell_Grid[i][j - 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i][j - 1] == GRID_TYPE_NULL))		// лево
			&& ((Cell_Grid[i][j + 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i][j + 1] == GRID_TYPE_NULL)))	// право
		{
			return WIN_GOOSE;
		}
	}

	if (j == 6)
	{
		if (((Cell_Grid[i - 1][j - 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i - 1][j - 1] == GRID_TYPE_NULL)) // лев верх
			&& ((Cell_Grid[i - 1][j] == GRID_TYPE_GOOSE) || (Cell_Grid[i - 1][j] == GRID_TYPE_NULL))        // центр верх
			&& ((Cell_Grid[i][j - 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i][j - 1] == GRID_TYPE_NULL))		// лево
			&& ((Cell_Grid[i + 1][j - 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i + 1][j - 1] == GRID_TYPE_NULL)) //лево низ
			&& ((Cell_Grid[i + 1][j] == GRID_TYPE_GOOSE) || (Cell_Grid[i + 1][j] == GRID_TYPE_NULL)))	// низ цетр
		{
			return WIN_GOOSE;
		}
	}

	if (((Cell_Grid[i - 1][j - 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i - 1][j - 1] == GRID_TYPE_NULL)) // лев верх
		&& ((Cell_Grid[i - 1][j] == GRID_TYPE_GOOSE) || (Cell_Grid[i - 1][j] == GRID_TYPE_NULL))        // центр верх
		&& ((Cell_Grid[i - 1][j + 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i - 1][j + 1] == GRID_TYPE_NULL))        // право верх
		&& ((Cell_Grid[i][j - 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i][j - 1] == GRID_TYPE_NULL))		// лево
		&& ((Cell_Grid[i][j + 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i][j + 1] == GRID_TYPE_NULL))	// право
		&& ((Cell_Grid[i + 1][j - 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i + 1][j - 1] == GRID_TYPE_NULL)) //лево низ
		&& ((Cell_Grid[i + 1][j] == GRID_TYPE_GOOSE) || (Cell_Grid[i + 1][j] == GRID_TYPE_NULL))	// низ цетр
		&& ((Cell_Grid[i + 1][j + 1] == GRID_TYPE_GOOSE) || (Cell_Grid[i + 1][j + 1] == GRID_TYPE_NULL))) // право низ
	{
		return WIN_GOOSE;
	}
	return false;
}