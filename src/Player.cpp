#include "Player.h"
#include "InputHandler.h"
#include <SDL2/SDL.h>

Player::Player(const LoaderParams *pParams)
    : SDLGameObject(pParams)
{
    m_velocity.setX(1);
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    // 动画速度为每秒10帧
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

    if (IInputHandler->isKeyDown(SDL_SCANCODE_LEFT))
    {
        m_acceleration.setX(-0.02f);
    }
    if (IInputHandler->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_acceleration.setX(0.02f);
    }
    if (m_position.getX() > 800)
    {
        m_position.setX(0);
    }
    // 调用基类更新方法
    SDLGameObject::update();
}

void Player::clean()
{
}