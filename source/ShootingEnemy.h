#ifndef SHOOTINGENEMY_H
#define SHOOTINGENEMY_H

#include "Enemy.h"
#include <stdlib.h>

using namespace std;

class ShootingEnemy: public Enemy
{
public:
	ShootingEnemy(void);
	~ShootingEnemy(void);
	void Update(float p_velocity, EnemyDirection p_direction, float p_deltaTime);
	void Render();
	bool WantsToFire();
private:
	bool m_wantsToFire;
	float m_shootIntervall;
	float m_tick;
private:
};

#endif

