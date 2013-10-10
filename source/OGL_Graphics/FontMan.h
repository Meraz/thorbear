#ifndef FONTMAN_H
#define FONTMAN_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <string>

#include "OGL_Graphics/Shader.h"

#define FONT_DIRECTORY std::string("fonts/")

class FontMan
{
public:
  FontMan();
  ~FontMan();
  
  void Init( );
  void Draw( std::wstring p_text, float p_size, float p_posX, float p_posY, unsigned int p_color );

private:
  FT_Library m_ft;
  FT_Face m_arial;
  GLuint m_arial_texture;
  GLuint m_vao, m_vbo;
  
  Shader m_fontShader;
  int m_windowWidth, m_windowHeight;
  
  int m_currentSize;
};

#endif