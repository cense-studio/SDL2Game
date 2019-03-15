#ifndef __GameObject__
#define __GameObject__

#include <iostream>
#include <string>
#include "LoaderParams.h"


#define UNUSED(x) (void)(x)

class GameObject
{
public:
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void clean() = 0;

protected:
  GameObject(const LoaderParams *pParams) {UNUSED(pParams);}
  virtual ~GameObject() {}
};

#endif // !__GameObject__