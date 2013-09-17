#ifndef OGL_GRAPHICS_H
#define OGL_GRAPHICS_H

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
    
    std::string GetError;
};

#endif