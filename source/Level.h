#ifndef LEVEL_H
#define LEVEL_H

#define POWERUPDROPRATIO 20
#define MODE_CAMPAIGN 0
#define MODE_SURVIVAL 1

#include <vector>
#include <time.h>
#include "Paddle.h"
#include "EnemySquad.h"
#include "LevelImporter.h"
#include "Ball.h"
#include "LargerPaddlePowerup.h"
#include "SmallerPaddlePowerup.h"
#include "AddBallPowerup.h"
#include "AddLifePowerup.h"
#include "SoundHandler.h"

class Level
{
public:
	Level(void);
	~Level(void);

	void Init(int p_lvlNr, int p_lvlWidth, int p_lvlHeight, int p_gameMode, RenderComponentInterface* p_renderComp);

	void	Update(int p_mousePosX, bool p_isMouseClicked, float p_deltaTime); //Not sure if int or float
	void	Render();
	int		GetLifeChanged();
	int		GetNrOfEnemies();
	int		GetNrOfBalls();
	void	AddBall();


private:
	vector<EnemySquad*> m_squad;
	vector<Ball*>		m_ball;
	vector<Powerup*>	m_powerup;
	BoundingBox			m_mapEdges;
	Paddle*				m_paddle;
	int**				m_map;
	int					m_changesInLife;

	int		m_gameMode;
	bool	m_prevLMouseClickStatus;
	float	m_ballSpeed;
	int		m_ballWidth;
	int		m_ballHeight;

	RenderComponentInterface*	m_renderComp;
	int		m_mapBorderThickness;
	int		m_enemyDistance;
	SoundHandler* m_soundHandler;

private:
	void	CheckAllCollisions(float p_deltaTime);
	void	CheckIncrementalCollisions(Ball* p_ball, BoundingBox p_bBox, bool p_isEnemy, float p_dt);
	void	CheckIncrementalCollisionsWithBall(Ball* p_ball1, Ball* p_ball2, float p_dt);
	bool	BoundingBoxIntersect(BoundingBox p_box1, BoundingBox p_box2);
	float	CalculateBallOnPaddlePosX();
	void	ShootBallFromPaddle(int p_ballVectorPos);
	void	CreateEnemies();
	void	RenderMapEdges();

	void	SpawnPowerup(float p_posX, float p_posY);
};

#endif LEVEL_H