#include "Enemy.h"
#include "TextureManager.h"

Enemy::Enemy(const LoaderParams *pParams)
    : SDLGameObject(pParams)
{
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    m_position.setX(m_position.getX() + 2);
    if(m_position.getX() > 800)
    {
        m_position.setX(0);
    }
}

void Enemy::clean()
{
}