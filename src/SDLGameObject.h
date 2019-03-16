#ifndef __SDL_Game_Object__
#define __SDL_Game_Object__

#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
  public:
	SDLGameObject(const LoaderParams *pParams);

	void draw() override;
	void update() override;
	void clean() override
	{
		delete this;
	}

  protected:
	// 位置向量
	Vector2D m_position;
	// 速度向量
	Vector2D m_velocity;
	// 加速度向量
	Vector2D m_acceleration;

	int m_width = 0;
	int m_height = 0;

	int m_currentRow = 1;
	int m_currentFrame = 0;

	std::string m_textureID;
};
#endif // !__SDL_Game_Object__