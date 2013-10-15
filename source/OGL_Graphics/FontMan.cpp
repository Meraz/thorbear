#include "FontMan.h"

#include <GL/glfw.h>
#include <cstdlib>

extern void GLCheckErrors( std::string p_where );

FontMan::FontMan()
{
}

FontMan::~FontMan()
{
  glDeleteTextures( 1, &m_arial_texture );
  glDeleteBuffers( 1, &m_vbo );
  glDeleteVertexArrays( 1, &m_vao );
}

void FontMan::Init( )
{
  if(FT_Init_FreeType(&m_ft)) {
    fprintf(stderr, "Could not init freetype library\n");
    return;
  }
  
  if(FT_New_Face(m_ft, (FONT_DIRECTORY+"Arial.ttf").c_str(), 0, &m_arial)) {
    fprintf(stderr, "Could not open font\n");
    return;
  }
  GLCheckErrors( "FontMan::Init - FT_Init" );
  
  m_fontShader.Init( SHADER_DIRECTORY + "fontVertex.glsl", SHADER_DIRECTORY + "fontFragment.glsl" );
  m_fontShader.Build( );
  m_fontShader.Use( );
  
  GLCheckErrors( "FontMan::Init - Shaders" );
  
  m_currentSize = 24;
  FT_Set_Pixel_Sizes(m_arial, 0, m_currentSize);
  
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &m_arial_texture);
  glBindTexture(GL_TEXTURE_2D, m_arial_texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  GLCheckErrors( "FontMan::Init - TexGen" );
  
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  GLCheckErrors( "FontMan::Init - PixelStore" );
  
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray( m_vao );
  
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  
  GLCheckErrors( "FontMan::Init - Buffer setup" );
    
}

void FontMan::Draw( std::string p_text, float p_size, float p_posX, float p_posY, unsigned int p_color )
{
  glfwGetWindowSize( &m_windowWidth, &m_windowHeight );
  
  if( m_currentSize != (int)p_size )
  {
    m_currentSize = (int)p_size;
    FT_Set_Pixel_Sizes(m_arial, 0, m_currentSize);
  }
  float x = p_posX;
  float y = p_posY + m_currentSize;

  glBindVertexArray( m_vao );
  
  GLCheckErrors( "FontMan::Draw" );
  
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_arial_texture);
  
  m_fontShader.Use();
  glm::vec4 l_fontColor = glm::vec4( (p_color >> 0) & 0xFF, (p_color >> 8) & 0xFF, (p_color >> 16) & 0xFF, (p_color >> 24) & 0xFF ) / 256.f;
  m_fontShader.SetUniformVector( "color", l_fontColor );
  m_fontShader.SetUniformInt( "tex", 1 );
  
  // For converting screenspace to clipspace [-1..1]
  float sx = 2.0f / m_windowWidth;
  float sy = 2.0f / m_windowHeight;
  
  for(const char* p = p_text.c_str(); *p; p++)
  {
    if( *p == '\r' )
      continue;
    if( *p == '\n' )
    {
      x = p_posX;
      y += m_currentSize;
      continue;
    }
    if(FT_Load_Char(m_arial, *p, FT_LOAD_RENDER))
        continue;
 
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      m_arial->glyph->bitmap.width,
      m_arial->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      m_arial->glyph->bitmap.buffer
    );
    GLCheckErrors( "FontMan::Draw - glTexImage2D" );

    float x2 = -1 + (x + m_arial->glyph->bitmap_left) * sx;
    float y2 =  1 - (y - m_arial->glyph->bitmap_top) * sy;
    float w = m_arial->glyph->bitmap.width * sx;
    float h = -m_arial->glyph->bitmap.rows * sy;

    GLfloat box[4][4] = {
        {x2    , y2 + h, 0, 1},
        {x2 + w, y2 + h, 1, 1},
        {x2    , y2    , 0, 0},
        {x2 + w, y2    , 1, 0},
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
    GLCheckErrors( "FontMan::Draw - glBindBuffer, glBufferData" );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    GLCheckErrors( "FontMan::Draw - glDrawArrays" );

    x += (m_arial->glyph->advance.x >> 6);
    y += (m_arial->glyph->advance.y >> 6);
  }
}
