#ifndef LEVELIMPORTER_H
#define LEVELIMPORTER_H

#include <string>
#include <iostream>
#include <fstream>
#include <hash_map>
#include "LodePNG.h"
using namespace std;

//defines for reading the level file
#define ENEMY1 0
#define ENEMY2 1
#define EMPTY 2

class LevelImporter
{
public:
	
	~LevelImporter(void);

	//Enter name of level without the .png file ending
	static int**		LoadLevel(string p_levelName);
	static hash_map<string, float>	LoadGameplayValues(string p_fileName);
private:
	LevelImporter(void);
	void SetStandardValues();
};

#endif