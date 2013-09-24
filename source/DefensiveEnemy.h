#ifndef DEFENSIVEENEMY_H
#define DEFENSIVEENEMY_H

#include "Enemy.h"
class DefensiveEnemy: public Enemy
{
public:
	DefensiveEnemy(void);
	~DefensiveEnemy(void);
	void Update(float p_deltaTime, EnemyDirection p_direction);
	void Render();
	bool WantsToFire();
private:

};

#endif
