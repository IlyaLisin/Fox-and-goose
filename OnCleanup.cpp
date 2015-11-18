//Очистка ресурсов
#include "CApp.h"

void CApp::OnCleanup()
{
	SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(Surf_Grid);
	SDL_FreeSurface(Surf_Fox);
	SDL_FreeSurface(Surf_Goose);
	SDL_Quit();
}