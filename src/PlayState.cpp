#include "PlayState.h"
#include "Game.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "PauseState.h"
#include <iostream>
const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if (IInputHandler->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        IGame->getStateMachine()->pushState(new PauseState());
        return;
    }
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
        if (m_bExited)
        {
            break;
        }
    }
}
void PlayState::render()
{
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PlayState::onEnter()
{
    if (!ITextureManager->load("assets/helicopter.png", "helicopter", IGame->getRenderer()))
    {
        return false;
    }
    if (!ITextureManager->load("assets/helicopter2.png", "helicopter2", IGame->getRenderer()))
    {
        return false;
    }
    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 55, "helicopter")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(400, 100, 128, 55, "helicopter2")));
    m_bExited = false;
    return true;
}

bool PlayState::onExit()
{
    // 逐个清空对象资源
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    // 清空对象数组
    m_gameObjects.clear();
    // 销毁当前状态创建的纹理
    ITextureManager->cleanFromTextureMap("helicopter");
    ITextureManager->cleanFromTextureMap("helicopter2");
    m_bExited = true;
    return true;
}