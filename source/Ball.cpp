#include "Ball.h"

#include <cstdlib>

Ball::Ball(void)
{
	m_posX = 0;
	m_posY = 0;
	m_width = 0;
	m_height = 0;
	m_speed = 0;
	m_direction.X = 0;
	m_direction.Y = 0;
	m_maxBallAngle = 170;
	m_minBallAngle = 10;
}


Ball::~Ball(void)
{
}

void Ball::Init(int p_PosX, int p_posY, int p_width, int p_height, int p_speed, BoundingBox p_mapEdges, RenderComponentInterface* p_renderComp)
{
	m_posX = p_PosX;
	m_posY = p_posY;
	m_width = p_width;
	m_height = p_height;
	m_speed = p_speed;
	m_mapEdges = p_mapEdges;
	m_renderComp = p_renderComp;
}

void Ball::ShootBall()
{
	m_isBallDead = false;
}

void Ball::Update()
{
	if (!m_isBallDead)
	{
		m_posX += m_direction.X * m_speed;
		m_posY += m_direction.Y * m_speed;
	
		CheckCollisionAgainstWalls();
		m_hasBallBouncedAgainstEnemy = false;
	}
}

void Ball::Render()
{
	m_renderComp->RenderObject(BoundingBox(m_posX, m_posY, 30, 30), BALL);
}

bool Ball::IsBallDead()
{
	return m_isBallDead;
}

void Ball::SetPosX( int p_PosX)
{
	m_posX = p_PosX;
}

void Ball::SetPosY( int p_posY )
{
	m_posY = p_posY;
}

void Ball::SetSpeed( int p_speed )
{
	m_speed = p_speed;
}

void Ball::SetDirection( float p_direction )
{
	m_direction.X = cos(p_direction); //Make sure the angle is correct and not offset. 
	m_direction.Y = sin(p_direction);
}

int Ball::GetPosX()
{
	return m_posX;
}

int Ball::GetPosY()
{
	return m_posY;
}

int Ball::GetSpeed()
{
	return m_speed;
}

float Ball::GetDirectionAngle()
{
	return acos(m_direction.X);
}

BoundingBox Ball::GetBoundingBox()
{
	BoundingBox l_bBox;
	l_bBox.Width = m_width;
	l_bBox.Height = m_height;
	l_bBox.PosX = m_posX;
	l_bBox.PosY = m_posY;

	return l_bBox;
}

void Ball::CheckCollisionAgainstWalls()
{
	if(m_posX < m_mapEdges.PosX)
		m_direction.Y *= -1;
	else if (m_posX + m_width > m_mapEdges.PosX + m_mapEdges.Width)
		m_direction.Y *= -1;

	if(m_posY < m_mapEdges.PosY)
		m_direction.X *= -1;
	else if(m_posY + m_height > m_mapEdges.PosY + m_mapEdges.Height)
		m_isBallDead = true;
}

void Ball::BallBounceAgainstEnemy( BoundingBox p_enemyBBox )
{
	
	if (!m_hasBallBouncedAgainstEnemy)
	{
		int l_bounceSide = CalculateBounceSide(p_enemyBBox);
	
		if(l_bounceSide == TOP || l_bounceSide == BOTTOM)
			m_direction.Y *= -1;
		else if(l_bounceSide == LEFT || l_bounceSide == RIGHT)
			m_direction.X *= -1;
		m_hasBallBouncedAgainstEnemy = true;
	}


}

void Ball::BallBounceAgainstPaddle( BoundingBox p_paddleBBox )
{
	int l_bounceSide = CalculateBounceSide(p_paddleBBox);

	if(l_bounceSide == LEFT || l_bounceSide == RIGHT)
		m_direction.X *= -1;
	else if(l_bounceSide == TOP)
	{
		int l_diff = m_posX+m_width/2 - p_paddleBBox.PosX+p_paddleBBox.Width/2; //length between middle of ball and middle of paddle
		float l_angle; //angle to add to the balls direction
	
		if(l_diff == 0) //if ball is in the middle of paddle
			l_angle = 0; //just reflect the ball
		else //set adding angle to a value between 45 and 135 (degrees)
			l_angle = cos(((m_width/2 + p_paddleBBox.Width/2) / l_diff) * 0.7);
	
		float l_newAngle = l_angle + acos(m_direction.X); //add angle to previous
	
		//clamp the new angle between min and max values (10 and 170 degrees)
		if(l_newAngle*180*M_1_PI < m_minBallAngle)
			l_newAngle = m_minBallAngle*M_PI/180;
		else if(l_newAngle*180/M_1_PI > m_maxBallAngle)
			l_newAngle = m_maxBallAngle*M_PI/180;
		
		m_direction.X = cos(l_newAngle);
		m_direction.Y = sin(l_newAngle)*-1;
	}
}

int Ball::CalculateBounceSide( BoundingBox p_objectBBox )
{
	int l_insideX = 0;
	int l_insideY = 0;

	//Calculate how much of the ball is inside the object on either side
	if(m_posX+m_width/2 < p_objectBBox.PosX) //if the middle of the ball is to the left of the object
		l_insideX = m_posX + m_width - p_objectBBox.PosX;
	else if(m_posX+m_width/2 > p_objectBBox.PosX+p_objectBBox.Width) //if the middle of the ball is to the right of the object
		l_insideX = p_objectBBox.PosX + p_objectBBox.Width - m_posX;
	else //the middle of the ball is inside the objects width
		l_insideX = p_objectBBox.Width/2 - abs(p_objectBBox.PosX+p_objectBBox.Width/2 - m_posX+m_width/2);

	//Same as above but with height
	if(m_posY+m_height/2 < p_objectBBox.PosY)
		l_insideY = m_posY + m_height - p_objectBBox.PosY;
	else if(m_posY+m_height/2 > p_objectBBox.PosY+p_objectBBox.Height)
		l_insideY = p_objectBBox.PosY + p_objectBBox.Height - m_posY;
	else
		l_insideY = p_objectBBox.Height/2 - abs(p_objectBBox.PosY+p_objectBBox.Height/2 - m_posY+m_height/2);

	//Compare the results
	if(l_insideX > l_insideY) //if more inside x-wise
	{
		if(m_direction.Y < 0)//coming from above
		{
			if(m_posY+m_height/2 > p_objectBBox.PosY+p_objectBBox.Height) //if below, can't bounce off top side
			{
				if(m_direction.X < 0) //choose left or right side instead
					return RIGHT;
				else
					return LEFT;
			}
			else
				return TOP;
		}
		else //coming from below
		{
			if(m_posY+m_height/2 < p_objectBBox.PosY+p_objectBBox.Height) //if above, can't bounce off bottom side
			{
				if(m_direction.X < 0) //choose left or right side instead
					return RIGHT;
				else
					return LEFT;
			}
			else
				return BOTTOM;
		}
	}
	else //more inside y-wise
	{
		if(m_direction.X > 0) //coming from left
		{
			if (m_posX+m_width/2 > p_objectBBox.PosX+p_objectBBox.Width) //if right of object, can't bounce off left side
			{
				if(m_direction.Y < 0) //choose top or bottom side instead
					return TOP;
				else
					return BOTTOM;
			}
			else
				return LEFT;
		}
		else
		{
			if (m_posX+m_width/2 < p_objectBBox.PosX+p_objectBBox.Width) //if left of object, can't bounce off right side
			{
				if(m_direction.Y < 0) //choose top or bottom side instead
					return TOP;
				else
					return BOTTOM;
			}
			else
				return RIGHT;
		}
	}

}
