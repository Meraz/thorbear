#ifndef PADDLE_H
#define PADDLE_H

#include <Windows.h>
using namespace std;
#include "RenderComponentInterface.h"

class Paddle
{

public:
	Paddle(int p_PosX, int p_posY, int p_Width, int p_height, int p_screenWidth);
	~Paddle(void);
	void Initialize(RenderComponentInterface* p_renderComp);

	void	Render();
	void	Update(int p_mousePosX);
	
	int			GetPosX();
	int			GetPosY();
	BoundingBox	GetBoundingBox();
	void		SetWidth(int p_Width);
	void		SetHeight(int p_height);
	void		SetGraphicalInterface(RenderComponentInterface* p_renderComp);

private:
	int		m_posX; 
	int	    m_posY;
	int		m_Width;
	int		m_height;
	int		m_screenWidth;
	RenderComponentInterface*	m_renderComp;
};

#endif