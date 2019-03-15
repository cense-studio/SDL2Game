﻿#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams *pParams)
    : GameObject(pParams),m_position((float)pParams->getX(), (float)pParams->getY())
{
    if (pParams)
    {
        m_width = pParams->getWidth();
        m_height = pParams->getHeight();
        m_textureID = pParams->getTextureID();
        m_currentRow = 1;
        m_currentFrame = 0;
        // 用完参数加载器就释放掉
        delete pParams;
    }
}

void SDLGameObject::update(){
    // 速度不断提升
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::draw()
{
    ITextureManager->drawFrame(
        m_textureID,
        (int)m_position.getX(), (int)m_position.getY(), m_width, m_height,
        m_currentRow, m_currentFrame,
        Game::Instance()->getRenderer());
}