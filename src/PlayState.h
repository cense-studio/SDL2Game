#ifndef __Play_State__
#define __Play_State__
#include "GameState.h"

class PlayState : public GameState
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

#endif // !__Play_State__