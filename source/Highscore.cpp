#include "Highscore.h"

Highscore::Highscore(RenderComponentInterface* p_renderComponentInterface)
{
	m_renderComponentInterface = p_renderComponentInterface;
	m_newAdditionToHighscore = false;
	m_playerName = "AAA";
}

Highscore::~Highscore()
{
	
}

void Highscore::Init(int p_PlayerScore, bool p_Campaign)
{
	if(p_Campaign == true)
		m_fileName = "campaign.score";
	else
		m_fileName = "survival.score";

	LoadFile();
	m_playerScore = p_PlayerScore;
	int l_lowestScore = atoi(m_highscoreData[MAX_HIGHSCORE_ENTRIES-1][1].c_str());
	if(l_lowestScore < m_playerScore)
		m_newAdditionToHighscore = true;
}

void Highscore::Update()
{

}

void Highscore::Render()
{
	if(m_newAdditionToHighscore)
	{
		m_renderComponentInterface->RenderText(m_playerName.substr(0,1), 15.0f, 400.0f, 200.0f, 0xffffffff);
		m_renderComponentInterface->RenderText(m_playerName.substr(1,1), 15.0f, 650.0f, 200.0f, 0xffffffff);
		m_renderComponentInterface->RenderText(m_playerName.substr(2,1), 15.0f, 900.0f, 200.0f, 0xffffffff);
	}
	std::stringstream l_tempstream;
	l_tempstream << "Your Score: " << m_playerScore;

	m_renderComponentInterface->RenderText(l_tempstream.str(), 50.0f, 400.0f, 900.0f, 0xff00ffff);
	//Render the highscore
	m_renderComponentInterface->RenderText("HighScore", 15.0f, 1115.0f, 350.0f, 0xffffffff);
	for(int i = 0; i < MAX_HIGHSCORE_ENTRIES; i++)
	{
		m_renderComponentInterface->RenderText(m_highscoreData[i][0], 15.0f, 1100.0f, 370.0f + i * 50.0f, 0xffffffff);
		m_renderComponentInterface->RenderText(m_highscoreData[i][1], 15.0f, 1160.0f, 370.0f + i * 50.0f, 0xffffffff);
	}
}

void Highscore::NextChar(int p_buttonId)
{
	if(m_playerName.compare(p_buttonId, 1, "Z") == 0)
		m_playerName[p_buttonId] = 'A';
	else
	m_playerName[p_buttonId] += 1;	
}

void Highscore::PrevChar(int p_buttonId)
{
	if(m_playerName.compare(p_buttonId, 1, "A") == 0)
		m_playerName[p_buttonId] = 'Z';
	else
		m_playerName[p_buttonId] -= 1;	
}

void Highscore::SaveFile()
{
	if(m_newAdditionToHighscore)
	{
		InsertScoreToHighscore();
		WriteFile();
		m_newAdditionToHighscore = false;
	}
}

void Highscore::LoadFile()
{
	std::string l_score, l_name;
	std::ifstream l_myfile;
	l_myfile.open(m_fileName);
	if(!l_myfile.is_open() || l_myfile.bad() || l_myfile.eof())
	{
		if(m_fileName.compare("campaign.score") == 0)
			CreateBaseHighscore(1);
		else
			CreateBaseHighscore(10);
	}
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

void Highscore::CreateBaseHighscore(int p_modifier)
{
	std::stringstream l_tempstream;
	//This is only called if the Highscorefile is corrupted or doesn't exist.
	m_highscoreData[0][0] = "ROM";
	l_tempstream << 10000 * p_modifier;
	m_highscoreData[0][1] = l_tempstream.str();
	m_highscoreData[1][0] = "RAG";
	l_tempstream.str("");
	l_tempstream << 9000 * p_modifier;
	m_highscoreData[1][1] = l_tempstream.str();
	m_highscoreData[2][0] = "YNK";
	l_tempstream.str("");
	l_tempstream << 6000 * p_modifier;
	m_highscoreData[2][1] = l_tempstream.str();
	m_highscoreData[3][0] = "BOL";
	l_tempstream.str("");
	l_tempstream << 3000 * p_modifier;
	m_highscoreData[3][1] = l_tempstream.str();
	m_highscoreData[4][0] = "SUN";
	l_tempstream.str("");
	l_tempstream << 2000 * p_modifier;
	m_highscoreData[4][1] = l_tempstream.str();
	m_highscoreData[5][0] = "TZU";
	l_tempstream.str("");
	l_tempstream << 1900 * p_modifier;
	m_highscoreData[5][1] = l_tempstream.str();
	m_highscoreData[6][0] = "POL";
	l_tempstream.str("");
	l_tempstream << 1700 * p_modifier;
	m_highscoreData[6][1] =l_tempstream.str();
	m_highscoreData[7][0] = "ULV";
	l_tempstream.str("");
	l_tempstream << 1400 * p_modifier;
	m_highscoreData[7][1] = l_tempstream.str();
	m_highscoreData[8][0] = "HEN";
	l_tempstream.str("");
	l_tempstream << 600 * p_modifier;
	m_highscoreData[8][1] = l_tempstream.str();
	l_tempstream.str("");
	l_tempstream << 200 * p_modifier;
	m_highscoreData[9][0] = "BAD";
	m_highscoreData[9][1] = l_tempstream.str();
	WriteFile();
}

void Highscore::WriteFile()
{
	std::ofstream l_myFile;
	l_myFile.open(m_fileName);
	for(int i = 0; i < MAX_HIGHSCORE_ENTRIES; i++)
		l_myFile << m_highscoreData[i][0] +' ' + m_highscoreData[i][1]+"\n";
	l_myFile.close();
}

void Highscore::InsertScoreToHighscore()
{

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
			if(i != MAX_HIGHSCORE_ENTRIES -1)
			{
				m_highscoreData[i+1][0] = l_tempName;
				m_highscoreData[i+1][1] = l_tempScore;
			}
			break;
		}
	}
}

bool Highscore::GetnewAdditionToHighscore()
{
	return m_newAdditionToHighscore;
}

bool* Highscore::GetnewAdditionToHighscorePointer()
{
	return &m_newAdditionToHighscore;
}