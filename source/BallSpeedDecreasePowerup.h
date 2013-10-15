#ifndef  BALLSPEEDDECREASEPOWERUP_H
#define  BALLSPEEDDECREASEPOWERUP_H
#include "Powerup.h"

class BallSpeedDecreasePowerup: public Powerup
{
public:
	BallSpeedDecreasePowerup(void);
	~BallSpeedDecreasePowerup(void);
	void Update(float p_deltaTime);
	void Render();
private:
};





#endif // ! ADDBALLPOWERUP_H
