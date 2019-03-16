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
  typedef void (*CallBack)();

  MenuButton(LoaderParams *pParams, CallBack callback);

  void update() override;
  void draw() override;
  void clean() override;

private:
  CallBack m_callback = nullptr;
  bool m_bReleased = true;
};

#endif