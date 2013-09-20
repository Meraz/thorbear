#ifndef BALL_H
#define BALL_H

#define TOP 1
#define BOTTOM 2
#define RIGHT 3
#define LEFT 4

#define _USE_MATH_DEFINES
#include <math.h>

struct BoundingBox //will be included later
{
	int	Width;
	int	Height;
	int posX,posY;
};

struct Vector2
{
	float X;
	float Y;
};

class Ball
{
public:
	Ball(void);
	~Ball(void);

	void Init(int p_posX, int p_posY, int p_width, int p_height, int p_speed, BoundingBox p_mapEdges); //Map edges are the inner bounds of the map
	void ShootBall();

	void Update();
	void Render();

	bool IsBallDead();

	void SetPosX(int p_posX);
	void SetPosY(int p_posY);
	void SetSpeed(int p_speed);
	void SetDirection(float p_direction); //Sets the direction in radians

	int		GetPosX();
	int		GetPosY();
	int		GetSpeed();
	float	GetDirectionAngle();

	BoundingBox GetBoundingBox();

	void	BallBounceAgainstEnemy(BoundingBox p_enemyBBox);
	void	BallBounceAgainstPaddle(BoundingBox p_paddleBBox);
	int		CalculateBounceSide(BoundingBox p_objectBBox);

	//void		SetGraphicalInterface(RenderComponentInterface* p_renderComp);

private:
	int		m_posX; //Kan bli avrundningsfel; float?
	int		m_posY;
	int		m_width;
	int		m_height;

	int		m_maxBallAngle;
	int		m_minBallAngle;

	bool	m_isBallDead;
	bool	m_hasBallBouncedAgainstEnemy;

	int		m_speed;
	Vector2 m_direction; 

	BoundingBox	m_mapEdges;

	//RenderComponentInterface*	m_renderComp;

private:

	void CheckCollisionAgainstWalls();

};

#endif BALL_H