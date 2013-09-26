#ifndef PADDLE_H
#define PADDLE_H

using namespace std;
#include "RenderComponentInterface.h"

class Paddle
{

public:
	Paddle(float p_posX, float p_posY, int p_width, int p_height, int p_screenWidth);
	~Paddle(void);
	void Initialize(RenderComponentInterface* p_renderComp);

	void	Render();
	void	Update(int p_mousePosX);
	
	float			GetPosX();
	float			GetPosY();
	BoundingBox	GetBoundingBox();
	void		SetWidth(int p_width);
	void		SetHeight(int p_height);

private:
	float		m_posX; 
	float	    m_posY;
	int		m_width;
	int		m_height;
	int		m_screenWidth;
	int		m_prevMousePosX;
	RenderComponentInterface*	m_renderComp;
};

#endif