#ifndef  LARGERPADDLEPOWERUP_H
#define  LARGERPADDLEPOWERUP_H
#include "Powerup.h"

class LargerPaddlePowerup: public Powerup
{
public:
	LargerPaddlePowerup(void);
	~LargerPaddlePowerup(void);
	void Update(float p_deltaTime);
	void Render();
private:
};





#endif // ! LARGERPADDLEPOWERUP_H
