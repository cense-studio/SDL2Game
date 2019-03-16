#ifndef __Play_State__
#define __Play_State__
#include "GameState.h"

class PlayState : public GameState
{
  public:
    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() override { return s_playID; }

  private:
    static const std::string s_playID;
};

#endif // !__Play_State__