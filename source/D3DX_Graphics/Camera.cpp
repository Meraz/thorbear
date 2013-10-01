#include "Camera.h"

Camera::Camera()
{
	m_position = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_right    = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_up       = D3DXVECTOR3(0.0f, 1.0f, -0.2f);
	m_look     = D3DXVECTOR3(0.0f, 0.2f, 1.0f);

	D3DXMatrixIdentity(&m_view);
	D3DXMatrixIdentity(&m_proj);

	m_speed			= 50.0f;
	m_deltaSpeed	= 0.0f;
}

Camera::~Camera()
{
}

D3DXVECTOR3& Camera::GetPos()
{
	return m_position;
}

void Camera::SetYPosition(float p_y)
{
	m_position.y = p_y;
}

D3DXMATRIX Camera::GetViewMatrix()const
{
	return m_view;
}

D3DXMATRIX Camera::GetProjMatrix()const
{
	return m_proj;
}

void Camera::SetLens(float p_fovY, float p_aspect, float p_znear, float p_zfar)
{
	D3DXMatrixPerspectiveFovLH(&m_proj, p_fovY, p_aspect, p_znear, p_zfar);
}


void Camera::Pitch(float p_angle)
{
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_right, p_angle);

	D3DXVec3TransformNormal(&m_up, &m_up, &R);
	D3DXVec3TransformNormal(&m_look, &m_look, &R);
}

void Camera::RotateY(float p_angle)
{
	D3DXMATRIX R;
	D3DXMatrixRotationY(&R, p_angle);

	D3DXVec3TransformNormal(&m_right, &m_right, &R);
	D3DXVec3TransformNormal(&m_up, &m_up, &R);
	D3DXVec3TransformNormal(&m_look, &m_look, &R);
}

void Camera::Update( float p_dt )
{
	m_deltaSpeed = m_speed * p_dt;

	RebuildView();
}

void Camera::RebuildView()
{
	// Keep camera's axes orthogonal to each other and of unit length.
	D3DXVec3Normalize(&m_look, &m_look);

	D3DXVec3Cross(&m_up, &m_look, &m_right);
	D3DXVec3Normalize(&m_up, &m_up);

	D3DXVec3Cross(&m_right, &m_up, &m_look);
	D3DXVec3Normalize(&m_right, &m_right);

	// Fill in the GetViewMatrix matrix entries.
	float x = -D3DXVec3Dot(&m_position, &m_right);
	float y = -D3DXVec3Dot(&m_position, &m_up);
	float z = -D3DXVec3Dot(&m_position, &m_look);

	m_view(0,0) = m_right.x; 
	m_view(1,0) = m_right.y; 
	m_view(2,0) = m_right.z; 
	m_view(3,0) = x;   

	m_view(0,1) = m_up.x;
	m_view(1,1) = m_up.y;
	m_view(2,1) = m_up.z;
	m_view(3,1) = y;  

	m_view(0,2) = m_look.x; 
	m_view(1,2) = m_look.y; 
	m_view(2,2) = m_look.z; 
	m_view(3,2) = z;   

	m_view(0,3) = 0.0f;
	m_view(1,3) = 0.0f;
	m_view(2,3) = 0.0f;
	m_view(3,3) = 1.0f;
}

void Camera::SetCamSpeed( float p_speed )
{
	m_speed = p_speed;
}

float Camera::GetCamSpeed()
{
	return m_speed;
}

void Camera::StrafeRight()
{
	m_position += m_deltaSpeed*m_right;
}

void Camera::StrafeLeft()
{
	m_position += -m_deltaSpeed*m_right;
}

void Camera::WalkForward()
{
	m_position += m_deltaSpeed*m_look;
}

void Camera::WalkBackward()
{
	m_position += -m_deltaSpeed*m_look;
}

void Camera::MoveUpY()
{
	m_position.y += m_deltaSpeed;
}

void Camera::MoveDownY()
{
	m_position.y -= m_deltaSpeed;
}

D3DXVECTOR3 Camera::GetLookAtVec()
{
	return m_look;
}

D3DXVECTOR3 Camera::GetRightVec()
{
	return m_right;
}

void Camera::SetPos( int p_x, int p_y, int p_z )
{
	m_position = D3DXVECTOR3((float)p_x, (float)p_y, (float)p_z);
}