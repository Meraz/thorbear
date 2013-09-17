#ifndef WINDOWBASECLASS_H
#define WINDOWBASECLASS_H

#include "RenderComponentInterface.h"
#include "GameInterface.h"
#include "Game.h"

class WindowBaseClass
{
public:
	WindowBaseClass();
	virtual ~WindowBaseClass();

protected:
	virtual void Render();
	
	/* Deltatime, Mouseposition.X, Mouseposition.Y */
	void Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY);	// Add support for use of keyboard

protected:
	GameInterface* m_gameInterface;
	RenderComponentInterface* m_renderComponentInterface;
};

#endif