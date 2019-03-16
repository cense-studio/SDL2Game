#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(LoaderParams *pParams) : SDLGameObject(pParams)
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
        m_currentFrame = MOUSE_OVER;
        if (IInputHandler->getMouseButtonState(SDL_BUTTON_LEFT)) // 鼠标左键点击了
        {
            m_currentFrame = CLICKED;
        }
    }
    else // 鼠标不在按钮范围
    {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}