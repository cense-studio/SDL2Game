#include "InputHandler.h"
#include "Game.h"

InputHandler *InputHandler::s_pInstance = nullptr;

InputHandler::InputHandler() : m_keysStates(SDL_GetKeyboardState(nullptr))
{
    // 初始化鼠标按钮状态
    for (int i = 0; i < 3; i++)
    {
        m_mouseButtonStates.push_back(false);
    }
}

void InputHandler::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            IGame->quit();
            break;
        case SDL_JOYAXISMOTION:
            onJoystickAxisMove(event);
            break;
        case SDL_JOYBUTTONDOWN:
            onJoystickButtonDown(event);
            break;
        case SDL_JOYBUTTONUP:
            onJoystickButtonUp(event);
            break;
        case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;
        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;
        default:
            break;
        }
    }
}

void InputHandler::clean()
{
    // 如果操纵杆启用了，则关闭所有打开的操纵杆
    if (m_bJoysticksInitialised)
    {
        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
}

void InputHandler::initialiseJoysticks()
{
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if (SDL_NumJoysticks() > 0)
    {
        // 打开每一个可用的操纵杆
        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_Joystick *joy = SDL_JoystickOpen(i);
            if (joy != nullptr)
            {
                m_joysticks.push_back(joy);
                // 为每个操纵杆添加方向向量，每个操纵杆有四个方向
                m_joystickValues.push_back(
                    std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));
                // 初始化手柄按钮状态
                std::vector<bool> tempButtons;
                for (int i = 0; i < SDL_JoystickNumButtons(joy); i++)
                {
                    tempButtons.push_back(false);
                }
                m_joyButtonStates.push_back(tempButtons);
            }
            else
            {
                std::cout << SDL_GetError() << "\n";
            }
        }
        // 开启操纵杆事件监听
        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;
        std::cout << "实际初始化了" << m_joysticks.size() << "个操纵杆。\n";
    }
    else
    {
        m_bJoysticksInitialised = false;
    }
}

int InputHandler::xvalue(int joy, int stick)
{
    if (m_joystickValues.size() > 0)
    {
        if (stick == 1)
        {
            return (int)m_joystickValues[joy].first->getX();
        }
        else if (stick == 2)
        {
            return (int)m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
    if (m_joystickValues.size() > 0)
    {
        if (stick == 1)
        {
            return (int)m_joystickValues[joy].first->getY();
        }
        else if (stick == 2)
        {
            return (int)m_joystickValues[joy].second->getY();
        }
    }
    return 0;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (m_keysStates)
    {
        if (m_keysStates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void InputHandler::onMouseMove(SDL_Event &event)
{
    m_mousePosition.setX((float)event.motion.x);
    m_mousePosition.setY((float)event.motion.y);
}
void InputHandler::onMouseButtonDown(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = true;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = true;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = true;
    }
}
void InputHandler::onMouseButtonUp(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = false;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = false;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::onJoystickAxisMove(SDL_Event &event)
{
    int whichOne = event.jaxis.which; // 传递事件的是哪个操纵杆
    // 左侧方向键左右移动
    if (event.jaxis.axis == 0) // 0 左侧左右
    {
        if (event.jaxis.value > m_joystickDeadZone)
        {
            m_joystickValues[whichOne].first->setX(1);
        }
        else if (event.jaxis.value < -m_joystickDeadZone)
        {
            m_joystickValues[whichOne].first->setX(-1);
        }
        else
        {
            m_joystickValues[whichOne].first->setX(0);
        }
    }
    // 左侧方向键上下移动
    if (event.jaxis.axis == 1) // 1 左侧上下
    {
        if (event.jaxis.value > m_joystickDeadZone)
        {
            m_joystickValues[whichOne].first->setY(1);
        }
        else if (event.jaxis.value < -m_joystickDeadZone)
        {
            m_joystickValues[whichOne].first->setY(-1);
        }
        else
        {
            m_joystickValues[whichOne].first->setY(0);
        }
    }

    // 右侧方向键左右移动
    if (event.jaxis.axis == 3) // 右侧左右
    {
        if (event.jaxis.value > m_joystickDeadZone)
        {
            m_joystickValues[whichOne].second->setX(1);
        }
        else if (event.jaxis.value < -m_joystickDeadZone)
        {
            m_joystickValues[whichOne].second->setX(-1);
        }
        else
        {
            m_joystickValues[whichOne].second->setX(0);
        }
    }

    // 右侧方向键上下移动
    if (event.jaxis.axis == 4) // 4 右侧上下
    {
        if (event.jaxis.value > m_joystickDeadZone)
        {
            m_joystickValues[whichOne].second->setY(1);
        }
        else if (event.jaxis.value < -m_joystickDeadZone)
        {
            m_joystickValues[whichOne].second->setY(-1);
        }
        else
        {
            m_joystickValues[whichOne].second->setY(0);
        }
    }
} // END:处理手柄方向键相关事件
void InputHandler::onJoystickButtonDown(SDL_Event &event)
{
    int whichOne = event.jaxis.which;
    m_joyButtonStates[whichOne][event.jbutton.button] = true;
}
void InputHandler::onJoystickButtonUp(SDL_Event &event)
{
    int whichOne = event.jaxis.which;
    m_joyButtonStates[whichOne][event.jbutton.button] = false;
}