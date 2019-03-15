#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState *pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState *pState)
{
    // 退出当前
    if (!m_gameStates.empty())
    {
        // 如果当前状态等于要改变的状态就什么也不做
        if (m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return;
        }
        // 退出当前游戏状态
        if (m_gameStates.back()->onExit())
        {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
    // 添加新状态
    pushState(pState);
}

void GameStateMachine::popState()
{
    if (!m_gameStates.empty() && m_gameStates.size() > 1)
    {
        if (m_gameStates.back()->onExit())
        {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::popAllState()
{
    if (!m_gameStates.empty())
    {
        for (size_t i = m_gameStates.size(); i != 0; --i)
        {
            if (m_gameStates.back()->onExit())
            {
                delete m_gameStates.back();
                m_gameStates.pop_back();
            }
        }
    }
}