#include "Camera.h"

#include "glm/ext.hpp"

Camera::Camera( )
		: viewMatrix( 1.f ), yaw(0), pitch(0), roll(0)
{
}

void Camera::SetPosition( const glm::vec3 _pos)
{
  position = _pos;
}

void Camera::SetYawPitch( const float _y, const float _p )
{
  yaw = _y;
  pitch = _p;
}

void Camera::SetRoll( const float _r )
{
  roll = _r;
}

void Camera::SetClip( const float _near, const float _far )
{
  nearClip = _near;
  farClip = _far;
}

void Camera::SetResolution( const int _width, const int _height)
{
  width = _width;
  height = _height;
}

void Camera::SetFoV( const float _fov )
{
  fov = _fov;
}

glm::mat4 Camera::GetViewMatrix( )
{
  return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix( )
{
  return projectionMatrix;
}

void Camera::UpdateViewMatrix( )
{
  viewMatrix = glm::translate(
    glm::rotate(
      glm::rotate(
        glm::rotate(
          glm::mat4( 1.f ),
          -pitch,
          glm::vec3( 1.f, 0.f, 0.f )
        ),
        yaw,
        glm::vec3( 0.f, 1.f, 0.f )
      ),
      roll,
      glm::vec3( 0.f, 0.f, 1.f )
    ),
    -position
  );
}

void Camera::UpdateProjectionMatrix( )
{
  projectionMatrix = glm::perspective(
    fov,
    (float)width / height,
    nearClip,
    farClip
  );
}
