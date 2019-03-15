#ifndef __Menu_State__
#define __Menu_State__
#include "GameState.h"

class MenuState : public GameState
{
public:
  virtual void update();
  virtual void render();

  virtual bool onEnter();
  virtual bool onExit();
  virtual std::string getStateID() { return s_menuID; }

private:
  static const std::string s_menuID;
};

#endif // !__Menu_State__