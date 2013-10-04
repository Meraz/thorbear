#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

struct BoundingBox
{
	BoundingBox()
	{
		Width = -1;
		Height = -1;
		Depth = -1;
		PosX = 0;
		PosY = 0;
		PosZ = 0;
	}
	BoundingBox(float p_posX, float p_posY)
	{
		PosX = p_posX;
		PosY = p_posY;
		PosZ = 0;
		Depth = Height = Width = -1;
	}
	BoundingBox(float p_posX, float p_posY, int p_width, int p_height)
	{
		PosX = p_posX;
		PosY = p_posY;
		PosZ = 0;
		Width = p_width;
		Height = p_height;
		Depth = -1;
	}
	BoundingBox(float p_posX, float p_posY, int p_width, int p_height, int p_depth)
	{
		PosX = p_posX;
		PosY = p_posY;
		PosZ = 0;
		Width = p_width;
		Height = p_height;
		Depth = p_depth;
	}
	float PosX, PosY, PosZ;
	int Width, Height, Depth;
};

#endif