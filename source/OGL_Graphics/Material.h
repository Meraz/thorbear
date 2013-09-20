#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"

#define GL_TEXOFFSET_AMBIENT 1
#define GL_TEXOFFSET_DIFFUSE 2
#define GL_TEXOFFSET_SPECULAR 3

class Material
{
public:
	float m_transparency;
	int m_illuminationModel;

	glm::vec3 m_coefficientAmbient, m_coefficientDiffuse, m_coefficientSpecular;
	GLuint m_mapAmbient, m_mapDiffuse, m_mapSpecular;

	Material( );
  ~Material( );
  
  void Apply( Shader& p_shader );
};

#endif
