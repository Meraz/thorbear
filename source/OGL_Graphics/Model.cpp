#include "Model.h"

// Parses the object data from an .obj file and stores it in the model
bool LoadOBJ( std::string dir, std::string fileName, Model &model );

Model::Model( )
  : ka( 0 ), kd( 0 ), ks( 0 ), tf( 0 ), d( 0 ), illum( 0 ),
		map_ka( 0 ), map_kd( 0 ), map_ks( 0 )
{
}

Model::~Model()
{
  glDeleteVertexArrays(1, m_handleVAO);
}

bool Load( std::string p_dir, std::string p_fileName, Shader &p_shader )
{
  if( !LoadOBJ( p_dir, p_fileName, (*this) ) )
  {
    throw stringf( "Failed to load model" );
    return false;
  }
  m_vertexCount = indices->size();
  // objShader.Init( "Resources/GenericShaders/vertex.glsl", "Resources/GenericShaders/fragment.glsl" );
  // objShader.Build( );
  // objShader.Use( );

  glGenTextures(1, &m_texID);
  
  glBindTexture(GL_TEXTURE_2D, m_texID);
  if( map_kd != NULL )
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, map_kd->w, map_kd->h, 0, GL_RGB, GL_UNSIGNED_BYTE, map_kd->data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }
  else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

  p_shader.SetUniformInt( "map_Kd", 0 );
    
  p_shader.SetUniformVector( "Ka", ka ); // material's ambient coefficient
  p_shader.SetUniformVector( "Ia", glm::vec3(0.01f) ); // ambient intensity
  p_shader.SetUniformVector( "Kd", kd ); // material's diffuse coefficient
  p_shader.SetUniformVector( "Id", glm::vec3(0.8f) ); // diffuse intensity
  p_shader.SetUniformVector( "Ks", ks ); // material's specular coefficient
  p_shader.SetUniformFloat( "c3", 2000.0f); // specular intensity
  p_shader.SetUniformVector( "Is", glm::vec3(0.5f) ); // specular intensity
  
  p_shader.modelMatrix = glm::translate( 300, 50, 200 );
  
  // create 1 VAO
  glGenVertexArrays(1, &m_handleVAO);
  glBindVertexArray(m_handleVAO);

  // enable "vertex attribute arrays"
  glEnableVertexAttribArray(0); // vertices
  //glBindAttribLocation( shaderProgHandle, 0, "vertexPosition");
  glEnableVertexAttribArray(1); // vertice uv
  //glBindAttribLocation( shaderProgHandle, 1, "vertexUV");
  glEnableVertexAttribArray(2); // vertice normals
  //glBindAttribLocation( shaderProgHandle, 2, "vertexNormal");
  //glEnableVertexAttribArray(3); // face vertice normals

  // "Bind" (switch focus to) first buffer
  glBindBuffer(GL_ARRAY_BUFFER, m_handleVBO);
  //glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(float), vertexData->data(), GL_STATIC_DRAW);
  // map index 0 to vertice buffer
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ) , ( GLubyte* )NULL );
  // map index 2 to vertice uv buffer
  glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), ( GLubyte* )NULL + 3 * sizeof( float ) );
  // map index 1 to vertice normal buffer
  glVertexAttribPointer( 2, 3, GL_FLOAT, GL_TRUE, 8 * sizeof( float ), ( GLubyte* )NULL + 5 * sizeof( float ) );
    
  glBindVertexArray(0); // disable VAO
  return true;
}

void Render( Shader &p_shader )
{
  p_shader.SetUniformMatrix( "modelMatrix", this->m_modelMatrix );
  // TODO: Graphics::UpdateUniform( p_shader );

  glActiveTexture( GL_TEXTURE0 );
  glBindTexture( GL_TEXTURE_2D, m_texID );

  glBindVertexArray( VAOHandle ); // bind VAO

  glDrawArrays( GL_TRIANGLES, 0, m_vertexCount );
}

//int LoadOBJ( std::string dir, std::string fileName, std::vector<float>* &vertexData, std::vector<unsigned int>* &indices, std::vector< MTL* >* &mtls)
bool LoadOBJ( std::string dir, std::string fileName, Model &model )
{
	std::fstream f;
	std::fstream mtlf;
	char tmp = ' ';
	std::string tmpstr;
	float tmpf = 0.f;
	int tmpi = 0;
	glm::vec3 tmpv3;
	glm::vec2 tmpv2;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> verticeUV;
	std::vector<glm::vec3> verticeNormals;
	std::vector<int> indexVUV;
	std::vector<int> indexVN;

	std::vector<float>* vertexData = new std::vector<float>();
	std::vector<unsigned int>* indices = new std::vector<unsigned int>();
	//std::vector< MTL* > mtls;

#pragma region FileParse
	f.open( ( dir + fileName ).c_str( ) );

	if (f.fail())
	{
		//printf("Error opening .obj file!\n");
		throw stringf( "Error opening .obj file!\n" );
	}

	bool skip = false;
	while (!f.eof())
	{
		f >> tmp;

		if (tmp == '#')
			skip = true;

		if (skip == true)
		{
			if (f.peek() == '\n' || f.peek() == '\r')
				skip = false;
			continue;
		}

		switch (tmp)
		{
		case 'm':
			f >> tmpstr;
			if( tmpstr.compare( "tllib" ) != 0 )
			{
				skip = true;
				break;
			}
			f >> tmpstr;
			mtlf.open( ( dir + tmpstr ).c_str( ) );
			if( mtlf.fail() )
			{
				throw stringf("MTL library m%s referenced in the object file could not be read!\n", tmpstr);
			}

#pragma region ParseMTL
			skip = false;
			MTL* mtl;
			while (!mtlf.eof())
			{
				if (f.peek() == '#')
					skip = true;

				if (skip == true)
				{
					mtlf >> tmp;

					if (f.peek() == '\n' || f.peek() == '\r')
						skip = false;
					continue;
				}
				mtlf >> tmpstr;

				if( tmpstr.compare( "newmtl" ) == 0 )
				{
					mtlf >> tmpstr;
					printf( "New MTL: %s\n", tmpstr.c_str( ) );
					mtl = new MTL( );
					//mtls.push_back( mtl );
				}
				if( tmpstr.compare( "Ka" ) == 0)
					mtlf >> model.ka.x >> model.ka.y >> model.ka.z;
				if( tmpstr.compare( "Kd" ) == 0)
					mtlf >> model.kd.x >> model.kd.y >> model.kd.z;
				if( tmpstr.compare( "Ks" ) == 0)
					mtlf >> model.ks.x >> model.ks.y >> model.ks.z;
				if( tmpstr.compare( "d" ) == 0)
					mtlf >> model.d;
				/*if( tmpstr.compare( "d" ) == 0)
					mtlf >> model.d;*/
				if( tmpstr.compare( "illum" ) == 0)
					mtlf >> model.illum;
				if( tmpstr.compare( "map_Ka" ) == 0 )
				{
					mtlf >> tmpstr;
					printf( "Ambient texture: %s\n", ( dir + tmpstr ).c_str( ) );

					model.map_ka = tga_data_load( ( dir + tmpstr ).c_str( ) );
				}
				if( tmpstr.compare( "map_Kd" ) == 0 )
				{
					mtlf >> tmpstr;
					printf( "Diffuse texture: %s\n", ( dir + tmpstr ).c_str( ) );

					model.map_kd = tga_data_load( ( dir + tmpstr ).c_str( ) );
				}
				if( tmpstr.compare( "map_Ks" ) == 0 )
				{
					mtlf >> tmpstr;
					printf( "Specular texture: %s\n", ( dir + tmpstr ).c_str( ) );

					model.map_ks = tga_data_load( ( dir + tmpstr ).c_str( ) );
				}
				else
				{
					if (f.peek() != '\n' && f.peek() != '\r')
						skip = true;
				}
			}
#pragma endregion
			break;
		case 'g': // mesh name or something
			f >> tmpstr;
			printf("Loading mesh '%s'\n", tmpstr.c_str());
			break;
		case 'v': // vertex or vertex normal, or vertex uv
			if (f.peek() == 'n') // vertex normal
			{
				f >> tmp; // remove the 'n' from the buffer
				//printf("\nVertex normal: ");
				for (int i = 0; i < 3; i++)
				{
					f >> tmpv3[i];
					//printf("%f ", tmpf);
				}
				verticeNormals.push_back(tmpv3);
				if (f.peek() != '\n' && f.peek() != '\r')
				{
					throw stringf( "Unexpected symbol." );
				}
			}
			else if (f.peek() == 't') // vertex uv
			{
				f >> tmp; // remove the 't' from the buffer
				//printf("\nVertex UV: ");
				for (int i = 0; i < 2; i++)
				{
					f >> tmpv2[i];
					//printf("%f ", tmpf);
				}
				verticeUV.push_back(tmpv2);
				if (f.peek() != '\n' && f.peek() != '\r')
				{
					throw stringf( "Unexpected symbol." );
				}
			}
			else // vertex
			{
				//printf("\nVertex: ");
				for (int i = 0; i < 3; i++)
				{
					f >> tmpv3[i];
					//printf("%f ", tmpf);
				}
				vertices.push_back(tmpv3);
				if (f.peek() != '\n' && f.peek() != '\r')
				{
					throw stringf( "Unexpected symbol." );
				}
			}
			break;
		case 'f': // face
			//printf("\nFace: ");
			for (int i = 0; i < 3; i++)
			{
				f >> tmpi;
				indices->push_back(tmpi-1);
				//printf("%i", tmpi);

				vertexData->push_back(vertices[tmpi-1].x);
				vertexData->push_back(vertices[tmpi-1].y);
				vertexData->push_back(vertices[tmpi-1].z);

				f >> tmp;
				if (tmp != '/')
					throw stringf( "Unexpected symbol." );
				if (f.peek() != '/')
				{
					f >> tmpi;
					indexVUV.push_back(tmpi-1);
					//printf("/%i ", tmpi);

					vertexData->push_back(verticeUV[tmpi-1].x);
					vertexData->push_back(verticeUV[tmpi-1].y);
				}
				else
				{
					//printf("/");
					
					vertexData->push_back(0);
					vertexData->push_back(0);
				}

				f >> tmp;
				if (tmp != '/')
					throw stringf( "Unexpected symbol." );
				if (f.peek() != ' ' && f.peek() != '\n' && f.peek() != '\r')
				{
					f >> tmpi;
					indexVN.push_back(tmpi-1);
					//printf("/%i ", tmpi);
					
					vertexData->push_back(verticeNormals[tmpi-1].x);
					vertexData->push_back(verticeNormals[tmpi-1].y);
					vertexData->push_back(verticeNormals[tmpi-1].z);
				}
				else
				{
					//printf("/");
					
					vertexData->push_back(0);
					vertexData->push_back(0);
					vertexData->push_back(0);
				}
			}
			if (f.peek() != ' ' && f.peek() != '\n' && f.peek() != '\r')
					throw stringf( "Unexpected symbol." );

			break;
		default:
			if (f.peek() != '\n' && f.peek() != '\r')
				skip = true;

			break;
		}
	}

	printf("Successfully loaded object\n");
	printf(" %d vertices, %d indices\n", vertexData->size( ) / 8, indices->size( ) );
#pragma endregion

  model.m_vertexCount = indices->size();

  // Make a new vertex buffer object
  glGenBuffers(1, &(model->m_handleVBO));

  // "Bind" (switch focus to) first buffer
  glBindBuffer(GL_ARRAY_BUFFER, model->m_handleVBO);
  glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(float), vertexData->data(), GL_STATIC_DRAW);


	return true;
}