#include "Enemy.h"
#include "TextureManager.h"
#include "InputHandler.h"
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
    m_position.setX(m_position.getX() + 3);
    if(m_position.getX() > 800)
    {
        m_position.setX(0);
    }
    if(IInputHandler->getMouseButtonState(0)){
        m_position = IInputHandler->getMousePosition();
    }
}

void Enemy::clean()
{
}