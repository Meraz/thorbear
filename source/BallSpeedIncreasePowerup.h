#ifndef  BALLSPEEDINCREASEPOWERUP_H
#define  BALLSPEEDINCREASEPOWERUP_H
#include "Powerup.h"

class BallSpeedIncreasePowerup: public Powerup
{
public:
	BallSpeedIncreasePowerup(void);
	~BallSpeedIncreasePowerup(void);
	void Update(float p_deltaTime);
	void Render();
private:
};





#endif // ! ADDBALLPOWERUP_H
