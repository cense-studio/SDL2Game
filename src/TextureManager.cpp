﻿#include "TextureManager.h"
#include <SDL2/SDL_image.h>
#include <iterator>

TextureManager *TextureManager::s_pInstance = nullptr;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
    clean();
}

bool TextureManager::load(const std::string &fileName, const std::string &id, SDL_Renderer *pRenderer)
{
    SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());
    if (pTempSurface == nullptr)
    {
        return false;
    }
    // 通过表面创建纹理
    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    // 创建成功，将纹理存入Map中
    if (pTexture != nullptr)
    {
        m_textureMap[id] = pTexture;
        return true;
    }
    // 纹理创建失败了
    return false;
}

void TextureManager::draw(const std::string &id, int x, int y, int width, int height,
                          SDL_Renderer *pRenderer, SDL_RendererFlip filp)
{
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect destRect = srcRect;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, filp);
}

void TextureManager::drawFrame(const std::string &id, int x, int y, int width, int height,
                               int currentRow, int currentFrame, // 当前绘制行数，从1开始，当前绘制帧，从0开始
                               SDL_Renderer *pRenderer, SDL_RendererFlip filp)
{
    SDL_Rect srcRect = {width * currentFrame, height * (currentRow - 1), width, height};
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, filp);
}

void TextureManager::clean()
{
    if (!m_textureMap.empty())
    {
        std::map<std::string, SDL_Texture *>::iterator it;
        for (it = m_textureMap.begin(); it != m_textureMap.end(); ++it)
        {
            SDL_DestroyTexture(it->second);
        }
        m_textureMap.clear();
    }
}