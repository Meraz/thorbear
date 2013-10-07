#include "HighscoreScene.h"

HighscoreScene::HighscoreScene()
{
	m_newAdditionToHighscore = false;
	m_playerName = "AAA";
}
HighscoreScene::~HighscoreScene()
{

}

void HighscoreScene::Init(int p_PlayerScore)
{
	LoadFile();
	m_playerScore = p_PlayerScore;
	int l_lowestScore = atoi(m_highscoreData[MAX_HIGHSCORE_ENTRIES-1][1].c_str());
	if(l_lowestScore < m_playerScore)
		m_newAdditionToHighscore = true;
}

void HighscoreScene::Update()
{

}

void HighscoreScene::Render()
{
	if(m_newAdditionToHighscore)
	{
		//Render the buttons and stuff like that here
	}
	
	printf("%c " ,m_playerName.at(0));
	//Render the highscore

}


void HighscoreScene::NextChar(int p_buttonId)
{
	if(m_playerName.compare(p_buttonId, 1, "Z") == 0)
		m_playerName[p_buttonId] = 'A';
	else
	m_playerName[p_buttonId] += 1;
	
}

void HighscoreScene::PrevChar(int p_buttonId)
{
	if(m_playerName.compare(p_buttonId, 1, "A") == 0)
		m_playerName[p_buttonId] = 'Z';
	else
		m_playerName[p_buttonId] -= 1;

	
}

void HighscoreScene::SaveFile()
{
	if(m_newAdditionToHighscore)
	{
		InsertScoreToHighscore();
		WriteFile();
	}

}

void HighscoreScene::LoadFile()
{
	std::string l_score, l_name;
	std::ifstream l_myfile;
	l_myfile.open("Highscore.score");
	if(!l_myfile.is_open() || l_myfile.bad() || l_myfile.eof())
		CreateBaseHighscore();
	else
	{
	int i = 0;
	while(getline(l_myfile, l_score ))
	{
		unsigned l_pos = l_score.find(' ');
		l_name = l_score.substr(0, l_pos);
		l_score = l_score.substr(l_pos+1, l_score.size()-1);

		m_highscoreData[i][0] = l_name;
		m_highscoreData[i][1] = l_score;
		i++;
	}
	l_myfile.close();
	}
}


void HighscoreScene::CreateBaseHighscore()
{
	//This is only called if the Highscorefile is corrupted or doesn't exist.
	m_highscoreData[0][0] = "ROM";
	m_highscoreData[0][1] = "10000";
	m_highscoreData[1][0] = "RAG";
	m_highscoreData[1][1] = "9000";
	m_highscoreData[2][0] = "YNK";
	m_highscoreData[2][1] = "6000";
	m_highscoreData[3][0] = "BOL";
	m_highscoreData[3][1] = "3000";
	m_highscoreData[4][0] = "SUN";
	m_highscoreData[4][1] = "2000";
	m_highscoreData[5][0] = "TZU";
	m_highscoreData[5][1] = "1900";
	m_highscoreData[6][0] = "POL";
	m_highscoreData[6][1] = "1700";
	m_highscoreData[7][0] = "ULV";
	m_highscoreData[7][1] = "1400";
	m_highscoreData[8][0] = "HEN";
	m_highscoreData[8][1] = "600";
	m_highscoreData[9][0] = "BAD";
	m_highscoreData[9][1] = "200";
}



void HighscoreScene::WriteFile()
{
	std::ofstream l_myFile;
	l_myFile.open("Highscore.score");
	for(int i = 0; i < MAX_HIGHSCORE_ENTRIES; i++)
		l_myFile << m_highscoreData[i][0] +' ' + m_highscoreData[i][1]+"\n";
	l_myFile.close();
}

void HighscoreScene::InsertScoreToHighscore()
{
	int l_insertPoint;
	for(int i = 0; i < MAX_HIGHSCORE_ENTRIES ; i++)
	{
		
		if( atoi(m_highscoreData[i][1].c_str()) < m_playerScore)
		{
			
			std::string l_tempName, l_tempScore;
			l_tempName = m_highscoreData[i][0];
			l_tempScore = m_highscoreData[i][1];
			std::stringstream l_tempstream;
			l_tempstream << m_playerScore;
			m_highscoreData[i][0] = m_playerName;
			m_highscoreData[i][1] = l_tempstream.str();
			for(int j = MAX_HIGHSCORE_ENTRIES-1 ; j > i+1; j--)
			{
				m_highscoreData[j][0] = m_highscoreData[j-1][0];
				m_highscoreData[j][1] = m_highscoreData[j-1][1];
			}
			m_highscoreData[i+1][0] = l_tempName;
			m_highscoreData[i+1][1] = l_tempScore;

			break;
		}
	}
}