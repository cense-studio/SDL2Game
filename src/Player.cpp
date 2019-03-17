#include "Player.h"
#include "InputHandler.h"
#include <SDL2/SDL.h>

Player::Player(const LoaderParams *pParams)
    : SDLGameObject(pParams)
{
    m_velocity.setX(0.05f);
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    // 动画速度为每秒10帧
    m_currentFrame = int(((SDL_GetTicks() / 60) % 5));

    if (IInputHandler->isKeyDown(SDL_SCANCODE_LEFT))
    {
        m_position.setX(m_position.getX() - 2.0f);
        m_velocity.setX(-0.1f);
    }
    if (IInputHandler->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_position.setX(m_position.getX() + 2.0f);
        m_velocity.setX(0.1f);
    }
    if (IInputHandler->isKeyDown(SDL_SCANCODE_UP))
    {
        m_position.setY(m_position.getY() - 2.0f);
    }
    if (IInputHandler->isKeyDown(SDL_SCANCODE_DOWN))
    {
        m_position.setY(m_position.getY() + 2.0f);
    }
    if (m_position.getX() > 800)
    {
        m_position.setX(0);
    }
    else if (m_position.getX() < 0)
    {
        m_position.setX(800);
    }

    // 调用基类更新方法
    SDLGameObject::update();
}

void Player::clean()
{
}

void Player::handleInput()
{
    m_velocity = IInputHandler->getMousePosition() - m_position;
    m_velocity /= 50;
}