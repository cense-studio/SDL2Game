#ifndef __Vector_2D__
#define __Vector_2D__

#include <math.h>

class Vector2D
{
  public:
    Vector2D(float x = 0.0f, float y = 0.0f) : m_x(x), m_y(y) {}
    // 获得X值
    float getX() { return m_x; }
    // 获得Y值
    float getY() { return m_y; }

    // 设置X值
    void setX(float x) { m_x = x; }
    // 设置Y值
    void setY(float y) { m_y = y; }

    // 获取向量长度
    float length() { return sqrt(m_x * m_x + m_y * m_y); }

    // 向量归一化，当归一化后表示一个方向
    void normalize()
    {
        float l = length();
        if (l > 0)  // 防止除法出错
        {
            (*this) *= 1 / l;
        }
    }

    // v3 = v1 + v2
    Vector2D operator+(const Vector2D &v2) const
    {
        return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
    }

    // v1 = v1 + v2
    friend Vector2D &operator+=(Vector2D &v1, const Vector2D &v2)
    {
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;
        return v1;
    }

    // v2 = v1 * n
    Vector2D operator*(float scalar)
    {
        return Vector2D(m_x * scalar, m_y * scalar);
    }

    // v1 = v1 * n
    Vector2D &operator*=(float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        return *this;
    }

    // v3 = v1 - v2
    Vector2D operator-(const Vector2D &v2) const
    {
        return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
    }

    // v1 = v1 - v2
    friend Vector2D &operator-=(Vector2D &v1, const Vector2D &v2)
    {
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;
        return v1;
    }

    // v2 = v1 / n
    Vector2D operator/(float scalar)
    {
        return Vector2D(m_x / scalar, m_y / scalar);
    }

    // v1 = v1 / n
    Vector2D &operator/=(float scalar)
    {
        m_x /= scalar;
        m_y /= scalar;
        return *this;
    }

  private:
    float m_x;
    float m_y;
};

#endif //__Vector_2D__