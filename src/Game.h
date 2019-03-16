#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "GameObject.h"
#include "GameStateMachine.h"
class Game
{
public:
  // 获取游戏实例
  static Game *Instance()
  {
    if (s_pInstance == nullptr)
    {
      s_pInstance = new Game;
    }
    return s_pInstance;
  }
  // 清除游戏实例
  static void purge()
  {
    if (s_pInstance)
    {
      delete s_pInstance;
      s_pInstance = nullptr;
    }
  }
  // 初始化游戏
  bool init(const std::string &title,
            int xpos, int ypos,
            int width, int height,
            bool fullscreen);
  // 游戏渲染
  void render();
  // 更新
  void update();
  // 处理事件
  void handleEvents();
  // 清理数据
  void clean();

  // 获取游戏是否正在运行
  bool running()
  {
    return m_bRunning;
  }
  // 退出游戏
  void quit()
  {
    m_bRunning = false;
  }
  // 获取SDL渲染器
  SDL_Renderer *getRenderer()
  {
    return m_pRenderer;
  }
  // 获取状态机
  GameStateMachine *getStateMachine()
  {
    return m_pGameStateMachine;
  }

protected:
  void onInitialized();

private:
  Game() {}
  ~Game() {}

private:
  static Game *s_pInstance;            // 游戏实例
  SDL_Window *m_pWindow = nullptr;     //窗口指针
  SDL_Renderer *m_pRenderer = nullptr; //渲染器指针
  bool m_bRunning = false;             // 游戏是否在运行

  // 游戏状态机
  GameStateMachine *m_pGameStateMachine = nullptr;
};

// 简化获取游戏实例方式
#define IGame Game::Instance()
#endif