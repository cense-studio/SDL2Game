#ifndef __Game_State_Machine__
#define __Game_State_Machine__

#include "GameState.h"
#include <vector>

class GameStateMachine
{
  public:
    // 添加一个状态到尾部
    void pushState(GameState *pState);
    // 改变当前状态
    void changeState(GameState *pState);
    // 退出当前状态
    void popState();
    // 弹出所有状态
    void popAllState();
    
    void update()
    {
        if (!m_gameStates.empty())
        {
            m_gameStates.back()->update();
        }
    }

    void render()
    {
        if (!m_gameStates.empty())
        {
            m_gameStates.back()->render();
        }
    }

  private:
    std::vector<GameState *> m_gameStates;
};

#endif