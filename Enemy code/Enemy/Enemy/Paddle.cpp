#include "Paddle.h"


Paddle::Paddle(int p_posX, int p_posY, int p_width, int p_height, int p_screenWidth)
{
	m_posX = p_posX - p_width/2;
	m_posY = p_posY;
	m_width = p_width;
	m_height = p_height;
	m_screenWidth = p_screenWidth;
}

Paddle::~Paddle(void)
{
}

void Paddle::Update(int p_mousePosX)
{
	m_posX = p_mousePosX;

	if(m_posX > m_screenWidth - m_width)
		m_posX = m_screenWidth - m_width;
	else if (m_posX < 0)
		m_posX = 0;
	

}

void Paddle::Render()
{
	//m_renderComp->RenderObject(m_bBox, PADDLE) //PADDLE == enum
}

int Paddle::GetPosX()
{
	return m_posX;
}

int Paddle::GetPosY()
{
	return m_posY;
}

BoundingBox Paddle::GetBoundingBox()
{
	BoundingBox l_bBox;
	l_bBox.width = m_width;
	l_bBox.height = m_height;
	l_bBox.farTopLeftX = m_posX;
	l_bBox.farTopLeftY = m_posY;

	return l_bBox;
}
/*
void Paddle::SetGraphicalInterface(RenderComponentInterface* p_renderComp)
{
	m_renderComp = p_renderComp;
}
*/

void Paddle::SetWidth( int p_width )
{
	m_width = p_width;
}

void Paddle::SetHeight( int p_height )
{
	m_height = p_height;
}

