#include "Level.h"


Level::Level(void)
{
	m_mapEdges.PosX = 0;
	m_mapEdges.PosY = 0;
	m_PaddleHasDied = false;
	m_map = NULL;
}


Level::~Level(void)
{
	delete m_paddle;
	delete m_map;
	vector<EnemySquad*>().swap(m_squad);
}

void Level::Init( int p_lvlNr, int p_lvlWidth, int p_lvlHeight, RenderComponentInterface* p_renderComp )
{
	m_renderComp = p_renderComp;
	m_mapEdges.Width = p_lvlWidth; 
	m_mapEdges.Height = p_lvlHeight; 
	string tmpString = "level"+to_string(p_lvlNr); 
	m_map = LevelImporter::LoadLevel(tmpString);	
	m_paddle = new Paddle(p_lvlWidth/2.0f, 50.0f, 200, 50, p_lvlWidth); //example values
	m_paddle->Initialize(p_renderComp);

	m_ball = new Ball();
	int l_ballHeight = 5; //TEST ONLY
	int l_ballWidth = 5; //TEST ONLY
	m_ball->Init(CalculateBallOnPaddlePosX(), (float)m_paddle->GetPosY()-m_paddle->GetBoundingBox().Height-l_ballHeight, l_ballWidth, l_ballHeight, 200.0f, m_mapEdges, m_renderComp); //SPEED?!

	CreateEnemies();

}


void Level::CreateEnemies()
{
	vector<Enemy*> l_enemy;
	Enemy* tempEnemy;
	EnemySquad* tempSquad;
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			if(m_map[i][j] == ENEMY1)
			{
				tempEnemy = new ShootingEnemy();
				tempEnemy->Init(j * 20.0f, m_mapEdges.Height - (i * 20.0f), 20, 20); //TODO Don't hard code width and height in the end
				l_enemy.push_back(tempEnemy);
			}
			else if(m_map[i][j] == ENEMY2)
			{
				tempEnemy = new DefensiveEnemy();
				tempEnemy->Init(j * 20.0f, m_mapEdges.Height - (i * 20.0f), 20, 20); //TODO Don't hard code width and height in the end
				l_enemy.push_back(tempEnemy);
			}
		}
	}

	tempSquad = new EnemySquad();
	tempSquad->Init(m_mapEdges, 50, l_enemy);
	tempSquad->SetSquadRenderComponent(m_renderComp);
	m_squad.push_back(tempSquad);
}

void Level::Update( int p_mousePosX, bool p_isMouseClicked, float p_deltaTime )
{
	if(m_ball->IsBallDead())
	{
		m_ball->SetPosX(CalculateBallOnPaddlePosX());
		m_ball->SetPosY((float)(m_paddle->GetPosY() + m_paddle->GetBoundingBox().Height));
		if(p_isMouseClicked)
			ShootBallFromPaddle();
	}
	m_paddle->Update(p_mousePosX);
	m_ball->Update(p_deltaTime);

	for(unsigned int i = 0; i < m_squad.size(); i++)
	{
		m_squad.at(i)->Update(p_deltaTime);
	}

	CheckAllCollisions();
}



void Level::Render()
{
	m_paddle->Render();
	m_ball->Render();
	
	for(unsigned int i = 0; i < m_squad.size(); i++)
	{
		m_squad.at(i)->Render();
	}
	//TODO powerups. 
	//m_renderComp->RenderObject(m_bBox, OUTERBOUNDS) Render maps outer bounds/edges
}

void Level::CheckAllCollisions()
{
	
	//Paddle vs Laser and Ball vs Laser
	for(unsigned int i = 0; i < m_squad.size(); i++)
	{
			for(unsigned int j = 0; j < m_squad.at(i)->GetLasers().size(); j++)
			{
				if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), m_squad.at(i)->GetLasers().at(j)->GetBoundingBox()))
				{
					m_PaddleHasDied = true;
					m_squad.at(i)->EraseMember(BALL, j); //TODO Change to LASER once this define is implemented
				}
				else if(BoundingBoxIntersect(m_ball->GetBoundingBox(), m_squad.at(i)->GetLasers().at(j)->GetBoundingBox()))
					m_squad.at(i)->EraseMember(BALL, j); //TODO Change to LASER once this define is implemented
			}
	}
	
	//Paddle vs Ball
	if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), m_ball->GetBoundingBox()))
		m_ball->BallBounceAgainstPaddle(m_paddle->GetBoundingBox());

	for(unsigned int i = 0; i < m_squad.size(); i++)
	{
		for(unsigned int j = 0; j < m_squad.at(i)->GetEnemies().size(); j++)
		{
			//Ball vs Enemy
			if(BoundingBoxIntersect(m_ball->GetBoundingBox(), m_squad.at(i)->GetEnemies().at(j)->GetBoundingBox()))
			{
				m_ball->BallBounceAgainstEnemy(m_squad.at(i)->GetEnemies().at(j)->GetBoundingBox());
				m_squad.at(i)->GetEnemies().at(j)->TakeDamage();
				if(m_squad.at(i)->GetEnemies().at(j)->GetNumOfLives() == 0)
					m_squad.at(i)->EraseMember(ENEMY1, j);
			}
		}
		
	}

	//Paddle vs PowerUp
	//if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), PowerUpBoundingBox))
	//TODO Stuff happens

}

bool Level::BoundingBoxIntersect(BoundingBox p_box1, BoundingBox p_box2)
{
	if((p_box1.PosX+p_box1.Width > p_box2.PosX && p_box1.PosX < p_box2.PosX+p_box2.Width) && 
		p_box1.PosY+p_box1.Height > p_box2.PosY && p_box1.PosY < p_box2.PosY+p_box2.Height)
		return true;
	else
		return false;
}

bool Level::HasPaddleDied()
{
	bool temp = m_PaddleHasDied;
	m_PaddleHasDied = false;

	return temp;
}

int Level::GetNrOfEnemies()
{
	int l_numEnemies = 0;
	for(unsigned int i = 0; i < m_squad.size(); i++)
	{
		l_numEnemies += m_squad.at(i)->GetNumOfEnemies();
	}
	return l_numEnemies;
}

float Level::CalculateBallOnPaddlePosX()
{
	//return m_paddle->GetPosX()+m_paddle->GetBoundingBox().Width; // TODO byt ut mot b�ttre algoritm!!!
	//del/max
	return m_paddle->GetPosX()+(m_paddle->GetBoundingBox().Width/2) + (((m_paddle->GetBoundingBox().Width/2) / (m_mapEdges.Width/2))*((m_mapEdges.Width/2.0f) - (m_paddle->GetPosX() + (m_paddle->GetBoundingBox().Width/2)))) - (m_ball->GetBoundingBox().Width/2);
}

void Level::ShootBallFromPaddle()
{
	
	float l_diff = m_ball->GetPosX()+(m_ball->GetBoundingBox().Width/2) - m_paddle->GetPosX()+(m_paddle->GetBoundingBox().Width/2); //length between middle of ball and middle of paddle

	if(l_diff == 0) //if ball is in the middle of paddle
	{
		m_ball->SetDirection((float)cos(0));
	}
	else //set angle to a value between 45 and 135 (degrees)
	{
		m_ball->SetDirection((float)cos((((m_ball->GetBoundingBox().Width/2) + (m_paddle->GetBoundingBox().Width/2)) / l_diff) * 0.7));
	}
	m_ball->ShootBall();
}
