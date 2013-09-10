#ifndef PADDLE_H
#define PADDLE_H

#include <Windows.h>
using namespace std;

struct BoundingBox
{
	int	Width;
	int	Height;
	POINT Position;
};

class Paddle
{

public:
	Paddle(POINT p_pos, int p_width, int p_height);
	~Paddle(void);

	void	Render();
	void	Update();
	
	POINT		GetPos();
	BoundingBox	GetBoundingBox();
	void		SetWidth(int p_width);
	void		SetHeight(int p_height);

private:
	POINT	m_pos;
	int		m_width;
	int		m_height;

	

};

#endif