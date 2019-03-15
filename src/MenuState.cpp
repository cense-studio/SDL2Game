#include "MenuState.h"
#include "PlayState.h"
#include "Game.h"
#include "InputHandler.h"
#include <iostream>
const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    // 按下回车进入游戏状态
    if (IInputHandler->isKeyDown(SDL_SCANCODE_RETURN))
    {
        IGame->getStateMachine()->changeState(new PlayState());
        IGame->getStateMachine()->pushState(new PlayState());
        IGame->getStateMachine()->pushState(new PlayState());
        IGame->getStateMachine()->pushState(new PlayState());
    }
}

void MenuState::render()
{
}

bool MenuState::onEnter()
{
    std::cout << "进入菜单状态\n";
    return true;
}

bool MenuState::onExit()
{
    std::cout << "退出菜单状态\n";
    return true;
}