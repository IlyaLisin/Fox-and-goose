#include "CApp.h"
#include <iostream>
CApp::CApp() 
{
	Surf_Display = NULL;
	Surf_Grid = NULL;
	Surf_Fox = NULL;
	Surf_Goose = NULL;

	Running = true;
}

int CApp::OnExecute() 
{
	if (OnInit() == false) 
	{
		return -1;
	}

	SDL_Event Event;

	while (Running)
	{
		while (SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}

		OnLoop();
		OnRender();
		//std::cout << "1";
	}

	OnCleanup();

	return 0;
}

int main(int argc, char* argv[]) 
{
	CApp theApp;

	return theApp.OnExecute();
}