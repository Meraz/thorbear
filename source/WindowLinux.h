#ifndef WINDOWLINUX_H
#define WINDOWLINUX_H

#include "WindowBaseClass.h"
#include "RenderComponentLinux.h"

class WindowLinux : public WindowBaseClass
{
public:
	WindowLinux();
	virtual ~WindowLinux();
	int Run();

	void Update();
	void Render();
};

#endif