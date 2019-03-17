#ifndef __Game_Over_State__
#define __Game_Over_State__
#include "GameState.h"
#include "GameObject.h"
#include <vector>

class GameOverState:public GameState
{
public:
	void update()override;
	void render()override;

	bool onEnter()override;
	bool onExit()override;
	std::string getStateID()override {return s_playID; }

private:
	static const std::string s_playID;

	std::vector <GameObject *> m_gameObjects;

	bool m_bExited = false;
};
#endif