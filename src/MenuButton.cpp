#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(LoaderParams *pParams, CallBack callback)
    : SDLGameObject(pParams), m_callback(callback)
{
    // 设置按钮图标第一帧
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    const Vector2D &mousePos = IInputHandler->getMousePosition();
    // 如果鼠标进入按钮范围
    if (mousePos.getX() < (m_position.getX() + m_width) &&
        mousePos.getX() > m_position.getX() &&
        mousePos.getY() < (m_position.getY() + m_height) &&
        mousePos.getY() > m_position.getY())
    {
        // 如果鼠标进入按钮，且左键按下了，按钮处于释放状态
        if (IInputHandler->getMouseButtonState(SDL_BUTTON_LEFT) && m_bReleased)
        {
            m_currentFrame = CLICKED;
            m_bReleased = false;
        }
        else if (!IInputHandler->getMouseButtonState(SDL_BUTTON_LEFT)) // 如果鼠标进入按钮且，左键没有按下
        {
			if (!m_bReleased)
			{
				m_callback();
				m_bReleased = true;
			}
            m_currentFrame = MOUSE_OVER;
        }
    }
    else // 鼠标不在按钮范围
    {
        m_currentFrame = MOUSE_OUT;
        m_bReleased = true;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}