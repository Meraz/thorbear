#include "HighscoreScene.h"

HighscoreScene::HighscoreScene()
{

}
HighscoreScene::~HighscoreScene()
{

}

void HighscoreScene::Init()
{
	LoadFile();
}

void HighscoreScene::Update()
{

}

void HighscoreScene::Render()
{

}

void HighscoreScene::LoadFile()
{
	std::string l_line, l_temp;
	std::ifstream l_myfile;
	l_myfile.open("Highscore.score");
	if(!l_myfile.is_open() || l_myfile.bad() || l_myfile.eof())
		int fea = 11; //Add creation of the original highscorefile =D=D=D=D=D=D
	int i = 0;
	while(getline(l_myfile, l_line ))
	{
		unsigned l_pos = l_line.find(' ');
		l_temp = l_line.substr(0, l_pos);
		l_line = l_line.substr(l_pos+1, l_line.size()-1);

		m_highscoreData[i][0] = l_temp;
		m_highscoreData[i][1] = l_line;
		i++;
	}
	l_myfile.close();

}

void HighscoreScene::WriteFile()
{

}