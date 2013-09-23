#ifndef LEVELIMPORTER_H
#define LEVELIMPORTER_H

#include <Windows.h>
#include <string>
#include <iostream>
#include "LodePNG.h"

using namespace std;

class LevelImporter
{
public:
	LevelImporter(void);
	~LevelImporter(void);

	//Enter name of level without the .png file ending
	int**	LoadLevel(string p_levelName);
	int		GetLevelHeight();

private:
	
	int m_mapHeight;
};

#endif