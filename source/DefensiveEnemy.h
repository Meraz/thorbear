#ifndef DEFENSIVEENEMY_H
#define DEFENSIVEENEMY_H

#include "Enemy.h"
class DefensiveEnemy: public Enemy
{
public:
	DefensiveEnemy(void);
	~DefensiveEnemy(void);
	void Update(int p_posX, int p_posY);
	void Render();
private:

};

#endif
