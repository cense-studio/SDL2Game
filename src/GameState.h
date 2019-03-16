#ifndef __Game_State__
#define __Game_State__
#include <string>

// 游戏状态抽象类
class GameState
{
public:
  virtual ~GameState() {}
  virtual void update() = 0;
  virtual void render() = 0;

  virtual bool onEnter() = 0;
  virtual bool onExit() = 0;

  virtual std::string getStateID() = 0;
};

#endif // !__Game_State__