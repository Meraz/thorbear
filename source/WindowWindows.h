#ifndef WINDOWWINDOWS_H
#define WINDOWWINDOWS_H

#include <windows.h>
#include "RenderComponentWin.h"
#include "WindowBaseClass.h"

class WindowWindows : public WindowBaseClass
{
public:
	WindowWindows(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow);
	~WindowWindows();
private:
	void Update();
	void Render();

};

#endif