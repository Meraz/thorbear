#include "Model.h"

#include "TGALoader.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <fstream>
#include <vector>
#include <cstdio>

// Parses the object data from an .obj file and stores it in the model
bool LoadOBJ( std::string p_dir, std::string p_fileName, Model &p_model );
extern inline std::string stringf( const char *p_fmt, ... );

Model::Model( )
  : m_mtl( 0 )
{
}

Model::~Model()
{
  glDeleteVertexArrays( 1, &m_handleVAO );
}

bool Model::Load( std::string p_dir, std::string p_fileName )
{
  // create 1 VAO
  glGenVertexArrays( 1, &m_handleVAO );
  glBindVertexArray( m_handleVAO );
  
  if( !LoadOBJ( p_dir, p_fileName, (*this) ) )
  {
    printf( "Failed to load model.\n" );
    return false;
  }
  
  // "Bind" (switch focus to) first buffer
  //glBindBuffer( GL_ARRAY_BUFFER, m_handleVBO );
  // map index 0 to vertice buffer
  glEnableVertexAttribArray( 0 ); // vertices
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ) , ( GLubyte* )NULL );
  // map index 2 to vertice uv buffer
  glEnableVertexAttribArray( 1 ); // vertice uv
  glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), ( GLubyte* )NULL + 3 * sizeof( float ) );
  // map index 1 to vertice normal buffer
  glEnableVertexAttribArray( 2 ); // vertice normals
  glVertexAttribPointer( 2, 3, GL_FLOAT, GL_TRUE, 8 * sizeof( float ), ( GLubyte* )NULL + 5 * sizeof( float ) );
    
  glBindVertexArray( 0 ); // disable VAO
  return true;
}

void Model::Render( Shader &p_shader )
{
  m_mtl->Apply( p_shader );
  
  p_shader.SetUniformVector( "intensityAmbient", glm::vec3(0.01f) ); // ambient intensity
  p_shader.SetUniformVector( "intensityDiffuse", glm::vec3(0.8f) ); // diffuse intensity
  p_shader.SetUniformFloat( "powerSpecular", 2000.0f); // specular intensity
  p_shader.SetUniformVector( "intensitySpecular", glm::vec3(0.5f) ); // specular intensity

  glBindVertexArray( m_handleVAO ); // bind VAO
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
		printf( "Error opening file: %s!\n", ( dir + fileName ).c_str( ) );
    return false;
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
				printf("MTL library %s referenced in the object file could not be read!\n", tmpstr.c_str());
        break;
			}

#pragma region ParseMTL
			skip = false;
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
					printf( "New Material: %s\n", tmpstr.c_str( ) );
					model.m_mtl = new Material( );
					//mtls.push_back( mtl );
				}
				if( tmpstr.compare( "Ka" ) == 0 )
					mtlf >> model.m_mtl->m_coefficientAmbient.x >> model.m_mtl->m_coefficientAmbient.y >> model.m_mtl->m_coefficientAmbient.z;
				if( tmpstr.compare( "Kd" ) == 0 )
					mtlf >> model.m_mtl->m_coefficientDiffuse.x >> model.m_mtl->m_coefficientDiffuse.y >> model.m_mtl->m_coefficientDiffuse.z;
				if( tmpstr.compare( "Ks" ) == 0 )
					mtlf >> model.m_mtl->m_coefficientSpecular.x >> model.m_mtl->m_coefficientSpecular.y >> model.m_mtl->m_coefficientSpecular.z;
				if( tmpstr.compare( "d" ) == 0 || tmpstr.compare( "Tr" ) == 0  )
					mtlf >> model.m_mtl->m_transparency;
				if( tmpstr.compare( "illum" ) == 0 )
					mtlf >> model.m_mtl->m_illuminationModel;
				if( tmpstr.compare( "map_Ka" ) == 0 )
				{
					mtlf >> tmpstr;
					printf( "Ambient texture: " );

					tga_data_t* l_mapAmbient = tga_data_load( ( dir + tmpstr ).c_str( ) );
          model.m_mtl->m_coefficientAmbient = glm::vec3(0);
          
          glGenTextures( 1, &model.m_mtl->m_mapAmbient );
          glBindTexture( GL_TEXTURE_2D, model.m_mtl->m_mapAmbient );
          
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, l_mapAmbient->w, l_mapAmbient->h, 0, GL_RGB, GL_UNSIGNED_BYTE, l_mapAmbient->data);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          
          delete l_mapAmbient;
				}
				if( tmpstr.compare( "map_Kd" ) == 0 )
				{
					mtlf >> tmpstr;
					printf( "Diffuse texture: " );

					tga_data_t* l_mapDiffuse = tga_data_load( ( dir + tmpstr ).c_str( ) );
          model.m_mtl->m_coefficientDiffuse = glm::vec3(0);
          
          glGenTextures( 1, &model.m_mtl->m_mapDiffuse );
          glBindTexture( GL_TEXTURE_2D, model.m_mtl->m_mapDiffuse );
          
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, l_mapDiffuse->w, l_mapDiffuse->h, 0, GL_RGB, GL_UNSIGNED_BYTE, l_mapDiffuse->data);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          
          delete l_mapDiffuse;
				}
				if( tmpstr.compare( "map_Ks" ) == 0 )
				{
					mtlf >> tmpstr;
					printf( "Specular texture: " );

					tga_data_t* l_mapSpecular = tga_data_load( ( dir + tmpstr ).c_str( ) );
          model.m_mtl->m_coefficientSpecular = glm::vec3(0);
          
          glGenTextures( 1, &model.m_mtl->m_mapSpecular );
          glBindTexture( GL_TEXTURE_2D, model.m_mtl->m_mapSpecular );
          
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, l_mapSpecular->w, l_mapSpecular->h, 0, GL_RGB, GL_UNSIGNED_BYTE, l_mapSpecular->data);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          
          delete l_mapSpecular;
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
	printf(" %d vertices, %d indices\n", (int)vertexData->size( ) / 8, (int)indices->size( ) );
#pragma endregion

  model.m_vertexCount = indices->size();

  // Make a new vertex buffer object
  glGenBuffers(1, &(model.m_handleVBO));

  // "Bind" (switch focus to) first buffer
  glBindBuffer(GL_ARRAY_BUFFER, model.m_handleVBO);
  glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(float), vertexData->data(), GL_STATIC_DRAW);


	return true;
}