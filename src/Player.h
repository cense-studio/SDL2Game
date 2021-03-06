﻿#ifndef __Player__
#define __Player__
#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
  Player(const LoaderParams *pParams);
  void draw() override;
  void update() override;
  void clean() override;

private:
  void handleInput();
};

#endif // !__Player__