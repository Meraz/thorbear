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
	unsigned l_width, l_height;


	ifstream l_fileCheck("levels/" + p_levelName + ".png");
	
	//Check if the file actually exists
	if(l_fileCheck)
	{
		//An external library which handles PNG reading and decoding
		unsigned l_error = lodepng::decode(l_image,l_width,l_height, "levels/" + p_levelName + ".png");


		if(l_error) cout << "decode error " << l_error << ": " << lodepng_error_text(l_error) << endl;
	}
	else
	{
		return NULL;
	}

	//Creating a double array
	int** l_map = new int*[l_height]; //Send or return this somewhere?
	for(unsigned int i = 0; i < l_height; i++)
	{
		l_map[i] = new int[l_width];
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
		if(x >= l_width)
		{
			y++;
			x = 0;
		}
	}

	return l_map;
}

hash_map<string, float> LevelImporter::LoadGameplayValues( string p_fileName )
{
	hash_map<string, float> l_values;

	//Set standard values if no file can be read
	l_values.insert(pair<string, float>("LEVELHEIGHT", 400));
	l_values.insert(pair<string, float>("LEVELWIDTH", 600));
	l_values.insert(pair<string, float>("LEVELBORDER", 9));
	l_values.insert(pair<string, float>("BALLHEIGHT", 5));
	l_values.insert(pair<string, float>("BALLWIDTH", 5));
	l_values.insert(pair<string, float>("BALLSPEED", 200));
	l_values.insert(pair<string, float>("PADDLEHEIGHT", 10));
	l_values.insert(pair<string, float>("PADDLEWIDTH", 60));
	l_values.insert(pair<string, float>("ENEMYHEIGHT", 20));
	l_values.insert(pair<string, float>("ENEMYWIDTH", 20));
	l_values.insert(pair<string, float>("ENEMYSPEED", 50));
	l_values.insert(pair<string, float>("LASERSPEED", 200));

	ifstream l_file;
	l_file.open("levels/" + p_fileName + ".txt");

	string l_key;
	string l_value;
	if(l_file.is_open())
	{
		while(!l_file.eof())
		{
			l_file >> l_key;
			l_file >> l_value;
			if(l_values.count(l_key))
				l_values.at(l_key) = stof(l_value.c_str());
		}
	}

	return l_values;
}

