#include "LevelImporter.h"


LevelImporter::LevelImporter(void)
{
}


LevelImporter::~LevelImporter(void)
{
}


int** LevelImporter::LoadLevel( string p_levelName )
{
	std::vector<unsigned char> l_image;
	unsigned l_Width, l_height;

	//An external library which handles PNG reading and decoding
	unsigned l_error = lodepng::decode(l_image,l_Width,l_height, "levels/" + p_levelName + ".png");

	if(l_error) cout << "decode error " << l_error << ": " << lodepng_error_text(l_error) << endl;

	//Creating a double array
	int** l_map = new int*[l_height]; //Send or return this somewhere?
	for(unsigned int i = 0; i < l_height; i++)
	{
		l_map[i] = new int[l_Width];
	}

	unsigned int x,y;
	x = y = 0;
	int l_enemyType;

	for(unsigned int i = 0; i < l_image.size(); i +=4)
	{
		
		int l_value = (int)l_image.at(i);

		if(l_value == 0)
		{
			l_enemyType = ENEMY1;
		}
		else if(l_value == 100)
		{
			l_enemyType = ENEMY2;
		}
		else
		{
			l_enemyType = EMPTY;
		}
		l_map[y][x] = l_enemyType;
		x++;
		if(x >= l_Width)
		{
			y++;
			x = 0;
		}
	}
	///////////////TESTING///////////////////
	/*
	for(int i = 0; i < l_height; i++)
	{
		for(int j = 0; j < l_Width; j++)
			cout << l_map[i][j];
		cout << endl;
	}
	*/
	return l_map;
}
