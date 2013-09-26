#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Paddle.h"
#include "EnemySquad.h"
#include "LevelImporter.h"
#include "Ball.h"

class Level
{
public:
	Level(void);
	~Level(void);

	void Init(int p_lvlNr, int p_lvlWidth, int p_lvlHeight, RenderComponentInterface* p_renderComp);

	void	Update(int p_mousePosX, bool p_isMouseClicked, float p_deltaTime); //Not sure if int or float
	void	Render();
	bool	HasPaddleDied();
	int		GetNrOfEnemies();

private:
	vector<EnemySquad*> m_squad;
	BoundingBox	m_mapEdges;
	Paddle*		m_paddle;
	Ball*		m_ball;
	int**		m_map;
	bool		m_PaddleHasDied;

	RenderComponentInterface*	m_renderComp;
	int		m_mapBorderThickness;

private:
	void	CheckAllCollisions();
	bool	BoundingBoxIntersect(BoundingBox p_box1, BoundingBox p_box2);
	float	CalculateBallOnPaddlePosX();
	void	ShootBallFromPaddle();
	void	CreateEnemies();
	void	RenderMapEdges();
};

#endif LEVEL_H