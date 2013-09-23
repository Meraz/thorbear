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
	BoundingBox(int p_posX, int p_posY, int p_width, int p_height)
	{
		PosX = p_posX;
		PosY = p_posY;
		Width = p_width;
		Height = p_height;
	}
	int PosX, PosY;
	int Width, Height;
};


#endif