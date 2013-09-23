#ifndef BALL_H
#define BALL_H

#define TOP 1
#define BOTTOM 2
#define RIGHT 3
#define LEFT 4

#define _USE_MATH_DEFINES
#include <math.h>

#include "RenderComponentInterface.h"

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

	void Init(float p_PosX, float p_posY, int p_width, int p_height, float p_speed, BoundingBox p_mapEdges, RenderComponentInterface* p_renderComp); //Map edges are the inner bounds of the map
	void ShootBall();

	void Update(float p_deltaTime);
	void Render();

	bool IsBallDead();

	void SetPosX(float p_PosX);
	void SetPosY(float p_posY);
	void SetSpeed(float p_speed);
	void SetDirection(float p_direction); //Sets the direction in radians

	float	GetPosX();
	float	GetPosY();
	float	GetSpeed();
	float	GetDirectionAngle();

	BoundingBox GetBoundingBox();

	void	BallBounceAgainstEnemy(BoundingBox p_enemyBBox);
	void	BallBounceAgainstPaddle(BoundingBox p_paddleBBox);
	int		CalculateBounceSide(BoundingBox p_objectBBox);

private:
	float	m_posX; //Kan bli avrundningsfel; float?
	float	m_posY;
	int		m_width;
	int		m_height;

	int		m_maxBallAngle;
	int		m_minBallAngle;

	bool	m_isBallDead;
	bool	m_hasBallBouncedAgainstEnemy;

	float	m_speed;
	Vector2 m_direction; 

	BoundingBox	m_mapEdges;

	RenderComponentInterface*	m_renderComp;

private:

	void CheckCollisionAgainstWalls();

};

#endif BALL_H