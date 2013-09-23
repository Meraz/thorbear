#ifndef ENEMY_H
#define ENEMY_H

#include "RenderComponentInterface.h"
#include <iostream>
using namespace std;

class Enemy
{
public:
	void Init(int p_posX, int p_posY, int p_width, int p_height);
	virtual void Update(int p_posX, int p_posY) = 0;
	virtual void Render() = 0;
	BoundingBox GetBoundingBox();
	void SetRenderComponentInterface(RenderComponentInterface* p_RenderComp);
	void TakeDamage();
	int GetNumOfLives();
	void WritePosition(); //For test purpose
protected:
	int m_numOfLives;
	BoundingBox m_BoundingBox;
	RenderComponentInterface* m_RenderComp;
};

#endif