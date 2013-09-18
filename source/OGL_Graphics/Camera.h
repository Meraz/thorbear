#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

class Camera
{
	glm::vec3 position;
	float yaw; // Y
	float pitch; // X
	float roll; // Z

	float nearClip;
	float farClip;

	int width;
	int height;

	float fov;

public:

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
  
	Camera( );

	void SetPosition( const glm::vec3& _pos);
	void SetYawPitch( const float& _y, const float& _p );
	void SetRoll( const float& _r );

	void SetClip( const float& _near, const float& _far );
	void SetResolution( const int& _width, const int& _height);
	void SetFoV( const float& _fov );

	glm::mat4& GetViewMatrix( );
	glm::mat4& GetProjectionMatrix( );

	void UpdateViewMatrix( );
	void UpdateProjectionMatrix( );
};

#endif