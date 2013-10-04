#ifndef  ADDBALLPOWERUP_H
#define  ADDBALLPOWERUP_H
#include "Powerup.h"

class AddBallPowerup: public Powerup
{
public:
	AddBallPowerup(void);
	~AddBallPowerup(void);
	void Update(float p_deltaTime);
	void Render();
private:
};





#endif // ! ADDBALLPOWERUP_H
