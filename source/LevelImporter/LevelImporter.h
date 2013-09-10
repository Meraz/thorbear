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
	
	~LevelImporter(void);

	static void LoadLevel(string p_levelName);
private:
	LevelImporter(void);
};

#endif