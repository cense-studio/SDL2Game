#ifndef __Input_Handler__
#define __Input_Handler__

#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.h"

class InputHandler
{
public:
  static InputHandler *Instance()
  {
    if (s_pInstance == nullptr)
    {
      s_pInstance = new InputHandler;
    }
    return s_pInstance;
  }
  // 清除实例
  static void purge()
  {
    if (s_pInstance)
    {
      delete s_pInstance;
      s_pInstance = nullptr;
    }
  }

public:
  // 鼠标按钮枚举
  enum mouse_buttons
  {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
  };

  void update();
  void clean();

  // 初始化游戏手柄操纵杆
  void initialiseJoysticks();
  // 获取游戏手柄操纵杆初始化状态
  bool joysticksInitialised()
  {
    return m_bJoysticksInitialised;
  }
  // 获得某个手柄的方向键左右方向状态 stick: 1 左方向键 2 右方向键
  int xvalue(int joy, int stick);
  // 获得某个手柄的方向键上下方向状态 stick: 1 左方向键 2 右方向键
  int yvalue(int joy, int stick);
  // 获得某个手柄的某个按钮状态
  bool getJoyButtonState(int joy, int buttonID)
  {
    return m_joyButtonStates[joy][buttonID];
  }

  // 获得鼠标位置
  const Vector2D &getMousePosition() const
  {
    return m_mousePosition;
  }
  // 获得鼠标按钮状态
  bool getMouseButtonState(int buttonNumber)
  {
    return m_mouseButtonStates[buttonNumber];
  }

  // 获得键盘按键状态
  bool isKeyDown(SDL_Scancode key);

private:
  InputHandler();
  ~InputHandler() {}

  // 处理键盘事件
  //void onKeyDown();
  //void onKeyUp();
  // 处理鼠标事件
  void onMouseMove(SDL_Event &event);
  void onMouseButtonDown(SDL_Event &event);
  void onMouseButtonUp(SDL_Event &event);
  // 处理手柄事件
  void onJoystickAxisMove(SDL_Event &event);
  void onJoystickButtonDown(SDL_Event &event);
  void onJoystickButtonUp(SDL_Event &event);

  static InputHandler *s_pInstance;

private:
  // 游戏手柄初始化状态
  bool m_bJoysticksInitialised = false;
  // 游戏手柄数据指针
  std::vector<SDL_Joystick *> m_joysticks;
  // 用向量对来保存手柄方向键移动方向，一个手柄有2个方向键，一个方向键有上下左右四个方向
  std::vector<std::pair<Vector2D *, Vector2D *>> m_joystickValues;
  // 手柄按键状态2维动态数组，意思为哪个手柄的哪个按钮
  std::vector<std::vector<bool>> m_joyButtonStates;
  // 手柄方向键按键灵敏度
  const int m_joystickDeadZone = 10000;

  // 鼠标按钮状态
  std::vector<bool> m_mouseButtonStates;
  // 鼠标位置
  Vector2D m_mousePosition;

  // 键盘按键状态
  const Uint8 *m_keysStates;
};
// 获取游戏输入处理器实例
#define IInputHandler InputHandler::Instance()

#endif // !__Input_Hand__ler