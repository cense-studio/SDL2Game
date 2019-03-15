#include "PlayState.h"
#include "Game.h"
#include "InputHandler.h"
#include <iostream>
const std::string PlayState::s_menuID = "PLAY";

void PlayState::update()
{
    if (IInputHandler->isKeyDown(SDL_SCANCODE_SPACE))
    {
        IGame->getStateMachine()->popState();
    }
}

void PlayState::render()
{ // nothing for now
}

bool PlayState::onEnter()
{
    std::cout << "进入游戏状态\n";
    return true;
}

bool PlayState::onExit()
{
    std::cout << "退出游戏状态\n";
    return true;
}