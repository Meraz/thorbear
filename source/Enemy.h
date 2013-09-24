#ifndef ENEMY_H
#define ENEMY_H

#include "RenderComponentInterface.h"
#include <iostream>
using namespace std;

enum EnemyDirection {VERTICAL, HORIZONTAL};

class Enemy
{
public:
	void			Init(float p_posX, float p_posY, int p_width, int p_height, float p_velocity);
	virtual void	Update(float p_deltaTime, EnemyDirection p_direction) = 0;
	virtual void	Render() = 0;
	BoundingBox		GetBoundingBox();
	void			SetRenderComponentInterface(RenderComponentInterface* p_RenderComp);
	void			TakeDamage();
	int				GetNumOfLives();
	float			GetVelocity();
	void			SetVelocity(float p_velocity);
	void			WritePosition(); //For test purpose
	virtual bool	WantsToFire() = 0;
protected:
	float	m_posX;
	float	m_posY;
	float	m_velocity;
	int m_numOfLives;
	int m_enemyType;
	BoundingBox m_BoundingBox;
	RenderComponentInterface* m_RenderComp;
};

#endif