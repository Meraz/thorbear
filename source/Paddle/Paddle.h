#ifndef PADDLE_H
#define PADDLE_H

#include <Windows.h>
//#include "GraphicalComponentInterface.h"
using namespace std;

struct BoundingBox
{
	int	Width;
	int	Height;
	int posX,posY;
};

class Paddle
{

public:
	Paddle(int p_posX, int p_posY, int p_width, int p_height, int p_screenWidth);
	~Paddle(void);

	void	Render();
	void	Update(int p_mousePosX);
	
	int			GetPosX();
	int			GetPosY();
	BoundingBox	GetBoundingBox();
	void		SetWidth(int p_width);
	void		SetHeight(int p_height);
	//void		SetGraphicalInterface(RenderComponentInterface* p_renderComp);

private:
	int		m_posX; 
	int	    m_posY;
	int		m_width;
	int		m_height;
	int		m_screenWidth;

	//RenderComponentInterface*	m_renderComp;

	

};

#endif