#ifndef __Texture_Manager__
#define __Texture_Manager__

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include "Config.h"
class TextureManager
{
public:
  static TextureManager *Instance()
  {
    if (s_pInstance == nullptr)
    {
      s_pInstance = new TextureManager;
    }
    return s_pInstance;
  }
  static void purge()
  {
    if (s_pInstance != nullptr)
    {
      delete s_pInstance;
      s_pInstance = nullptr;
    }
  }

  // 加载一个纹理
  bool load(const std::string &fileName, const std::string &id, SDL_Renderer *pRenderer);
  // 绘制一个纹理
  void draw(const std::string &id, int x, int y, int width, int height,
            SDL_Renderer *pRenderer, SDL_RendererFlip filp = SDL_FLIP_NONE);
  // 绘制纹理的一帧
  void drawFrame(const std::string &id, int x, int y, int width, int height,
                 int currentRow, int currentFrame,
                 SDL_Renderer *pRenderer, SDL_RendererFlip filp = SDL_FLIP_NONE);
  // 清空
  void cleanAll();

  // 从纹理图中清除纹理
  void cleanFromTextureMap(const std::string &id);

private:
  TextureManager();
  ~TextureManager();

private:
  // 纹理管理区实例
  static TextureManager *s_pInstance;
  // 纹理对象Map
  std::map<std::string, SDL_Texture *> m_textureMap;
};

// 获取纹理管理器实例
#define ITextureManager TextureManager::Instance()

#endif