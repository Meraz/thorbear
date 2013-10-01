#include "Paddle.h"


Paddle::Paddle(float p_posX, float p_posY, int p_width, int p_height, int p_screenWidth)
{
	m_posX = p_width - p_posX - (p_width/2);
	m_posY = p_posY;
	m_width = p_width;
	m_height = p_height;
	m_screenWidth = p_screenWidth;
	m_prevMousePosX = 0;
	
}

Paddle::~Paddle()
{
}

void Paddle::Initialize(RenderComponentInterface* p_renderComp)
{
	m_renderComp = p_renderComp;
}

void Paddle::Update(int p_mousePosX)
{
	m_posX += p_mousePosX - m_prevMousePosX; 

	if(m_posX > m_screenWidth - m_width)
		m_posX = (float)(m_screenWidth - m_width);
	else if (m_posX < 0)
		m_posX = 0;
	
	m_prevMousePosX = p_mousePosX;
}

void Paddle::Render()
{
	m_renderComp->RenderObject(GetBoundingBox(), PADDLE, Vect3(1.0f, 1.0f, 0.0f)); //PADDLE == enum OH REALLY?!
}

float Paddle::GetPosX()
{
	return m_posX;
}

float Paddle::GetPosY()
{
	return m_posY;
}

BoundingBox Paddle::GetBoundingBox()
{
	BoundingBox l_bBox;
	l_bBox.Width = m_width;
	l_bBox.Height = m_height;
	l_bBox.PosX = m_posX;
	l_bBox.PosY = m_posY;
	l_bBox.Depth = 9;

	return l_bBox;
}

void Paddle::SetWidth( int p_width )
{
	m_width = p_width;
}

void Paddle::SetHeight( int p_height )
{
	m_height = p_height;
}

