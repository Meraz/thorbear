#include "Material.h"

#include <string>

Material::Material( ) : name( "" ), m_coefficientAmbient( 0 ), m_coefficientDiffuse( 0 ),
  m_coefficientSpecular( 0 ), m_transparency( 0 ), m_illuminationModel( 0 ), m_mapAmbient( 0 ), m_mapDiffuse( 0 ),
  m_mapSpecular( 0 )
{
}

Material::~Material( )
{
  glDeleteTextures( 1, &m_mapAmbient );
  glDeleteTextures( 1, &m_mapDiffuse );
  glDeleteTextures( 1, &m_mapSpecular );
}

void Material::Apply( Shader& p_shader )
{
  p_shader.SetUniformInt( "mapAmbient", GL_TEXOFFSET_AMBIENT );
  p_shader.SetUniformInt( "mapDiffuse", GL_TEXOFFSET_DIFFUSE );
  p_shader.SetUniformInt( "mapSpecular", GL_TEXOFFSET_SPECULAR );
  // These shoudl equal 0 if there is a texture bound
  p_shader.SetUniformVector( "coefficientAmbient", m_coefficientAmbient ); // material's ambient coefficient
  p_shader.SetUniformVector( "coefficientDiffuse", m_coefficientDiffuse ); // material's diffuse coefficient
  p_shader.SetUniformVector( "coefficientSpecular", m_coefficientSpecular ); // material's specular coefficient
}