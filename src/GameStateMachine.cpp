#include "GameStateMachine.h"
#include <iostream>

void GameStateMachine::pushState(GameState *pState)
{
    if (!m_gameStates.empty())
    {
        std::cout << m_gameStates.back()->getStateID() << "处于暂停状态，临时进入" << pState->getStateID() << "状态\n";
    }
    else
    {
        std::cout << "进入" << pState->getStateID() << "状态\n";
    }
    m_gameStates.push_back(pState);
    pState->onEnter();
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
        while (!m_gameStates.empty())
        {
            popState();
        }
    }
    // 添加新状态
    pushState(pState);
}

void GameStateMachine::popState()
{
    if (!m_gameStates.empty())
    {
        if (m_gameStates.back()->onExit())
        {
            std::cout << "退出了" << m_gameStates.back()->getStateID() << "状态\n";
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
        if (!m_gameStates.empty())
        {
            std::cout << "恢复了" << m_gameStates.back()->getStateID() << "状态\n ";
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