#ifndef __Loader_Params__
#define __Loader_Params__
#include <string>
#include "Config.h"
class LoaderParams
{
public:
  LoaderParams(int x, int y, int width, int height, const std::string &textureID);

  int getX() const { return m_x; }
  int getY() const { return m_y; }
  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }
  std::string getTextureID() const { return m_textureID; }

private:
  int m_x;
  int m_y;
  int m_width;
  int m_height;
  std::string m_textureID;
};
#endif // !__Loader_Params__
