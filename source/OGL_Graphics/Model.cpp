#include "Model.h"

#include "TGALoader.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <fstream>
#include <vector>
#include <cstdio>

// Parses the object data from an .obj file and stores it in the model
bool LoadOBJ( std::string p_dir, std::string p_fileName, Model &p_model );
extern std::string stringf( const char *p_fmt, ... );

Model::Model( )
  : m_mtl( 0 )
{
}

Model::~Model()
{
  glDeleteVertexArrays( 1, &m_handleVAO );
  delete m_mtl;
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

void Model::Render( Shader &p_shader, glm::vec3 p_tint )
{
  glBindVertexArray( m_handleVAO ); // bind VAO
  m_mtl->Apply( p_shader );
  
  p_shader.SetUniformVector( "intensityDiffuse", p_tint ); // override diffuse intensity with tint

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
  
  glm::vec3 l_min_val = glm::vec3(0);
  glm::vec3 l_max_val = glm::vec3(0);

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
#ifdef DEBUG
					printf( "New Material: %s\n", tmpstr.c_str( ) );
#endif
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
#ifdef DEBUG
					printf( "Ambient texture: " );
#endif

					tga_data_t* l_mapAmbient = tga_data_load( ( dir + tmpstr + TEXTURE_EXT).c_str( ) );
          model.m_mtl->m_coefficientAmbient = glm::vec3(0);
          
          glGenTextures( 1, &model.m_mtl->m_mapAmbient );
          glBindTexture( GL_TEXTURE_2D, model.m_mtl->m_mapAmbient );
          
          if( l_mapAmbient->depth/8 == 3 ) // RGB
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, l_mapAmbient->w, l_mapAmbient->h, 0, GL_RGB, GL_UNSIGNED_BYTE, l_mapAmbient->data);
          else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, l_mapAmbient->w, l_mapAmbient->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_mapAmbient->data);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          
          free( l_mapAmbient->data );
          free( l_mapAmbient );
				}
				if( tmpstr.compare( "map_Kd" ) == 0 )
				{
					mtlf >> tmpstr;
#ifdef DEBUG
					printf( "Diffuse texture: " );
#endif

					tga_data_t* l_mapDiffuse = tga_data_load( ( dir + tmpstr + TEXTURE_EXT ).c_str( ) );
          model.m_mtl->m_coefficientDiffuse = glm::vec3(0);
          
          glGenTextures( 1, &model.m_mtl->m_mapDiffuse );
          glBindTexture( GL_TEXTURE_2D, model.m_mtl->m_mapDiffuse );
          
          if( l_mapDiffuse->depth/8 == 3 ) // RGB
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, l_mapDiffuse->w, l_mapDiffuse->h, 0, GL_RGB, GL_UNSIGNED_BYTE, l_mapDiffuse->data);
          else // RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, l_mapDiffuse->w, l_mapDiffuse->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_mapDiffuse->data);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          
          free( l_mapDiffuse->data );
          free( l_mapDiffuse );
				}
				if( tmpstr.compare( "map_Ks" ) == 0 )
				{
					mtlf >> tmpstr;
#ifdef DEBUG
					printf( "Specular texture: " );
#endif

					tga_data_t* l_mapSpecular = tga_data_load( ( dir + tmpstr + TEXTURE_EXT ).c_str( ) );
          model.m_mtl->m_coefficientSpecular = glm::vec3(0);
          
          glGenTextures( 1, &model.m_mtl->m_mapSpecular );
          glBindTexture( GL_TEXTURE_2D, model.m_mtl->m_mapSpecular );
          
          if( l_mapSpecular->depth/8 == 3 ) // RGB
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, l_mapSpecular->w, l_mapSpecular->h, 0, GL_RGB, GL_UNSIGNED_BYTE, l_mapSpecular->data);
          else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, l_mapSpecular->w, l_mapSpecular->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_mapSpecular->data);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          
          free( l_mapSpecular->data );
          free( l_mapSpecular );
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
#ifdef DEBUG
			printf("Loading mesh '%s'\n", tmpstr.c_str());
#endif
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
        
        // Update min and max values of model to find the current scale of the model
        if( tmpv3.x < l_min_val.x )
          l_min_val.x = tmpv3.x;
        if( tmpv3.y < l_min_val.y )
          l_min_val.y = tmpv3.y;
        if( tmpv3.z < l_min_val.z )
          l_min_val.z = tmpv3.z;
          
        if( tmpv3.x > l_max_val.x )
          l_max_val.x = tmpv3.x;
        if( tmpv3.y > l_max_val.y )
          l_max_val.y = tmpv3.y;
        if( tmpv3.z > l_max_val.z )
          l_max_val.z = tmpv3.z;
        
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
        
        // Normalize model scaling
        glm::vec3 l_diff = 1.f/(l_max_val - l_min_val);
        glm::vec3 l_vertex = vertices[tmpi-1];
        l_vertex.x = l_vertex.x * l_diff.x;
        l_vertex.y = l_vertex.y * l_diff.y;
        l_vertex.z = l_vertex.z * l_diff.z;

				vertexData->push_back(l_vertex.x);
				vertexData->push_back(l_vertex.y);
				vertexData->push_back(l_vertex.z);

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
#ifdef DEBUG
	printf("Successfully loaded object\n");
	printf(" %d vertices, %d indices\n", (int)vertexData->size( ) / 8, (int)indices->size( ) );
#endif
#pragma endregion

  model.m_vertexCount = indices->size();

  // Make a new vertex buffer object
  glGenBuffers(1, &(model.m_handleVBO));

  // "Bind" (switch focus to) first buffer
  glBindBuffer(GL_ARRAY_BUFFER, model.m_handleVBO);
  glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(float), vertexData->data(), GL_STATIC_DRAW);

	delete vertexData;
	delete indices;

	return true;
}
