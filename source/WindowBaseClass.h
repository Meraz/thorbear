#ifndef WINDOWBASECLASS_H
#define WINDOWBASECLASS_H

#include "RenderComponentInterface.h"
#include "GameInterface.h"
#include "SceneManager.h"

class WindowBaseClass
{
public:
	WindowBaseClass();
	virtual ~WindowBaseClass();
	virtual int Run() = 0;

protected:
	virtual void Render();

	/* Deltatime, Mouseposition.X, Mouseposition.Y */
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);	// Add support for use of keyboard

protected:
	GameInterface* m_gameInterface;
	RenderComponentInterface* m_renderComponentInterface;
private:

};

#endif