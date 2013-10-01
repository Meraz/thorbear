#ifndef DEFENSIVEENEMY_H
#define DEFENSIVEENEMY_H

#include "Enemy.h"
class DefensiveEnemy: public Enemy
{
public:
	DefensiveEnemy(void);
	~DefensiveEnemy(void);
	void Update(float p_velocity, EnemyDirection p_direction, float p_deltaTime);
	void Render();
	bool WantsToFire();
private:
	float m_phaseZ;
};

#endif
