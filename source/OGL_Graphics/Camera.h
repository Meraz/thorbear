#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

class Camera
{
	glm::vec3 m_position;
	float m_yaw; // Y
	float m_pitch; // X
	float m_roll; // Z

	float m_nearClip;
	float m_farClip;

	int m_width;
	int m_height;

	float m_fov;

public:

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
  
	Camera( );

	void SetPosition( const glm::vec3 p_pos);
	glm::vec3 GetPosition( );
	void SetYawPitch( const float p_y, const float p_p );
	void SetRoll( const float p_r );

	void SetClip( const float p_near, const float p_far );
	void SetResolution( const int p_width, const int p_height);
	void SetFoV( const float p_fov );

	glm::mat4 GetViewMatrix( );
	glm::mat4 GetProjectionMatrix( );

	void UpdateViewMatrix( );
	void UpdateProjectionMatrix( );
};

#endif