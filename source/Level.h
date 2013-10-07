#ifndef LEVEL_H
#define LEVEL_H

#define POWERUPDROPRATIO 20

#include <vector>
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

	void Init(int p_lvlNr, RenderComponentInterface* p_renderComp);

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
	//Ball*				m_ball;
	int**				m_map;
	int					m_changesInLife;

	bool	m_prevLMouseClickStatus;

	RenderComponentInterface*	m_renderComp;
	int		m_mapBorderThickness;

	SoundHandler* m_soundHandler;

	hash_map<string, float> m_levelValues;

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