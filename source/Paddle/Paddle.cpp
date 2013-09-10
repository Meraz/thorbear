#include "Paddle.h"


Paddle::Paddle(POINT p_pos, int p_width, int p_height)
{
	m_pos = p_pos;
	m_width = p_width;
	m_height = p_height;
}

Paddle::~Paddle(void)
{
}

void Paddle::Update()
{
	POINT l_mousePos;
	int l_screenWidth = 800; //Test variable

	GetCursorPos(&l_mousePos); //Use relative to window instead
	//ScreenToClient(hwnd, &l_mousePos); 
	m_pos.x = l_mousePos.x;

	if(m_pos.x > l_screenWidth - m_width)
		m_pos.x = l_screenWidth - m_width;
	else if (m_pos.x < 0)
		m_pos.x = 0;
	

}

void Paddle::Render()
{
	//Render the paddle
}

POINT Paddle::GetPos()
{
	return m_pos;
}

BoundingBox Paddle::GetBoundingBox()
{
	BoundingBox l_bBox;
	l_bBox.Width = m_width;
	l_bBox.Height = m_height;
	l_bBox.Position = m_pos;

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

