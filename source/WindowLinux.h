#ifndef WINDOWLINUX_H
#define WINDOWLINUX_H

#include "WindowBaseClass.h"
#include "RenderComponentLinux.h"

#include <GL/glew.h> // always include GLEW before including freeGLUT so that you get the latest opengl headers and not the default ones
#include <GL/glfw.h>

class WindowLinux : public WindowBaseClass
{
public:
	WindowLinux();
	virtual ~WindowLinux();
  
  bool Init();

  void Run(); // like a Kenyan
	void Update();
	void Render();
  
  // Return the error message
  std::string GetErrorMessage( );
  
private:
  std::string m_errorMessage;
  
  // Set the error message and return false to be returned further on for the error management
  bool SetError( std::string p_errorMessage );
};

#endif