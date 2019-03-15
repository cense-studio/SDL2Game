#include "LoaderParams.h"

LoaderParams::LoaderParams(int x, int y, int width, int height, const std::string &textureID)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_textureID = textureID;
}
