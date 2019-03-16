#ifndef __Menu_State__
#define __Menu_State__
#include "GameState.h"
#include "GameObject.h"
#include <vector>

class MenuState : public GameState
{
public:
  void update() override;
  void render() override;

  bool onEnter() override;
  bool onExit() override;
  std::string getStateID() override { return s_menuID; }

protected:
  static void onPlayButtonCliked();
  static void onExitButtonCliked();

private:
  static const std::string s_menuID;

  std::vector<GameObject *> m_gameObjects;
};

#endif // !__Menu_State__