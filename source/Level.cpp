#include "Level.h"

#include <string>
#include <sstream>
using namespace std;

Level::Level(void)
{
	m_mapEdges.PosX = 0;
	m_mapEdges.PosY = 0;
	m_changesInLife = 0;
	m_map = NULL;
	m_prevLMouseClickStatus = false;

	m_enemyDistance = 2;
	m_scoreMultiplier = 1.0f;

	m_isBeginningOfGame = true;
	m_isPaddleInvulnerable = false;
	m_isPaddleVisible = true;
	m_blinkTimer = 0.0f;
	m_blinkTime = 0.2f;
	m_invulTimer = 0.0f;
	m_invulTime = 1.5f;

	m_mapBorderThickness = 0;
	m_errorMessageTick = 0.0f;
	m_renderErrorLoadingLevel = false;
}


Level::~Level(void)
{
	delete m_paddle;
	delete m_map;

	for (unsigned int i = 0; i < m_squad.size(); i++)
	{
		delete m_squad.at(i);
		m_squad.at(i) = 0;
	}
	m_squad.clear();
	m_squad.shrink_to_fit();

	for (unsigned int i = 0; i < m_ball.size(); i++)
	{
		delete m_ball.at(i);
		m_ball.at(i) = 0;
	}
	m_ball.clear();
	m_ball.shrink_to_fit();

	for (unsigned int i = 0; i < m_powerup.size(); i++)
	{
		delete m_powerup.at(i);
		m_powerup.at(i) = 0;
	}
	m_powerup.clear();
	m_powerup.shrink_to_fit();


}

void Level::Init( int p_lvlNr, int p_gameMode, RenderComponentInterface* p_renderComp, SoundHandler* p_soundHandler )
{
	m_renderComp = p_renderComp;
	m_gameMode = p_gameMode;
	m_soundHandler = p_soundHandler;
	if(m_gameMode == MODE_CAMPAIGN)
	{
		std::stringstream l_ss;
		l_ss << p_lvlNr;
		std::string tmpString( "level" + l_ss.str() );

		m_map = LevelImporter::LoadLevel(tmpString);
		if(m_map == 0)
		{
			m_gameMode = MODE_SURVIVAL;
			m_renderErrorLoadingLevel = true;
		}
	}

	m_levelValues = LevelImporter::LoadGameplayValues("Gameplay Variables");

	m_mapEdges.Width = (int)m_levelValues.at("LEVELWIDTH");
	m_mapEdges.Height = (int)m_levelValues.at("LEVELHEIGHT");
	m_mapBorderThickness = (int)m_levelValues.at("LEVELBORDER");
	
	m_paddle = new Paddle(m_mapEdges.Width/2.0f, 10, (int)m_levelValues.at("PADDLEWIDTH"), (int)m_levelValues.at("PADDLEHEIGHT"), m_mapEdges.Width);
	m_paddle->Initialize(p_renderComp);

	m_ball.push_back(new Ball());
	m_ball.front()->Init(CalculateBallOnPaddlePosX(), (float)m_paddle->GetPosY()+m_paddle->GetBoundingBox().Height,
		(int)m_levelValues.at("BALLWIDTH"), (int)m_levelValues.at("BALLHEIGHT"), m_levelValues.at("BALLSPEED"), m_mapEdges, m_renderComp); //SPEED?!

	CreateEnemies();

}


void Level::CreateEnemies()
{
	vector<Enemy*> l_enemy;
	Enemy* tempEnemy;
	EnemySquad* tempSquad;

	int l_enemyWidth = (int)m_levelValues.at("ENEMYWIDTH");
	int l_enemyHeight = (int)m_levelValues.at("ENEMYHEIGHT");
	float l_enemySpeed = m_levelValues.at("ENEMYSPEED");

	if(m_gameMode == MODE_CAMPAIGN)
	{
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 15; j++)
			{
				if(m_map[i][j] == ENEMY1)
				{
					tempEnemy = new ShootingEnemy();
					tempEnemy->Init(j * (float)l_enemyWidth, m_mapEdges.PosX + m_mapEdges.Height - ((i+1) * (float)l_enemyHeight), l_enemyWidth, l_enemyHeight);
					l_enemy.push_back(tempEnemy);
				}
				else if(m_map[i][j] == ENEMY2)
				{
					tempEnemy = new DefensiveEnemy();
					tempEnemy->Init(j * (float)l_enemyWidth, m_mapEdges.PosX + m_mapEdges.Height - ((i+1) * (float)l_enemyHeight), l_enemyWidth, l_enemyHeight);
					l_enemy.push_back(tempEnemy);
				}
				
			}
		}
	}
	else if(m_gameMode == MODE_SURVIVAL)
	{
		srand(time(NULL));
		for(unsigned int i = 0; i < 15; i++) // TODO Hardcoded number of enemies
		{
			if(rand() % 2 == 0)
			{
				tempEnemy = new ShootingEnemy();
				tempEnemy->Init(i * (float)l_enemyWidth, m_mapEdges.PosY + m_mapEdges.Height - m_enemyDistance - (float)l_enemyHeight, l_enemyWidth, l_enemyHeight);
			}
			else
			{
				tempEnemy = new DefensiveEnemy();
				tempEnemy->Init(i * (float)l_enemyWidth, m_mapEdges.PosY + m_mapEdges.Height - m_enemyDistance - (float)l_enemyHeight, l_enemyWidth, l_enemyHeight);
			}
			l_enemy.push_back(tempEnemy);
		}
	}
	tempSquad = new EnemySquad();
	tempSquad->Init(m_mapEdges, 25, l_enemy);
	tempSquad->SetSquadRenderComponent(m_renderComp);
	m_squad.push_back(tempSquad);
}

void Level::AddBall()
{
	m_ball.push_back(new Ball());
	m_ball.back()->Init(CalculateBallOnPaddlePosX(), m_paddle->GetBoundingBox().PosY+m_paddle->GetBoundingBox().Height, 
		(int)m_levelValues.at("BALLWIDTH"), (int)m_levelValues.at("BALLHEIGHT"), m_levelValues.at("BALLSPEED"), m_mapEdges, m_renderComp);
	ShootBallFromPaddle(m_ball.size()-1);
}
void Level::SpawnPowerup(float p_posX, float p_posY)
{
	int l_random = rand() % 10;
	if(l_random < 3) // 0,1,2
		m_powerup.push_back(new LargerPaddlePowerup());
	else if(l_random < 6) // 3,4,5
		m_powerup.push_back(new SmallerPaddlePowerUp());
	else if(l_random < 9) // 6,7,8
		m_powerup.push_back(new AddBallPowerup());
	else
		m_powerup.push_back(new AddLifePowerup());

	m_powerup.back()->init(p_posX, p_posY, 20, 20 , m_renderComp);
}

void Level::Update( int p_mousePosX, bool p_isMouseClicked, float p_deltaTime )
{
	m_changesInLife = 0;

	for (unsigned int i = 0; i < m_ball.size(); i++)
	{
		m_ball.at(i)->Update(p_deltaTime);

		if(m_ball.at(i)->IsBallDead())
		{
			if (m_ball.size() == 1)
			{
				
				m_ball.at(i)->SetPosX(CalculateBallOnPaddlePosX());
				m_ball.at(i)->SetPosY((float)(m_paddle->GetPosY() + m_paddle->GetBoundingBox().Height));
				if(p_isMouseClicked && !m_prevLMouseClickStatus)
				{
					if(m_isBeginningOfGame)
					{
						m_isBeginningOfGame = false;
					}
					ShootBallFromPaddle(i);
				}
			}
			else
			{
				delete m_ball.at(i);
				m_ball.at(i) = 0;
				m_ball.erase(m_ball.begin() + i);
				i--; 
			}
		}
	} 

	m_paddle->Update(p_mousePosX);

	if (m_gameMode == MODE_SURVIVAL)
	{
		if((m_squad.back()->GetBoundingBox().PosY + m_squad.back()->GetBoundingBox().Height < m_mapEdges.PosY + m_mapEdges.Height - m_squad.back()->GetBoundingBox().Height)
			&& m_squad.back()->GetDirection() == 1)
		{
			CreateEnemies();
		}
	}
	if(!m_isBeginningOfGame)
	{
		for(unsigned int i = 0; i < m_squad.size(); i++)
		{
			m_squad.at(i)->Update(p_deltaTime);
		}
		for(unsigned int i = 0; i < m_powerup.size(); i++)
		{
			m_powerup.at(i)->Update(p_deltaTime);
		}

		if (m_isPaddleInvulnerable)
		{
			m_blinkTimer -= p_deltaTime;
			if (m_blinkTimer < 0)
			{
				m_blinkTimer += m_blinkTime;
				if(m_isPaddleVisible)
					m_isPaddleVisible = false;
				else
					m_isPaddleVisible = true;
			}
			m_invulTimer -= p_deltaTime;
			if (m_invulTimer < 0)
			{
				m_isPaddleInvulnerable = false;
				m_isPaddleVisible = true;
			}
		}
	}
	CheckAllCollisions(p_deltaTime);

	m_soundHandler->Update();
	m_prevLMouseClickStatus = p_isMouseClicked;

	if(m_errorMessageTick < 5)
		m_errorMessageTick += p_deltaTime;
	else
		m_renderErrorLoadingLevel = false;
}

void Level::Render()
{
	RenderMapEdges();
	if(m_isPaddleVisible)
		m_paddle->Render(); 

	for (unsigned int i = 0; i < m_ball.size(); i++)
	{
		m_ball.at(i)->Render();
	}
	
	for(unsigned int i = 0; i < m_squad.size(); i++)
	{
		m_squad.at(i)->Render();
	}

	for( unsigned int i = 0; i < m_powerup.size(); i++)
	{
		m_powerup.at(i)->Render();
	}

	if(m_renderErrorLoadingLevel == true)
		m_renderComp->RenderText("No level file found, loaded survival mode....", 15.0f, 5.0f, 70.0f, 0xff0099ff);
	
}

void Level::CheckAllCollisions(float p_deltaTime)
{
	for (unsigned int k = 0; k < m_ball.size(); k++) // Ball vs...
	{
		//... Laser
		for(unsigned int i = 0; i < m_squad.size(); i++)
		{
			for(unsigned int j = 0; j < m_squad.at(i)->GetLasers().size(); j++)
			{
				if(BoundingBoxIntersect(m_ball.at(k)->GetBoundingBox(), m_squad.at(i)->GetLasers().at(j)->GetBoundingBox()))
					m_squad.at(i)->EraseMember(BALL, j); //TODO Change to LASER once this define is implemented
			}
		}
		//... Paddle
		if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), m_ball.at(k)->GetBoundingBox()))
		{
			CheckIncrementalCollisions(m_ball.at(k), m_paddle->GetBoundingBox(), false, p_deltaTime);
			m_soundHandler->PlayGameSound(BALLBOUNCE);
		}
		//... Enemy
		for(unsigned int i = 0; i < m_squad.size(); i++)
		{
			for(unsigned int j = 0; j < m_squad.at(i)->GetEnemies().size(); j++)
			{
				if(BoundingBoxIntersect(m_ball.at(k)->GetBoundingBox(), m_squad.at(i)->GetEnemies().at(j)->GetBoundingBox()))
				{
					CheckIncrementalCollisions(m_ball.at(k), m_squad.at(i)->GetEnemies().at(j)->GetBoundingBox(), true, p_deltaTime);
					m_squad.at(i)->GetEnemies().at(j)->TakeDamage();
					if(m_squad.at(i)->GetEnemies().at(j)->GetNumOfLives() == 0)
					{
						int l_random = rand() % 100;
						if(l_random < POWERUPDROPRATIO)
							SpawnPowerup(m_squad.at(i)->GetEnemies().at(j)->GetBoundingBox().PosX, m_squad.at(i)->GetEnemies().at(j)->GetBoundingBox().PosY);
						m_squad.at(i)->EraseMember(ENEMY1, j);
						m_soundHandler->PlayGameSound(ENEMYDEATH);

						ParticleEmitterDesc l_desc;
						l_desc.position			= Vect3(m_ball.at(k)->GetBoundingBox().PosX, m_ball.at(k)->GetBoundingBox().PosY, m_ball.at(k)->GetBoundingBox().PosZ);
						l_desc.lifeTimeMin		= 0.5f;
						l_desc.lifeTimeMax		= 0.7f;
						l_desc.acceleration		= Vect3(0.0f, 0.0f, 0.0f);
						l_desc.nrOfParticles	= 200;
						l_desc.speedMin			= 50.0f;
						l_desc.speedMax			= 300.0f;
						l_desc.scale			= Vect3(0.5f, 0.5f, 0.5f);
						l_desc.startColor		= Vect3(0.0f, 1.0f, 0.0f);
						l_desc.endColor			= Vect3(0.0f, 0.4f, 0.0f);
						m_renderComp->CreateParticleEmitter(l_desc);

						//m_renderComp->CreateSplashText(L"NICE!", 200.0f, 900.0f, 450.0f, 0.4f, 0.0f);
					}
					m_soundHandler->PlayGameSound(BALLBOUNCE);
				}
			}
		}
		//... Ball
		for (unsigned int i = 0; i < m_ball.size(); i++)
		{
			if(BoundingBoxIntersect(m_ball.at(k)->GetBoundingBox(), m_ball.at(i)->GetBoundingBox()))
			{
				if(m_ball.at(k) != m_ball.at(i))
					CheckIncrementalCollisionsWithBall(m_ball.at(k), m_ball.at(i), p_deltaTime);
			}
		}
	}
	// Paddle vs Laser
	for(unsigned int i = 0; i < m_squad.size(); i++)
	{
		for(unsigned int j = 0; j < m_squad.at(i)->GetLasers().size(); j++)
		{
			if(!m_isPaddleInvulnerable && BoundingBoxIntersect(m_paddle->GetBoundingBox(), m_squad.at(i)->GetLasers().at(j)->GetBoundingBox()))
			{
				m_changesInLife--;
				SetInvulnerability();
				m_squad.at(i)->EraseMember(BALL, j); //TODO Change to LASER once this define is implemented
			}
		}
	}

	// Paddle vs PowerUp
	for(unsigned int i = 0; i < m_powerup.size(); i++)
	{
		if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), m_powerup.at(i)->GetBoundingBox()))
		{
			if(m_powerup.at(i)->GetPowerUpType() ==  LARGERPADDLE)
			{
				if(m_paddle->GetBoundingBox().Width < 100)
				{
					m_paddle->SetWidth(m_paddle->GetBoundingBox().Width + 20);
					if (m_scoreMultiplier <= 1.0f)
					{
						if (m_scoreMultiplier != 0.25f)
							m_scoreMultiplier -= 0.25f;
					}
					else
					{
						m_scoreMultiplier -= 0.50f;
					}
				}
			}	
			else if(m_powerup.at(i)->GetPowerUpType() ==  SMALLERPADDLE)
			{
				
				if(m_paddle->GetBoundingBox().Width > 20)
				{
					m_paddle->SetWidth(m_paddle->GetBoundingBox().Width - 20);
					if (m_scoreMultiplier < 1.0f)
					{
						m_scoreMultiplier += 0.25f;
					}
					else
					{
						if (m_scoreMultiplier != 2.00f)
							m_scoreMultiplier += 0.50f;
					}
				}
			}
			else if(m_powerup.at(i)->GetPowerUpType() ==  ADDBALL)
			{
				AddBall();
			}
			else if(m_powerup.at(i)->GetPowerUpType() ==  ADDLIFE)
			{
				m_changesInLife++;
			}
			delete m_powerup.at(i);
			m_powerup.at(i) = 0;
			m_powerup.erase(m_powerup.begin() + i);
		}
		else if(m_powerup.at(i)->GetBoundingBox().PosY <= 0)
		{
				delete m_powerup.at(i);
				m_powerup.at(i) = 0;
				m_powerup.erase(m_powerup.begin() + i);
		}
	}
	// Enemy vs Enemy
	for(unsigned int i = 1; i < m_squad.size(); i++)
	{
		if(!m_squad.at(i)->IsPaused())
		{
			if(BoundingBoxIntersect(m_squad.at(i-1)->GetBoundingBox(), m_squad.at(i)->GetBoundingBox()))
			{
				if(m_squad.at(i)->GetBoundingBox().PosY > m_squad.at(i-1)->GetBoundingBox().PosY)
					m_squad.at(i)->PauseMovement();
				else
					m_squad.at(i-1)->PauseMovement();
			}
		}
	}

	for(unsigned int i = 1; i < m_squad.size(); i++)
	{
		if(m_squad.at(i)->IsPaused())
		{
			if(!BoundingBoxIntersect(m_squad.at(i-1)->GetBoundingBox(), m_squad.at(i)->GetBoundingBox()))
				m_squad.at(i)->StartMovement();
		}
	}
	
	// if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), PowerUpBoundingBox))
	// TODO Stuff happens
	
}

void Level::CheckIncrementalCollisions(Ball* p_ball, BoundingBox p_bBox, bool p_isEnemy, float p_dt)
{
	//Increment the balls position to find out exactly where it hit the other object, for more accurate collisions
	float l_incTime = 0.0f;
	float l_increment = 0.0001f;

	while (l_incTime < p_dt)
	{
		p_ball->IncUpdate(l_increment);
		if(BoundingBoxIntersect(p_ball->GetIncBBox(), p_bBox))
		{
			if(p_isEnemy)
				p_ball->BallBounceAgainstEnemy(p_bBox);
			else
				p_ball->BallBounceAgainstPaddle(p_bBox);
		}

		l_incTime += l_increment;
	}

	p_ball->SetActualPosAndDir();
}

void Level::CheckIncrementalCollisionsWithBall(Ball* p_ball1, Ball* p_ball2, float p_dt)
{
	//Increment the balls position to find out exactly where it hit the other ball, for more accurate collisions
	float l_incTime = 0.0f;
	float l_increment = 0.0001f;

	while (l_incTime < p_dt)
	{
		p_ball1->IncUpdate(l_increment);
		p_ball2->IncUpdate(l_increment);
		if(BoundingBoxIntersect(p_ball1->GetIncBBox(), p_ball2->GetIncBBox()))
		{
			p_ball1->BallBounceAgainstBall(p_ball2->GetIncBBox());
			p_ball2->BallBounceAgainstBall(p_ball1->GetIncBBox());
		}

		l_incTime += l_increment;
	}

	p_ball1->SetActualPosAndDir();
	p_ball2->SetActualPosAndDir();
}

bool Level::BoundingBoxIntersect(BoundingBox p_box1, BoundingBox p_box2)
{
	if((p_box1.PosX+p_box1.Width > p_box2.PosX && p_box1.PosX < p_box2.PosX+p_box2.Width) && 
		p_box1.PosY+p_box1.Height > p_box2.PosY && p_box1.PosY < p_box2.PosY+p_box2.Height)
		return true;
	else
		return false;
}

int Level::GetLifeChanged()
{
	return m_changesInLife;
}

int Level::GetNrOfEnemies()
{
	int l_numEnemies = 0;
	for(unsigned int i = 0; i < m_squad.size(); i++)
	{
		if(m_squad.at(i)->GetNumOfEnemies() == 0)
		{
			delete m_squad.at(i);
			m_squad.at(i) = 0;
			m_squad.erase(m_squad.begin()+i);
			if(m_squad.size() == 0 && m_gameMode == MODE_SURVIVAL)
				CreateEnemies();
		}
		else
			l_numEnemies += m_squad.at(i)->GetNumOfEnemies();
	}
	return l_numEnemies;
}

float Level::CalculateBallOnPaddlePosX()
{
	
	return ((m_paddle->GetPosX()/(m_mapEdges.Width-m_paddle->GetBoundingBox().Width)) * (m_mapEdges.Width - (2 * m_paddle->GetBoundingBox().Width))) + m_paddle->GetBoundingBox().Width - (m_ball.front()->GetBoundingBox().Width/2.0f);
}

void Level::ShootBallFromPaddle(int p_ballVectorPos)
{
	float l_diff = m_ball.at(p_ballVectorPos)->GetPosX()+(m_ball.at(p_ballVectorPos)->GetBoundingBox().Width/2) - (m_paddle->GetPosX()+(m_paddle->GetBoundingBox().Width/2)); //length between middle of ball and middle of paddle

	if(l_diff == 0) //if ball is in the middle of paddle
	{
		m_ball.at(p_ballVectorPos)->SetDirection((float)cos(0));
	}
	else //set angle to a value between 45 and 135 (degrees)
	{
		m_ball.at(p_ballVectorPos)->SetDirection((float)acos((l_diff / ((m_ball.at(p_ballVectorPos)->GetBoundingBox().Width/2) + (m_paddle->GetBoundingBox().Width/2))) * 0.7));
	}
	m_ball.at(p_ballVectorPos)->ShootBall();
}

void Level::RenderMapEdges()
{
	BoundingBox l_leftSide = BoundingBox(m_mapEdges.PosX - m_mapBorderThickness, m_mapEdges.PosY, m_mapBorderThickness, m_mapEdges.Height + m_mapBorderThickness, 9);
	BoundingBox l_rightSide = BoundingBox(m_mapEdges.PosX + m_mapEdges.Width, m_mapEdges.PosY, m_mapBorderThickness, m_mapEdges.Height + m_mapBorderThickness, 9);
	BoundingBox l_topSide = BoundingBox(m_mapEdges.PosX + m_mapBorderThickness/2, m_mapEdges.PosY + m_mapEdges.Height, m_mapEdges.Width + m_mapBorderThickness, m_mapBorderThickness, 9);

	m_renderComp->RenderObject(l_leftSide, BALL);
	m_renderComp->RenderObject(l_rightSide, BALL);
	m_renderComp->RenderObject(l_topSide, BALL);
}

int Level::GetNrOfBalls()
{
	return m_ball.size();
}

float Level::GetMultiplier()
{
	return m_scoreMultiplier;
}

void Level::SetInvulnerability()
{
	m_isPaddleInvulnerable = true;
	m_invulTimer = m_invulTime;
}
