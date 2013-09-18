#ifndef MODEL_H
#define MODEL_H

class Model
{
public:
	Model();
	~Model();
  
	bool Load( std::string p_dir, std::string p_fileName, Shader &p_shader );
  
  void Render( Shader &p_shader );
  
private:
	glm::vec3 ka, kd, ks, tf;

	float d;
	int illum;

	tga_data_t *map_ka, *map_kd, *map_ks;

  int m_vertexCount;
	//std::vector< MTL* >* mtls;

	Shader objShader;
	GLuint m_handleVAO;
	GLuint m_handleVBO;

	GLuint m_texID;
  
};

#endif
