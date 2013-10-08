#ifndef HighScore_H
#define HighScore_H

#include <fstream>
#include <string>
#include <sstream>
#define MAX_HIGHSCORE_ENTRIES 10
class HighScore
{
public:
	HighScore();
	~HighScore();
	void Init(int p_PlayerScore, bool p_Campaign); //p_Campaign should be true if the game mode was campaign
	void Update();
	void Render();
	void NextChar(int p_buttonId);
	void PrevChar(int p_buttonId);
	void SaveFile();
private:
	void LoadFile();
	void CreateBaseHighscore(int p_modifier);
	
	void InsertScoreToHighscore();
	void WriteFile();

private:
	std::string m_highscoreData[MAX_HIGHSCORE_ENTRIES][2]; // slot 1 = name slot 2 = score
	std::string m_playerName;
	std::string m_fileName;
	int			m_playerScore;
	bool		m_newAdditionToHighscore;

};
#endif // !HighScore_H
