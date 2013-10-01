#ifndef BOUNINGBOX2D_H
#define BOUNINGBOX2D_H

struct BoundingBox2D
{
	BoundingBox2D()
	{
		Width = -1;
		Height = -1;
	}
	BoundingBox2D(float p_posX, float p_posY)
	{
		PosX = p_posX;
		PosY = p_posY;
	}

	BoundingBox2D(float p_posX, float p_posY, float p_width, float p_height)
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