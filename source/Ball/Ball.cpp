#include "Ball.h"


Ball::Ball(void)
{
	m_posX = 0;
	m_posY = 0;
	m_width = 0;
	m_height = 0;
	m_speed = 0;
	m_direction.X = 0;
	m_direction.Y = 0;
}


Ball::~Ball(void)
{
}

void Ball::Init(int p_posX, int p_posY, int p_width, int p_height, int p_speed, BoundingBox p_mapEdges)
{
	m_posX = p_posX;
	m_posY = p_posY;
	m_width = p_width;
	m_height = p_height;
	m_speed = p_speed;
	m_mapEdges = p_mapEdges;
}

void Ball::Reset(int p_paddlePosX, int p_paddlePosY)
{
	m_posX = p_paddlePosX;
	m_posY = p_paddlePosY;
	m_isBallDead = false;
}

void Ball::Update()
{
	m_posX += m_direction.X * m_speed;
	m_posY += m_direction.Y * m_speed;

	CheckCollisionAgainstWalls();
}

void Ball::Render()
{
	//m_renderComp->RenderObject(m_bBox, BALL)
}

bool Ball::IsBallDead()
{
	return m_isBallDead;
}

void Ball::SetPosition( int p_posX, int p_posY )
{
	m_posX = p_posX;
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

float Ball::GetDirection()
{
	return acos(m_direction.X);
}

BoundingBox Ball::GetBoundingBox()
{
	BoundingBox l_bBox;
	l_bBox.Width = m_width;
	l_bBox.Height = m_height;
	l_bBox.posX = m_posX;
	l_bBox.posY = m_posY;

	return l_bBox;
}

void Ball::CheckCollisionAgainstWalls()
{
	if(m_posX < m_mapEdges.posX)
		m_direction.Y *= -1;
	else if (m_posX + m_width > m_mapEdges.posX + m_mapEdges.Width)
		m_direction.Y *= -1;

	if(m_posY < m_mapEdges.posY)
		m_direction.X *= -1;
	else if(m_posY + m_height > m_mapEdges.posY + m_mapEdges.Height)
		m_isBallDead = true;
}

void Ball::BallBounceAgainstEnemy( BoundingBox p_enemyBBox )
{
	//Already bounced?

	int l_insideX = 0;
	int l_insideY = 0;

	//Calculate how much of the ball is inside the enemy on either side
	if(m_posX+m_width/2 < p_enemyBBox.posX) //if the middle of the ball is to the left of the enemy
		l_insideX = m_posX + m_width - p_enemyBBox.posX;
	else if(m_posX+m_width/2 > p_enemyBBox.posX+p_enemyBBox.Width) //if the middle of the ball is to the right of the enemy
		l_insideX = p_enemyBBox.posX + p_enemyBBox.Width - m_posX;
	else //the middle of the ball is inside the enemys width
		l_insideX = p_enemyBBox.Width/2 - abs(p_enemyBBox.posX+p_enemyBBox.Width/2 - m_posX+m_width/2);
	
	//Same as above but with height
	if(m_posY+m_height/2 < p_enemyBBox.posY)
		l_insideY = m_posY + m_height - p_enemyBBox.posY;
	else if(m_posY+m_height/2 > p_enemyBBox.posY+p_enemyBBox.Height)
		l_insideY = p_enemyBBox.posY + p_enemyBBox.Height - m_posY;
	else
		l_insideY = p_enemyBBox.Height/2 - abs(p_enemyBBox.posY+p_enemyBBox.Height/2 - m_posY+m_height/2);


	//Compare the results
	if(l_insideX > l_insideY) //if more inside x-wise
	{
		if((m_direction.Y > 0 && m_posY+m_height/2 > p_enemyBBox.posY+p_enemyBBox.Height) || //if coming from above and is under the enemy...
			(m_direction.Y < 0 && m_posY+m_height/2 < p_enemyBBox.posY+p_enemyBBox.Height))  //or from below and is over the enemy...
			m_direction.X *= -1; //change x direction
		else
			m_direction.Y *= -1; //otherwise change y as normal
	}
	else
	{
		if((m_direction.X > 0 && m_posX+m_width/2 > p_enemyBBox.posX+p_enemyBBox.Width) || //if coming from left and is to the right of the enemy...
			(m_direction.X < 0 && m_posX+m_width/2 < p_enemyBBox.posX+p_enemyBBox.Width))  //or from right and is to the left of the enemy...
			m_direction.Y *= -1; //change y direction
		else
			m_direction.X *= -1; //otherwise change x as normal
	}
}

void Ball::BallBounceAgainstPaddle( BoundingBox p_paddleBBox )
{

}
