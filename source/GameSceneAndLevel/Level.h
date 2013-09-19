#ifndef LEVEL_H
#define LEVEL_H

#include "Ball.h"
#include "Paddle.h"
#include "LevelImporter.h"

class Level
{
public:
	Level(void);
	~Level(void);

	void Init(int p_lvlNr, int p_lvlWidth, int p_lvlHeight);

	void	Update(int p_mousePosX); //Not sure if int or float
	void	Render();
	bool	HasPaddleDied();
	int		GetNrOfEnemies();
	//void SetGraphicalInterface(RenderComponentInterface* p_renderComp)
private:
	BoundingBox	m_mapEdges;
	Paddle*		m_paddle;
	Ball*		m_ball;
	int**		m_map;
	bool		m_PaddleHasDied;
	//RenderComponentInterface*	m_renderComp;

	int		m_nrOfEnemies; //TEST

private:
	void CheckAllCollisions();
	bool BoundingBoxIntersect(BoundingBox p_box1, BoundingBox p_box2);
	int	 CalculateBallOnPaddlePosX();
};

#endif LEVEL_H