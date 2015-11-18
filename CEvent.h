#ifndef _CEVENT_H_
#define _CEVENT_H_

#include <SDL.h>

class CEvent {
public:
	CEvent();

	virtual ~CEvent();

	virtual void OnEvent(SDL_Event* Event);

	virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);

	virtual void OnLButtonDown(int mX, int mY);

	virtual void OnExit();
};

#endif
