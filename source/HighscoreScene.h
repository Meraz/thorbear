#ifndef HIGHSCORESCENE_H
#define HIGHSCORESCENE_H

#include <iostream>
#include <fstream>
#include <string>


class HighscoreScene
{
public:
	HighscoreScene();
	~HighscoreScene();
	void Init();
	void Update();
	void Render();
private:
	void LoadFile();
	void WriteFile();

private:
	std::string m_highscoreData[10][2];

};
#endif // !HIGHSCORESCENE_H
