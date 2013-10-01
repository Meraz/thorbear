#ifndef  ADDLIFEPOWERUP_H
#define  ADDLIFEPOWERUP_H
#include "Powerup.h"

class AddLifePowerup: public Powerup
{
public:
	AddLifePowerup(void);
	~AddLifePowerup(void);
	void Update(float p_deltaTime);
	void Render();
private:
};





#endif // ! ADDLIFEPOWERUP_H
