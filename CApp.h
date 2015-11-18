#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>

#include "CEvent.h"
#include "CSurface.h"

class CApp : public CEvent {
private:
	bool Running;

	SDL_Surface* Surf_Display;

	SDL_Surface* Surf_Grid;
	SDL_Surface* Surf_Fox;
	SDL_Surface* Surf_Goose;

public:
	CApp();

	int OnExecute();

	bool OnInit();

	void OnEvent(SDL_Event* Event);

	void OnExit();

	void OnLoop();

	void OnRender();

	void OnCleanup();
};

#endif