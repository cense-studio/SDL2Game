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
        if (m_bExited)
        {
            break;
        }
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

    m_gameObjects.push_back(new MenuButton(new LoaderParams(200, 100, 400, 100, "play_button"), onPlayButtonCliked));
    m_gameObjects.push_back(new MenuButton(new LoaderParams(200, 300, 400, 100, "exit_button"), onExitButtonCliked));
    m_bExited = false;
    return true;
}

bool MenuState::onExit()
{
    // 逐个清空对象资源
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    // 清空对象数组
    m_gameObjects.clear();
    // 销毁当前状态创建的纹理
    ITextureManager->cleanFromTextureMap("play_button");
    ITextureManager->cleanFromTextureMap("exit_button");
    m_bExited = true;
    return true;
}

void MenuState::onPlayButtonCliked()
{
    IGame->getStateMachine()->changeState(new PlayState());
}

void MenuState::onExitButtonCliked()
{
    IGame->quit();
}