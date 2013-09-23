#ifndef CAMERA_H
#define CAMERA_H

#include "d3dUtil.h"

// Simple camera class that lets the viewer explore the 3D scene.
//   -It keeps track of the camera coordinate system relative to the world space
//    so that the GetViewMatrix matrix can be obtained.  
//   -It keeps track of the viewing frustum of the camera so that the projection
//    matrix can be obtained.
class Camera
{
public:
	Camera();
	~Camera();

	D3DXVECTOR3& GetPos();

	D3DXMATRIX GetViewMatrix()const;
	D3DXMATRIX GetProjMatrix()const;

	void SetLens(float p_fovY, float p_aspect, float p_znear, float p_zfar);

	void StrafeRight();
	void StrafeLeft();
	void WalkForward();
	void WalkBackward();
	void MoveUpY();
	void MoveDownY();
	void SetYPosition(float p_y);
	void SetPos(int p_x, int p_y, int p_z);
	void Pitch(float p_angle);
	void RotateY(float p_angle);
	void SetCamSpeed(float p_speed);
	float GetCamSpeed();
	void Update(float p_dt);
	void RebuildView();

	D3DXVECTOR3 GetLookAtVec();
	D3DXVECTOR3 GetRightVec();

private:

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_look;

	D3DXMATRIX m_view;
	D3DXMATRIX m_proj;

	float m_speed;
	float m_deltaSpeed;

};


#endif // DEMO_CAMERA_H