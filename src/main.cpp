#include "Game.h"
#undef main
// 帧率
const int FPS = 60;
// 帧耗时毫秒数
const int DELAY_TIME = (int)(1000.0f / FPS);
//12 616
int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    Uint32 frameStart; //, frameTime;

    if (IGame->init(u8"速度与激情 0.1",
                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    800, 600, false))
    {
        while (IGame->running())
        {
            // 帧开始记录时间
            frameStart = SDL_GetTicks();
            IGame->handleEvents();
            IGame->update();
            IGame->render();

            while ((SDL_GetTicks() - frameStart) < DELAY_TIME)
            {
                SDL_Delay(1);
            }
        }
        IGame->clean();
        Game::purge();
    }
    else
    {
        std::cout << "游戏初始化失败，" << SDL_GetError() << "\n";
        Game::purge();
        return -1;
    }

    return 0;
}

// 计算帧结束用了多少毫秒
//frameTime = SDL_GetTicks() - frameStart;
// 如当前帧实际耗时小于设定帧耗时,等待一小段时间
//if (frameTime < DELAY_TIME)
//{
//    SDL_Delay(DELAY_TIME - frameTime);
//}