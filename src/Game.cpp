#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

Game *Game::s_pInstance = nullptr;

Game::Game(/* args */)
{
}

Game::~Game()
{
}

// 初始化
bool Game::init(const std::string &title,
                int xpos, int ypos,
                int width, int height,
                bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    // 初始化SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        std::cout << "SDL初始化成功！\n";
        // 如果成功，创建窗口
        m_pWindow = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
        // 如果窗口创建成功，创建渲染器
        if (m_pWindow != nullptr)
        {
            std::cout << "窗口创建成功！\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            // 如果渲染器创建失败，销毁窗口，且引擎初始化失败！
            if (m_pRenderer != nullptr)
            {
                std::cout << "渲染器创建成功！\n";
                // 初始绘制颜色设置为白色
                SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 255, 255);
            }
            else
            {
                std::cout << "渲染器创建失败！\n";
                return false; // 渲染器创建失败了！
            }
        }
        else
        {
            std::cout << "窗口创建失败！\n";
            return false; // 窗口创建失败了
        }
    }
    else
    {
        std::cout << "SDL初始化失败！\n";
        return false; // 初始化失败了！
    }
    // 初始化 JPG和PNG 解码器
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) <= 0)
    {
        std::cout << "SDL图像解码器初始化失败！\n";
        return false;
    }
    // 初始化 MP3解码器
    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        std::cout << "SDL声音解码器初始化失败！\n";
        return false;
    }
    // 初始化字体渲染器
    if (TTF_Init() == -1)
    {
        std::cout << "SDL字体渲染器初始化失败！\n";
        return false;
    }
    // 初始化游戏手柄事件监听器
    IInputHandler->initialiseJoysticks();

    std::cout << "所有设备初始化成功！\n";
    // 运行标志设置为真
    m_bRunning = true;
    onInitialized();
    return true;
}

// 绘制
void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    if (!m_gameObjects.empty())
    {
        for (std::size_t i = 0; i != m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
    SDL_RenderPresent(m_pRenderer);
}

// 更新
void Game::update()
{
    if (!m_gameObjects.empty())
    {
        for (std::size_t i = 0; i != m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->update();
        }
    }
}

// 处理事件
void Game::handleEvents()
{
    IInputHandler->update();
}

// 清除
void Game::clean()
{
    if (!m_gameObjects.empty())
    {
        for (std::size_t i = 0; i != m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->clean();
            std::cout << "释放游对象:" << i << "\n";
        }
    }
    std::cout << "正在清除游戏资源。\n";
    TextureManager::purge();

    SDL_DestroyRenderer(m_pRenderer);
    m_pRenderer = nullptr;

    SDL_DestroyWindow(m_pWindow);
    m_pWindow = nullptr;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

// 初始化成功时调用
void Game::onInitialized()
{
    ITextureManager->load("../assets/animate.png", "animate", m_pRenderer);
    m_gameObjects.push_back(new Player(new LoaderParams(0, 0, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(0, 200, 128, 82, "animate")));
}