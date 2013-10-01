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

	void Init(int p_lvlNr, int p_lvlWidth, int p_lvlHeight, RenderComponentInterface* p_renderComp);

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
	float	m_ballSpeed;
	int		m_ballWidth;
	int		m_ballHeight;

	RenderComponentInterface*	m_renderComp;
	int		m_mapBorderThickness;

	SoundHandler* m_soundHandler;

private:
	void	CheckAllCollisions();
	bool	BoundingBoxIntersect(BoundingBox p_box1, BoundingBox p_box2);
	float	CalculateBallOnPaddlePosX();
	void	ShootBallFromPaddle(int p_ballVectorPos);
	void	CreateEnemies();
	void	RenderMapEdges();
	void	SpawnPowerup(float p_posX, float p_posY);
};

#endif LEVEL_H