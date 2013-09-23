#ifndef LEVELIMPORTER_H
#define LEVELIMPORTER_H

#include <Windows.h>
#include <string>
#include <iostream>
#include "LodePNG.h"
using namespace std;

#define ENEMY1 0
#define ENEMY2 1
#define EMPTY 2
class LevelImporter
{
public:
	
	~LevelImporter(void);

	//Enter name of level without the .png file ending
	static int** LoadLevel(string p_levelName);
private:
	LevelImporter(void);
};

#endif