#include "FontMan.h"

#include <GL/glfw.h>

FontMan::FontMan()
{
}

FontMan::~FontMan()
{
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
  
  m_fontShader.Init( SHADER_DIRECTORY + "fontVertex.glsl", SHADER_DIRECTORY + "fontFragment.glsl" );
  m_fontShader.Build( );
  m_fontShader.Use( );
  
  m_currentSize = 48;
  FT_Set_Pixel_Sizes(m_arial, 0, m_currentSize);
  
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &m_arial_texture);
  glBindTexture(GL_TEXTURE_2D, m_arial_texture);
  m_fontShader.SetUniformInt( "tex", 0 );
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  glGenBuffers(1, &m_vbo);
  glEnableVertexAttribArray( 0 );
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
  glfwGetWindowSize( &m_windowWidth, &m_windowHeight );
}

void FontMan::Draw( std::wstring p_text, float p_size, float p_posX, float p_posY, unsigned int p_color )
{
  float x = p_posX;
  float y = p_posY;
  
  if( m_currentSize != (int)p_size )
  {
    m_currentSize = (int)p_size;
    FT_Set_Pixel_Sizes(m_arial, 0, m_currentSize);
  }
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  m_fontShader.Use();
  m_fontShader.SetUniformVector( "color", glm::vec4( (p_color >> 24) & 0xFF, (p_color >> 16) & 0xFF, (p_color >> 8) & 0xFF, p_color & 0xFF ) );
  
  for(const wchar_t* p = p_text.c_str(); *p; p++)
  {
    if(FT_Load_Char(m_arial, *p, FT_LOAD_RENDER))
        continue;
 
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_ALPHA,
      m_arial->glyph->bitmap.width,
      m_arial->glyph->bitmap.rows,
      0,
      GL_ALPHA,
      GL_UNSIGNED_BYTE,
      m_arial->glyph->bitmap.buffer
    );
      
    float sx = 2.0f / m_windowWidth;
    float sy = 2.0f / m_windowHeight;
    
    float x2 = x + m_arial->glyph->bitmap_left * sx;
    float y2 = -y - m_arial->glyph->bitmap_top * sy;
    float w = m_arial->glyph->bitmap.width * sx;
    float h = m_arial->glyph->bitmap.rows * sy;

    GLfloat box[4][4] = {
        {x2,     -y2    , 0, 0},
        {x2 + w, -y2    , 1, 0},
        {x2,     -y2 - h, 0, 1},
        {x2 + w, -y2 - h, 1, 1},
    };
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    x += (m_arial->glyph->advance.x >> 6) * sx;
    y += (m_arial->glyph->advance.y >> 6) * sy;
  }
}
