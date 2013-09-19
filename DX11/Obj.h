#ifndef OBJ_H
#define OBJ_H

#include "d3dUtil.h"
#include <string>
#include "ModelLoader.h"
#include "Shader.h"

using namespace std;

class Obj
{
public:
	Obj(ID3D11Device* p_d3dDevice, ID3D11DeviceContext* p_context, Shader* p_shader, float p_x, float p_y, float p_z, Model* p_model);
	~Obj();

	void SetScale(float p_XScale, float p_YScale, float p_ZScale);

	void SetXRotation(float p_rotation);
	void SetYRotation(float p_rotation);
	void SetZRotation(float p_rotation);

	void SetXPosition(float p_position);
	void SetYPosition(float p_position);
	void SetZPosition(float p_position);

	float GetXScale();
	float GetYScale();
	float GetZScale();

	float GetXRotation();
	float GetYRotation();
	float GetZRotation();

	float GetXPosition();
	float GetYPosition();
	float GetZPosition();

	void Update(float p_dt);

	void Draw(D3DXMATRIX p_viewMatrix, D3DXMATRIX p_projMatrix, D3DXVECTOR3 p_eyePos);

private:

	ID3D11Device*	m_d3dDevice;
	ID3D11DeviceContext* m_context;

	Shader*			m_shader;

	Model*			m_model;
	
	float			m_XScale;
	float			m_YScale;
	float			m_ZScale;

	D3DXVECTOR3		m_rotation;
	D3DXVECTOR3		m_position;

	D3DXMATRIX		m_translateMat;
	D3DXMATRIX		m_rotationMatX;
	D3DXMATRIX		m_rotationMatY;
	D3DXMATRIX		m_rotationMatZ;
	D3DXMATRIX		m_scaleMat;
};
#endif
