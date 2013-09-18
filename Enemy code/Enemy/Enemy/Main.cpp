#include "GameScene.h"

int main()
{
	GameScene* scene = new GameScene();
	scene->Init();

	bool pressed = false;
	while(true)
	{
		if(GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if(pressed == false)
			{
				pressed = true;
				scene->Update(0);
			}
		}
		else
		{
			pressed = false;
		}
	}

	return 0;
}