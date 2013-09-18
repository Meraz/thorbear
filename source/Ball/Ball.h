#ifndef BALL_H
#define BALL_H
#define NULL 1
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
	void Reset(int p_paddlePosX, int p_paddlePosY);

	void Update();
	void Render();

	bool IsBallDead();

	void SetPosition(int p_posX, int p_posY);
	void SetSpeed(int p_speed);
	void SetDirection(float p_direction); //Sets the direction in radians

	int		GetPosX();
	int		GetPosY();
	int		GetSpeed();
	float	GetDirection();

	BoundingBox GetBoundingBox();

	void	BallBounceAgainstEnemy(BoundingBox p_enemyBBox);
	void	BallBounceAgainstPaddle(BoundingBox p_paddleBBox);

	//void		SetGraphicalInterface(RenderComponentInterface* p_renderComp);

private:
	int		m_posX; //Kan bli avrundningsfel; float?
	int		m_posY;
	int		m_width;
	int		m_height;

	bool	m_isBallDead;

	int		m_speed;
	Vector2 m_direction; 

	BoundingBox	m_mapEdges;

	//RenderComponentInterface*	m_renderComp;

private:

	void CheckCollisionAgainstWalls();

};

#endif BALL_H