#include "Level.h"


Level::Level(void)
{
	m_mapEdges.PosX = 0;
	m_mapEdges.PosY = 0;
	m_PaddleHasDied = false;
	m_map = NULL;
	m_nrOfEnemies = 0;
}


Level::~Level(void)
{
	delete m_paddle;
	delete m_map;
	delete m_ball;
}

void Level::Init(int p_lvlNr, int p_lvlWidth, int p_lvlHeight, RenderComponentInterface* p_renderComp)
{
	m_renderComp = p_renderComp;
	//m_nrOfEnemies = 5; //Test only
	m_mapEdges.Width = p_lvlWidth; 
	m_mapEdges.Height = p_lvlHeight; 
	string tmpString = "level"+to_string(p_lvlNr);
	m_map = LevelImporter::LoadLevel(tmpString);
	m_paddle = new Paddle(0, 50, 20, 5, p_lvlWidth); //example values
	m_paddle->Initialize(m_renderComp);
	m_ball = new Ball();
	int l_ballHeight = 20; //TEST ONLY
	int l_ballWidth = 20; //TEST ONLY

	m_ball->Init(CalculateBallOnPaddlePosX(), m_paddle->GetPosY()-m_paddle->GetBoundingBox().Height-l_ballHeight, l_ballWidth, l_ballHeight, 10, m_mapEdges, m_renderComp); //SPEED?!
	// TODO Create enemies from data in m_map

}

void Level::Update( int p_mousePosX, bool p_isMouseClicked )
{
	if(m_ball->IsBallDead())
	{
		m_ball->SetPosX(CalculateBallOnPaddlePosX());
		m_ball->SetPosY(m_paddle->GetPosY() - m_paddle->GetBoundingBox().Height - m_ball->GetBoundingBox().Height);
		if(p_isMouseClicked)
			ShootBallFromPaddle();
	}
//	m_paddle->Update(p_mousePosX);
	m_ball->Update();
	CheckAllCollisions();
	//TODO Update enemy position, make ball stick to paddle and shoot with mouse button
}

void Level::Render()
{
	m_paddle->Render();
	m_ball->Render();
	//TODO Render enemies, lasers, powerups and ball[X]. 
	//m_renderComp->RenderObject(m_bBox, OUTERBOUNDS) Render maps outer bounds/edges
}

void Level::CheckAllCollisions()
{
	
	/*
	BoundingBox LaserBoundingBox;
	LaserBoundingBox.Height = 50;
	LaserBoundingBox.Width	= 20;
	LaserBoundingBox.PosX = 400;
	LaserBoundingBox.PosY = 740;
	*/
	//Paddle vs Laser
	//if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), LaserBoundingBox))
		//m_PaddleHasDied = true;
	
	//Paddle vs Ball
	if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), m_ball->GetBoundingBox()))
		m_ball->BallBounceAgainstPaddle(m_paddle->GetBoundingBox());

	//Paddle vs PowerUp
	//if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), PowerUpBoundingBox))
		//Stuff happens
	
	//Ball vs Enemy
	//if(BoundingBoxIntersect(m_ball->GetBoundingBox(), m_enemy->GetBoundingBox()))
		//m_ball->BallBounceAgainstEnemy(m_enemy->GetBoundingBox());
		//Enemy hit

	//Ball vs Laser
	//if(BoundingBoxIntersect(BallBoundingBox, LaserBoundingBox))
		//Remove laser
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
	//m_nrOfEnemies--; //For test purposes only
	return m_nrOfEnemies;
}

int Level::CalculateBallOnPaddlePosX()
{
	return m_paddle->GetPosX()+m_paddle->GetBoundingBox().Width; // TODO byt ut mot bättre algoritm!!!
}

void Level::ShootBallFromPaddle()
{
	
	int l_diff = m_ball->GetPosX()+m_ball->GetBoundingBox().Width/2 - m_paddle->GetPosX()+m_paddle->GetBoundingBox().Width/2; //length between middle of ball and middle of paddle

	if(l_diff == 0) //if ball is in the middle of paddle
	{
		m_ball->SetDirection(cos(0));
	}
	else //set angle to a value between 45 and 135 (degrees)
	{
		m_ball->SetDirection(cos(((m_ball->GetBoundingBox().Width/2 + m_paddle->GetBoundingBox().Width/2) / l_diff) * 0.7));
	}
	m_ball->ShootBall();
}

/*void Level::SetGraphicalInterface(RenderComponentInterface* p_renderComp)
{
	m_renderComp = p_renderComp;
	m_paddle->SetGraphicalInterface(p_renderComp);
	//Set the interface for enemy,ball
}*/

/* BALL BOUNCE
Enum left, right, top, down, i bollen och block
jämför mittpunkt på bollen och paddlen
*/