#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

struct BoundingBox
{
	BoundingBox(){}
	BoundingBox(int p_posX, int p_posY)
	{
		PosX = p_posX;
		PosY = p_posY;
	}
	int PosX, PosY;
	int Width, Height;
};


#endif