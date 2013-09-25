#ifndef ENEMY_H
#define ENEMY_H

#include "RenderComponentInterface.h"
#include <iostream>
using namespace std;

enum EnemyDirection {VERTICAL, HORIZONTAL};

class Enemy
{
public:
	void			Init(float p_posX, float p_posY, int p_width, int p_height);
	virtual void	Update(float p_velocity, EnemyDirection p_direction) = 0;
	virtual void	Render() = 0;
	BoundingBox		GetBoundingBox();
	void			SetRenderComponentInterface(RenderComponentInterface* p_RenderComp);
	void			TakeDamage();
	int				GetNumOfLives();
	void			WritePosition(); //For test purpose
	virtual bool	WantsToFire() = 0;
protected:
	float	m_posX;
	float	m_posY;
	int m_numOfLives;
	int m_enemyType;
	BoundingBox m_BoundingBox;
	RenderComponentInterface* m_RenderComp;
};

#endif