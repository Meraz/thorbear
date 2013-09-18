#ifndef ENEMY_H
#define ENEMY_H

//#include "RenderComponentInterface.h"

struct BoundingBox
{
	int farTopLeftX;
	int farTopLeftY;
	int farTopLeftZ;
	int width;
	int heigth;
	int depth;
};

class Enemy
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	BoundingBox GetBoundingBox();
	//void SetRenderComponentInterface(RenderComponentInterface* p_RenderComp);
protected:
	BoundingBox m_BoundingBox;
	//RenderComponentInterface* m_RenderComp;
};

#endif