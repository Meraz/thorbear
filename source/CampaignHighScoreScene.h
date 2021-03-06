#ifndef CAMPAIGNHIGHSCORESCENE_H
#define CAMPAIGNHIGHSCORESCENE_H

#include <vector>

#include "BaseScene.h"
#include "Button.h"
#include "Highscore.h"

class CampaignHighscoreScene : public BaseScene
{
public:
	CampaignHighscoreScene(int p_score);
	~CampaignHighscoreScene();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();
	void CheckButton(int p_mousePositionX, int p_mousePositionY);

private:
	std::vector<Button*> m_button;
	Highscore* m_highScore;
	int m_score;
	bool * m_newAdditionToHighscore;
};

#endif