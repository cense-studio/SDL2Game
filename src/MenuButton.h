#ifndef __Menu_Button__
#define __Menu_Button__

#include "SDLGameObject.h"

// 菜单按钮
class MenuButton : public SDLGameObject
{
    // 菜单按钮枚举
    enum button_state
    {
        // 鼠标离开
        MOUSE_OUT = 0,
        // 鼠标进入
        MOUSE_OVER = 1,
        // 点击
        CLICKED = 2
    };

  public:
    MenuButton(LoaderParams *pParams);

    void update() override;
    void draw() override;
    void clean() override;

  private:
    /* data */
};

#endif