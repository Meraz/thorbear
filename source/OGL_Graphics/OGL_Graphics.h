#ifndef OGL_GRAPHICS_H
#define OGL_GRAPHICS_H

#include <GL/glew.h> // always include GLEW before including freeGLUT so that you get the latest opengl headers and not the default ones
#define GLFW_DLL // We're linking to a DLL instead of embedding all of GLFW into our program
#include <GL/glfw.h>

#include <string>

class OGL_Graphics
{
  private:
    std::string m_errorMessage;
    
    // Set the error message and return false to be returned further on for the error management
    bool SetError( std::string &p_errorMessage );
  
  public:
    // Initialize the Win/Lin window and set up OpenGL 4
    bool Init( );
    
    // Draw rainbows!!!111
    bool Update( );
    
    // Return the error message
    std::string GetErrorMessage( );
};

#endif