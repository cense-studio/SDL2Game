#include "Enemy.h"
#include "TextureManager.h"
#include "InputHandler.h"
Enemy::Enemy(const LoaderParams *pParams)
    : SDLGameObject(pParams)
{
    m_velocity.setY(2);
    m_velocity.setX(-0.001);
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    m_currentFrame = int(((SDL_GetTicks() / 60) % 5));
    if (m_position.getY() < 0)
    {
        m_velocity.setY(2);
    }
    else if (m_position.getY() > 600 - 55)
    {
        m_velocity.setY(-2);
    }
    SDLGameObject::update();
}

void Enemy::clean()
{
}