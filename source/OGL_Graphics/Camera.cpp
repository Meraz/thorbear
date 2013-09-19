#include "Camera.h"

#include "glm/ext.hpp"

Camera::Camera( )
		: m_viewMatrix( 1.f ), m_yaw(0), m_pitch(0), m_roll(0)
{
}

void Camera::SetPosition( const glm::vec3 p_pos)
{
  m_position = p_pos;
}

void Camera::SetYawPitch( const float p_y, const float p_p )
{
  m_yaw = p_y;
  m_pitch = p_p;
}

void Camera::SetRoll( const float p_r )
{
  m_roll = p_r;
}

void Camera::SetClip( const float p_near, const float p_far )
{
  m_nearClip = p_near;
  m_farClip = p_far;
}

void Camera::SetResolution( const int p_width, const int p_height)
{
  m_width = p_width;
  m_height = p_height;
}

void Camera::SetFoV( const float p_fov )
{
  m_fov = p_fov;
}

glm::mat4 Camera::GetViewMatrix( )
{
  return m_viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix( )
{
  return m_projectionMatrix;
}

void Camera::UpdateViewMatrix( )
{
  m_viewMatrix = glm::translate(
    glm::rotate(
      glm::rotate(
        glm::rotate(
          glm::mat4( 1.f ),
          -m_pitch,
          glm::vec3( 1.f, 0.f, 0.f )
        ),
        m_yaw,
        glm::vec3( 0.f, 1.f, 0.f )
      ),
      m_roll,
      glm::vec3( 0.f, 0.f, 1.f )
    ),
    -m_position
  );
}

void Camera::UpdateProjectionMatrix( )
{
  m_projectionMatrix = glm::perspective(
    m_fov,
    (float)m_width / m_height,
    m_nearClip,
    m_farClip
  );
}
