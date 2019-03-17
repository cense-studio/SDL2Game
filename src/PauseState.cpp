#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Player.h"
#include "MenuState.h"
#include "MenuButton.h"
#include <iostream>

const std::string PauseState::s_playID = "PAUSE";

void PauseState::onMainButtonCliked()
{
	IGame->getStateMachine()->changeState(new MenuState());
}

void PauseState::onResumeButtonCliked()
{
	IGame->getStateMachine()->popState();
}

void PauseState::update()
{
	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
		if (m_bExited)
		{
			break;
		}
	}
}
void PauseState::render()
{
	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	if (!ITextureManager->load("assets/UI/main.png", "main_button", IGame->getRenderer()))
	{
		return false;
	}
	if (!ITextureManager->load("assets/UI/resume.png", "resume_button", IGame->getRenderer()))
	{
		return false;
	}
	m_gameObjects.push_back(new MenuButton(new LoaderParams(300, 200, 200, 80, "main_button"), onMainButtonCliked));
	m_gameObjects.push_back(new MenuButton(new LoaderParams(300, 320, 200, 80, "resume_button"), onResumeButtonCliked));
	m_bExited = false;
	return true;
}

bool PauseState::onExit()
{
	// 逐个清空对象资源
	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	// 清空对象数组
	m_gameObjects.clear();
	// 销毁当前状态创建的纹理
	ITextureManager->cleanFromTextureMap("main_button");
	ITextureManager->cleanFromTextureMap("resume_button");
	m_bExited = true;
	return true;
}