#ifndef HIGHSCORESCENE_H
#define HIGHSCORESCENE_H

#include <fstream>
#include <string>
#include <sstream>
#define MAX_HIGHSCORE_ENTRIES 10
class HighscoreScene
{
public:
	HighscoreScene();
	~HighscoreScene();
	void Init(int p_PlayerScore);
	void Update();
	void Render();
	void NextChar(int p_buttonId);
	void PrevChar(int p_buttonId);
	void SaveFile();
private:
	void LoadFile();
	void CreateBaseHighscore();
	
	void InsertScoreToHighscore();
	void WriteFile();

private:
	std::string m_highscoreData[MAX_HIGHSCORE_ENTRIES][2]; // slot 1 = name slot 2 = score
	std::string m_playerName;
	int			m_playerScore;
	bool		m_newAdditionToHighscore;

};
#endif // !HIGHSCORESCENE_H
