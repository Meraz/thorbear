#ifndef  SMALLERPADDLEPOWERUP_H
#define  SMALLERPADDLEPOWERUP_H
#include "Powerup.h"

class SmallerPaddlePowerUp: public Powerup
{
public:
	SmallerPaddlePowerUp(void);
	~SmallerPaddlePowerUp(void);
	void Update(float p_deltaTime);
	void Render();
private:
};





#endif // ! SMALLERPADDLEPOWERUP_H