#include "Paddle.h"


Paddle::Paddle(int p_PosX, int p_posY, int p_Width, int p_height, int p_screenWidth)
{
	m_posX = p_PosX - p_Width/2;
	m_posY = p_posY;
	m_Width = p_Width;
	m_height = p_height;
	m_screenWidth = p_screenWidth;
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
	m_posX = p_mousePosX;

	if(m_posX > m_screenWidth - m_Width)
		m_posX = m_screenWidth - m_Width;
	else if (m_posX < 0)
		m_posX = 0;
}

void Paddle::Render()
{
	m_renderComp->RenderObject(BoundingBox(m_posX, m_posY), PADDLE); //PADDLE == enum OH REALLY?!
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
	l_bBox.Width = m_Width;
	l_bBox.Height = m_height;
	l_bBox.PosX = m_posX;
	l_bBox.PosY = m_posY;

	return l_bBox;
}

void Paddle::SetWidth( int p_Width )
{
	m_Width = p_Width;
}

void Paddle::SetHeight( int p_height )
{
	m_height = p_height;
}

