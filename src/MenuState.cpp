#include "MenuState.h"
#include "PlayState.h"
#include "Game.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include <iostream>
const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MenuState::render()
{
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter()
{
    if (!ITextureManager->load("./assets/UI/play.png", "play_button", IGame->getRenderer()))
    {
        return false;
    }
    if (!ITextureManager->load("./assets/UI/exit.png", "exit_button", IGame->getRenderer()))
    {
        return false;
    }

    m_gameObjects.push_back(new MenuButton(new LoaderParams(100, 100, 400, 100, "play_button")));
    m_gameObjects.push_back(new MenuButton(new LoaderParams(100, 300, 400, 100, "exit_button")));

    std::cout << "进入菜单状态\n";
    return true;
}

bool MenuState::onExit()
{
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    std::cout << "退出菜单状态\n";
    return true;
}