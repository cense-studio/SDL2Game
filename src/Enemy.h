#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
  public:
    Enemy(const LoaderParams *pParams);
    void draw() override;
    void update() override;
    void clean() override;
};

#endif // !__Enemy__