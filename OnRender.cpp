#include "CApp.h"

void CApp::OnRender() 
{
	CSurface::OnDraw(Surf_Display, Surf_Grid, 0, 0); // вывод картинки

	SDL_Flip(Surf_Display);
}