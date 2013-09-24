#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

struct BoundingBox
{
	BoundingBox(){}
	BoundingBox(float p_posX, float p_posY)
	{
		PosX = p_posX;
		PosY = p_posY;
	}
	BoundingBox(float p_posX, float p_posY, int p_width, int p_height)
	{
		PosX = p_posX;
		PosY = p_posY;
		Width = p_width;
		Height = p_height;
	}
	float PosX, PosY;
	int Width, Height;
};


#endif